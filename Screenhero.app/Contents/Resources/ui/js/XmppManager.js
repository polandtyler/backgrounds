var XmppManager = new function () {
    var self = this;

    self.jsRpcID = 0;
    self.BOSH_SERVICE = 'http://xmpp0.screenhero.com:5280/http-bind'
    self.stropheConnection = null;

    self.networkRegions = 'unknown';
    self.handlers = [];
    
    self.settings = {
        buddyThatIsMe: {
            email: ""
        },
        password: "",
        shouldRememberPwd: true,
        isVoiceChatMutedOnScreenShare: false,
        shouldShowWelcomeView: false,
        turnInfoTimedHandlerRef: null,
    };

    this.UpdateNetworkRegions = function (newRegions) {
        var oldRegions = self.networkRegions;
        self.networkRegions = newRegions;

        if (newRegions != oldRegions)
        {
            self.RequestTurnInfo();
            console.log("UpdateNetworkRegions()");
        }
    }

    this.SendChatMessageToBuddy = function (bareJid, msgTxt) {
        var reply = $msg({to: bareJid, from: self.connection.jid, type: 'chat'})
                .c("body").t(msgTxt);
        self.connection.send(reply.tree());
    }

    this.jabberRosterCallback = function (iq)
    {
        console.log("jabberRosterCallback called");
        var jids = {};
        var hasBuddies = false;
        $(iq).find('item').each(function(){
            var jid = $(this).attr('jid');
            jids[jid] = $(this).attr('subscription');
            hasBuddies = true;
        });

        if (hasBuddies)
            self.LoadBuddyListForJids(jids);
        else {
            BuddyListManager.ShowNoBuddiesView();
            self.SendPresence();
        }
        return true;
    }

    this.turnInfoCallback = function(iq)
    {
        console.log("turnInfoCallback called");
        var ttl = parseInt($(iq).find('auth').attr('ttl'));

        if (ttl > 0)
        {
            console.log("Token received; valid for " + ttl + " seconds.");

            self.turnInfoTimedHandlerRef = self.connection.addTimedHandler(((ttl / 2) * 1000), function ()
                {
                    self.RequestTurnInfo();
                    return false;
                }
            );
        }
        else
        {
            console.log("Invalid TTL received -- We're likely unable to use the relay; retrying in 30 seconds");

            // Try again in 10 seconds
            self.turnInfoTimedHandlerRef = self.connection.addTimedHandler(30000, function ()
                {
                    self.RequestTurnInfo();
                    return false;
                }
            );
        }

        var turnServers = [];
        $(iq).find('turnserver').each(function(i) {
            turnServers.push({ region: $(this).attr('region'),
                               ipv4_address: $(this).attr('ipv4_address'),
                               udp_port: $(this).attr('udp_port'),
                               tcp_port: $(this).attr('tcp_port')});
        });

        JSToNativeBridge.CallNativeFunction("UpdateOptionsManager", {turnUsername: $(iq).find('auth').attr('username'),
                                                                     turnPassword: $(iq).find('auth').attr('password'),
                                                                     turnServers:  turnServers});

        return true;
    }

    this.turnInfoErrorCallback = function(iq)
    {
        if (iq == null)
            console.log("RequestTurnInfo timed out! Retrying in 30 seconds.");
        else
            console.log("RequestTurnInfo returned an error! Retrying in 30 seconds.");

        // Try again in 10 seconds
        self.turnInfoTimedHandlerRef = self.connection.addTimedHandler(30000, function ()
            {
                self.RequestTurnInfo();
                return false;
            }
        );
    }
    
    this.RequestTurnInfo = function()
    {
        if (self.connection.connected) {
            var regions = self.networkRegions;
            if (self.turnInfoTimedHandlerRef != null)
            {
                self.connection.deleteTimedHandler(self.turnInfoTimedHandlerRef);
                self.turnInfoTimedHandlerRef = null;
            }

            if (regions == 'unknown')
            {
                regions = "west|east|eu-west"; // Default fallback
            }

            var iq = $iq({type: 'get'}).c('regions', {xmlns: 'screenhero:api:turninfo'}).t(regions);
            self.connection.sendIQ(iq, self.turnInfoCallback, self.turnInfoErrorCallback, 30000 /* 30 second timeout */);
        }

        return true;
    }
    
    this.LoadBuddyListForJids = function(jids)
    {
        console.log("LoadBuddyListForJids called with " + Object.keys(jids).length);
        var requests = [];
        for (var jid in jids)
        {
            var pbUIR = ProtobufManager.builder.build("ServerSideProtocol.AgentUserInfoRequest");
            pbUIR = new pbUIR();
            pbUIR.buddyJID = jid;
            pbUIR.wantBuddyProfilePic = false;
            requests.push(pbUIR);
        }

        ProtobufManager.SendProtoBuf(
            "AgentBulkUserInfoRequest", 
            {
                requests: requests
            }, 
            function (jsonOutputStr) {
                var jsonOutput = JSON.parse(jsonOutputStr)
                var pbClass = jsonOutput.classType;
                var pbData = jsonOutput.pbData;
                var pbBulkResponse = ProtobufManager.builder.build("ServerSideProtocol.AgentBulkUserInfoResponse")
                pbBulkResponse = pbBulkResponse.decode64(pbData);
                var buddies = [];
                for (var i = pbBulkResponse.responses.length - 1; i >= 0; i--) {
                    var pbUIR = pbBulkResponse.responses[i];
                    buddies.push(Utils.buddyWithSanitizedProfilePic({
                        name: pbUIR.buddyName,
                        email: pbUIR.buddyEmail,
                        bareJid: pbUIR.buddyJID,
                        profilePicURL: pbUIR.buddyProfilePicURL,
                        paymentType: pbUIR.paymentType,
                        isOnline: false,
                        show: 0,
                        subscription: jids[pbUIR.buddyJID]
                    }));
                }

                BuddyListManager.UpdateBuddyList(buddies);
                BuddyListManager.ReinstatePreviousSessionStatesToUI();
                
                self.SendPresence();
            },
            function () {
                console.log("ProtobufManager.SendProtoBuf(AgentBulkUserInfoRequest) failed");
            }
        );
    }

    this.SendPresence = function()
    {
        var presence = $pres();
        presence.c("c", {xmlns: "http://jabber.org/protocol/caps", ver: BuddyListManager.ra.get("OptionsManager.version"), ext: ""});
        if (BuddyListManager.IsInShare()) {
            presence.up();
            presence.c("show", {}, "dnd");
        }
        try {
            self.connection.send(presence.tree());
        }
        catch (e) {
            console.log("XmppManager exception in SendPresence: " + e);
        }
    }

    this.jabberPresenceCallback = function (presence)
    {
        var presence_type = $(presence).attr('type'); // unavailable, subscribed, etc...
        var from = $(presence).attr('from'); // the jabber_id of the contact
//        console.log("presence: " + from);
        if (presence_type != 'error'){
            if (presence_type == "subscribe") {
                self.LoadProfileForJidWithCallback(from, self.ReceivedSubscriptionRequest)
            }
            else if (presence_type == 'subscribed' || (presence_type === undefined && BuddyListManager.GetBuddyWithJID($(presence).attr('from').split("/")[0]) == null && self.connection.jid != $(presence).attr('from'))) {
                self.LoadProfileForJidWithCallback(from, BuddyListManager.AddBuddyToList)
            }
            else if (presence_type == 'unsubscribe') {
                self.RemoveBuddyFromList(from); // unsubscribe from them
            }
            else if (presence_type == 'unsubscribed') {
                BuddyListManager.RemoveBuddyFromList(from); // remove from the ui
            }
            if (presence_type === undefined || presence_type == 'unavailable') {
                if (from.split("/")[0] != BuddyListManager.ra.get("OptionsManager.buddyThatIsMe.bareJid"))
                {
                    var found = false;
                    var buddyList = BuddyListManager.ra.get("buddyList");
                    for (var i = buddyList.length - 1; i >= 0; i--) {
                        if (buddyList[i]["bareJid"] == from.split("/")[0]) {
                            var isOnline = presence_type !== 'unavailable';
                            buddyList[i].isOnline = isOnline;
                            if (!isOnline) {
                                if (buddyList[i]["isSelected"]) {
                                    buddyList[i]["isSelected"] = false;
                                    var numSelectedBuddies = BuddyListManager.ra.get("numSelectedBuddies") - 1;
                                    BuddyListManager.ra.set("numSelectedBuddies", Math.max(0, numSelectedBuddies));
                                }
                            }
                            buddyList[i]["version"] = $(presence).find("c").attr("ver");
                            buddyList[i]["show"] = $(presence).find("show").length > 0 ? BuddyListManager.JabberStatusShow.DoNotDisturb : BuddyListManager.JabberStatusShow.None;
                            buddyList[i]["xmppJid"] = from;
                            buddyList[i]["hidden"] = false;
                            buddyList[i]["subscription"] = null;
                            found = true;
                            // console.log("got presence for " + BuddyListManager.ra.get("buddyList." + i).name + ", info: " + JSON.stringify(BuddyListManager.ra.get("buddyList." + i)));
                        }
                    };
                    if (!found)
                        self.queuedPresenceUpdates.push(presence);
                    else {
                        BuddyListManager.ra.set("buddyList", buddyList);
                        BuddyListManager.UpdateBuddyList(BuddyListManager.ra.get("buddyList"));
                    }
                }
            }
        }
        return true;
    }

    this.LoadProfileForJidWithCallback = function(jid, callback) {
        ProtobufManager.SendProtoBuf(
            "AgentUserInfoRequest", 
            {
                buddyJID: jid,
                wantBuddyProfilePic: false
            }, 
            function (jsonOutputStr) {
                var jsonOutput = JSON.parse(jsonOutputStr)
                var pbClass = jsonOutput.classType;
                var pbData = jsonOutput.pbData;
                var response = ProtobufManager.builder.build("ServerSideProtocol.AgentUserInfoResponse")
                response = response.decode64(pbData);
                var buddy = Utils.buddyWithSanitizedProfilePic({
                    name: response.buddyName,
                    email: response.buddyEmail,
                    bareJid: response.buddyJID,
                    profilePicURL: response.buddyProfilePicURL,
                    isOnline: false,
                    show: 0
                });
                callback(buddy);
                self.ProcessQueuedPresenceUpdates();
            },
            function () {
                console.log("LoadProfileForJidWithCallback failed");
            }
        );
    }

    this.ProcessQueuedPresenceUpdates = function() {
        var updates = self.queuedPresenceUpdates;
        self.queuedPresenceUpdates = [];
        updates.forEach(function (presence) {
            self.jabberPresenceCallback(presence);
        });
    }

    this.SendBuddyInviteToJid = function(jid) {
        var sendInvite = function(jid) {
            var iq = $iq({type: 'set'}).c('query', {xmlns: 'jabber:iq:roster'}).c('item', { jid: jid });
            self.connection.sendIQ(iq, self.jabberRosterCallback);
            self.connection.send($pres({ to: jid, type: "subscribe" }));
        }

        BuddyListManager.GetBuddyWithJID(jid, function(buddy) {
            buddy.subscription = "none";
            buddy.hidden = false;
            BuddyListManager.ra.set("buddyList", BuddyListManager.ra.get("buddyList")); // HACK but fixes the no-show for pending invites
            sendInvite(jid);
        });
    }

    this.ReceivedSubscriptionRequest = function(buddy) {
        var savedBuddy = BuddyListManager.GetBuddyWithJID(buddy.bareJid);
        if (savedBuddy) {
            self.connection.send($pres({ to: buddy.bareJid, type: "subscribed" }));
            if (savedBuddy.subscription == 'none')
                self.connection.send($pres({ to: buddy.bareJid, type: "subscribe" }));
        }
        else {
            BuddyList.ShowFriendRequest(buddy);
        }
    }

    this.RespondToInvitation = function(jid, didAccept)
    {
        if (didAccept) {
            self.connection.send($pres({ to: jid, type: "subscribe" }));
            self.connection.send($pres({ to: jid, type: "subscribed" }));
        }
        else
            self.connection.send($pres({ to: jid, type: "unsubscribed" }));
    }

    this.RemoveBuddyFromList = function(jid)
    {
        var iq = $iq({type: 'set'}).c('query', {xmlns: 'jabber:iq:roster'}).c('item', { jid: jid, subscription: 'remove'});
        self.connection.sendIQ(iq, self.jabberRosterCallback);
        BuddyListManager.RemoveBuddyFromList(jid);
    }

    this.onConnect = function(status, reason)
    {
        if (status == Strophe.Status.CONNECTING || status == Strophe.Status.AUTHENTICATING) {
            console.log('Strophe is connecting.');
            Main.SetLoginState(Main.loginStates.signingIn);
        }
        else if (status == Strophe.Status.CONNFAIL) {
            console.log('Strophe failed to connect.');
            Main.SetLoginState(Main.loginStates.signedOut);
            Main.HandleStatusReason(Main.loginErrors.XMPPError);
        }
        else if (status == Strophe.Status.DISCONNECTING) {
            console.log('Strophe is disconnecting because: ' + reason);
            // J: never gets here on websockets
            // Main.SetLoginState(Main.loginStates.signingOut);
            // if (reason == "unknown stream-error") {
            //     Main.HandleStatusReason(Main.loginErrors.signedInElsewhere);
            //     self.shouldReconnectOnDisconnect = false;
            // }
        }
        else if (status == Strophe.Status.DISCONNECTED || status == Strophe.Status.AUTHFAIL) {
            console.log("auth did fail = " + (status == Strophe.Status.AUTHFAIL));
            console.log('Strophe is disconnected because: ' + reason);
            BuddyListManager.XmppDidDisconnect();
            Main.SetLoginState(Main.loginStates.signedOut);
            if (status == Strophe.Status.AUTHFAIL)
                Main.HandleStatusReason(Main.loginErrors.badPassword);
            var shouldReconnect = self.shouldReconnectOnDisconnect;
            self.Initialize();
            if (shouldReconnect)
                LoginView.ToggleSignIn();
        }
        else if (status == Strophe.Status.CONNECTED) {
            console.log('Strophe is connected.');
            BuddyListManager.ra.set("OptionsManager.buddyThatIsMe.xmppJid", self.connection.jid);
            JSToNativeBridge.CallNativeFunction("UpdateOptionsManager", {buddyThatIsMe: BuddyListManager.ra.get("OptionsManager.buddyThatIsMe")});
            if (self.settings.shouldShowWelcomeView)
                self.LocalJSCall("ShowWelcomeView", []);
            self.settings.shouldShowWelcomeView = false;
            self.shouldReconnectOnDisconnect = true;
            JSToNativeBridge.CallNativeFunction("SaveSettings");

            Main.SetLoginState(Main.loginStates.signedIn);
            self.doPing();
            self.RequestTurnInfo();

            // self.LocalJSCall("UpdateUserProfile", [JSON.stringify(self.buddyThatIsMe)]);

            self.handlers.push(self.connection.addHandler(self.onMessage, null, 'message', null, null,  null));
            self.handlers.push(self.connection.addHandler(self.ReceivedSessionMessageFromJidOnChannel, Strophe.NS.SCREENHERO, "iq", "result"));
            self.handlers.push(self.connection.addHandler(self.doPeerPong, Strophe.NS.SPING, "iq", "get"));
            self.handlers.push(self.connection.addHandler(self.receivedApiRequest, Strophe.NS.SCREENHEROAPI, "iq", "set"));

            // J: remove this speedup until we revisit buddy list / presence stuff, right now this causes some ppl to never show up in the buddy list
            // if (BuddyListManager.ra.get("buddyList").length > 0)
            //     self.SendPresence();

            var iq = $iq({type: 'get'}).c('query', {xmlns: 'jabber:iq:roster'});
            self.connection.sendIQ(iq, self.jabberRosterCallback);
        }
        else if (status == Strophe.Status.ERROR) {
            if (reason == "conflict") {
                Main.HandleStatusReason(Main.loginErrors.signedInElsewhere);
                self.shouldReconnectOnDisconnect = false;
            } 
            else {
                console.log('Strophe got a confusing error');
            }
        }
        else {
            console.log('Strophe is confused');
        }
    }

    this.receivedApiRequest = function(iq) {
        if ($(iq).children()[0].nodeName == "rpc-request") {
            var msg = $(iq).children().text();
            var response = NativeToJSBridge.performJsonRpcWithSource(msg, NativeToJSBridge.SourceTypes.WebAPI);
            var iqresponse = $iq({type: 'result', to: $(iq).attr("from"), id: $(iq).attr("id")}).c('rpc:rpc-response', {"xmlns:rpc": Strophe.NS.SCREENHEROAPI}).t(response);
            self.connection.sendIQ(iqresponse, function() {} );
        }
        return true;
    }

    this.doPing = function() {
        if (Main.GetLoginState() == Main.loginStates.signedIn)
        {
            var id = self.connection.getUniqueId();
            var iq = $iq({type: 'get', to: self.connection.jid.split("@")[1].split("/")[0], id: id}).c('ping', {xmlns: 'urn:xmpp:ping'});
            self.connection.sendIQ(iq, self.getPong);
            clearTimeout(self.pingTimeoutHandle);
            self.pingTimeoutHandle = setTimeout(self.doPingTimeout, 50 * 1000);
        }
    }

    this.getPong = function (pongStanza) {
        clearTimeout(self.pingTimeoutHandle);
        self.pingTimeoutHandle = 0;
        setTimeout(self.doPing, 50 * 1000);
    }

    this.doPingTimeout = function() {
        console.log("ping timed out, disconnecting...");
        self.connection.disconnect();
    }

    // pingID = 0;
    // this.doPeerPing = function(xmppjid) {
    //     var iq = $iq({type: 'get', to: xmppjid, id: pingID++}).c('ping', { xmlns: Strophe.NS.SPING });
    //     self.connection.sendIQ(iq, self.SendSessionMessageToJidCallback);
    //     console.log("sending ping " + pingID);
    // }

    // this.doHundredPings = function(xmppjid) {
    //     for (var i=0; i<100; i++) {
    //         var iq = $iq({type: 'get', to: xmppjid, id: pingID++}).c('ping', { xmlns: Strophe.NS.SPING, reply: false });
    //         self.connection.sendIQ(iq, self.SendSessionMessageToJidCallback);
    //         console.log("sending ping " + pingID);
    //     }
    // }

    // this.doPeerPong = function(iq) {
    //     var from = $(iq).attr("from");
    //     var id = $(iq).attr("id");
    //     if (pingID == id) {
    //         console.log("pinged, i was at " + pingID + ", he was at " + id);
    //         pingID++;
    //         if ($(iq).children(0).attr("reply") !== "false")
    //             self.doPeerPing(from);
    //     }
    //     else {
    //         console.log("fucked, i was at " + pingID + ", he was at " + id);
    //     }
    //     return true;
    // }

    this.onMessage = function(msg) {
        var to = msg.getAttribute('to');
        var from = msg.getAttribute('from');
        var type = msg.getAttribute('type');
        var elems = msg.getElementsByTagName('body');

        if (type == "chat" && elems.length > 0) {
            var body = elems[0];
            from = from.split("/")[0];
            ChatWindowManager.ReceivedChatMessageFromBuddy(from, body.textContent);
        }
        // we must return true to keep the handler alive.  
        // returning false would remove it after it finishes.
        return true;
    }

    this.DoXmppLogin = function () {
        Strophe.SASLPlain.prototype.priority = 90;
        self.connection.connect(BuddyListManager.ra.get("OptionsManager.buddyThatIsMe.bareJid")+"/appsharing.web", BuddyListManager.ra.get("OptionsManager.password"), self.onConnect);
    }

    this.ChangeUserStatus = function (newStatus) {
        self.shouldReconnectOnDisconnect = false;
        self.connection.disconnect();
    }

    this.Initialize = function () {
        // self.connection = new Strophe.Connection(self.BOSH_SERVICE);
        if (self.connection) {
            for (var handler in self.handlers)
                self.connection.deleteHandler(handler);
            
            self.handlers = [];
        }
        self.connection = new Strophe.Connection("ws://10.10.10.10:5281/sockjs");

        self.handlers.push(self.connection.addHandler(self.jabberPresenceCallback, null, "presence"));
        Strophe.addNamespace('SCREENHEROAPI', "screenhero:api:rpc");
        Strophe.addNamespace('SCREENHERO', "urn:xmpp:screenhero");
        Strophe.addNamespace('SPING', "urn:xmpp:sping");
        self.queuedPresenceUpdates = [];
        self.pingTimeoutHandle = 0;
        self.shouldReconnectOnDisconnect = false;

        Strophe.log = function (level, msg) {
            if (level > 0)
                console.log("Strophe (" + level + "): " + msg);
        }
    }

    this.SendSessionMessageToJidOnChannel = function (msg, jid, channel, sessionid) {
        msg = Base64.encode(JSON.stringify({msg: msg, channel: channel, sessionid: sessionid}));
        var id = self.connection.getUniqueId();
        var iq = $iq({type: 'result', to: jid, id: id}).c('screenhero', {xmlns: Strophe.NS.SCREENHERO}, msg);
        self.connection.sendIQ(iq, self.SendSessionMessageToJidCallback);
        // self.connection.xmlOutput = function (msg) { console.log("Out: " + msg.innerHTML); }
        //self.connection.xmlInput = function (msg) { console.log("In: " + msg.outerHTML); }
    }

    this.SendSessionMessageToJidCallback = function (jid) {
        //IDGAF
        // console.log("idgaf");
    }

    this.ReceivedSessionMessageFromJidOnChannel = function (msg) {
//        console.log("Received msg " + msg.innerHTML);
        var to = msg.getAttribute('to');
        var from = msg.getAttribute('from');
        var type = msg.getAttribute('type');
        var id = msg.getAttribute('id');
        var elems = msg.getElementsByTagName('screenhero');
        var txt = Strophe.getText(elems[0]);
        txt = Base64.decode(txt);
        var obj = jQuery.parseJSON(txt);
        JSToNativeBridge.CallNativeFunction("ReceivedSessionMessageFromJidOnChannel", from, obj.msg, obj.channel, obj.sessionid);

        // var iq = $iq({type: 'result', to: from, id: id}).c(
        //         'screenhero', {xmlns: Strophe.NS.SCREENHERO}, "ok");
        // self.connection.sendIQ(iq, self.SendSessionMessageToJidCallback);

        return true;
    }
}
