var WebNativeObject = new function () {
    var self = this;

    self.jsRpcID = 0;
    self.BOSH_SERVICE = 'http://xmpp0.screenhero.com:5280/http-bind'
    self.stropheConnection = null;

    self.buddyList = [];

    self.settings = {
        buddyThatIsMe: {
            email: ""
        },
        password: "",
        shouldRememberPwd: true,
        isVoiceChatMutedOnScreenShare: false,
        shouldShowWelcomeView: false
    };

    this.CallNativeFunction = function(jsonStr) {
        var jsonrpc = jQuery.parseJSON(jsonStr);
        var method = eval("self." + jsonrpc.method);
        if (method)
            method.apply(this, jsonrpc.params);
        else
            console.log("Native->" + jsonrpc.method + "() not implemented in WebNativeObject.js");
    }

    this.UpdateOptionsManager = function(updateObj) {
        for (var key in updateObj) {
            self.settings[key] = updateObj[key];
        }
    }

    this.SaveSettings = function() {
        docCookies.setItem("settings", JSON.stringify(Utils.sanitizedObject(self.settings, {keysToSkip: ["profilePicURL"]})));
    }

    this.LoadSettings = function() {
        var jsonStr = docCookies.getItem("settings");
        if (jsonStr)
            self.settings = JSON.parse(jsonStr);
    }

    this.SendChatMessageToBuddy = function (bareJid, msgTxt) {
        var reply = $msg({to: bareJid, from: self.connection.jid, type: 'chat'})
                .c("body").t(msgTxt);
        self.connection.send(reply.tree());
    }

    this.jabberRosterCallback = function (iq)
    {
        var requests = [];
        $(iq).find('item').each(function(){
            var jid = $(this).attr('jid');
            var pbUIR = self.builder.build("ServerSideProtocol.AgentUserInfoRequest");
            pbUIR = new pbUIR();
            pbUIR.buddyJID = jid;
            requests.push(pbUIR);
        });

        self.SendProtoBuf(
            "AgentBulkUserInfoRequest", 
            {
                requests: requests
            }, 
            function (jsonOutputStr) {
                var jsonOutput = JSON.parse(jsonOutputStr)
                var pbClass = jsonOutput.classType;
                var pbData = jsonOutput.pbData;
                var pbBulkResponse = self.builder.build("ServerSideProtocol.AgentBulkUserInfoResponse")
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
                        show: 0
                    }));
                }

                self.buddyList = buddies;
                self.SendBuddyList();

                if (!self.hasInitializedPresence) {
                    self.connection.addHandler(self.jabberPresenceCallback, null, "presence");
                    self.connection.send($pres().tree());
                    self.hasInitializedPresence = true;
                }
        });

        return true;
    }

    this.LocalJSCall = function(funcName, paramArray) {
        NativeToJSBridge.performJsonRpcWithSource(JSON.stringify(Utils.createJsonRpcObjectFromObject({method:funcName, params: paramArray, id: self.jsRpcID++})), NativeToJSBridge.SourceTypes.Native);
    }

    this.SendBuddyList = function() {
        self.LocalJSCall("RefreshBuddyList", [self.buddyList]);
    }

    this.jabberPresenceCallback = function (presence)
    {
        var presence_type = $(presence).attr('type'); // unavailable, subscribed, etc...
        var from = $(presence).attr('from'); // the jabber_id of the contact
        if (presence_type != 'error'){
            for (var i = self.buddyList.length - 1; i >= 0; i--) {
                if (self.buddyList[i].bareJid == from.split("/")[0]) {
                    self.buddyList[i].isOnline = presence_type !== 'unavailable';
                }
            };
            self.SendBuddyList();
        }

        return true;
    }

    this.onConnect = function(status)
    {
        if (status == Strophe.Status.CONNECTING || status == Strophe.Status.AUTHENTICATING) {
            console.log('Strophe is connecting.');
            self.LocalJSCall("UpdateUserStatus", [Main.loginStates.signingIn]);
        }
        else if (status == Strophe.Status.CONNFAIL) {
            console.log('Strophe failed to connect.');
            self.LocalJSCall("UpdateUserStatus", [Main.loginStates.signedOut]);
            self.LocalJSCall("UpdateUserStatusReason", [Main.loginErrors.XMPPError]);
        }
        else if (status == Strophe.Status.DISCONNECTING) {
            console.log('Strophe is disconnecting.');
            self.LocalJSCall("UpdateUserStatus", [Main.loginStates.signingOut]);
        }
        else if (status == Strophe.Status.DISCONNECTED || status == Strophe.Status.AUTHFAIL) {
            console.log('Strophe is disconnected.');
            self.LocalJSCall("UpdateUserStatus", [Main.loginStates.signedOut]);
            if (status == Strophe.Status.AUTHFAIL)
                self.LocalJSCall("UpdateUserStatusReason", [Main.loginErrors.badPassword]);
        }
        else if (status == Strophe.Status.CONNECTED) {
            console.log('Strophe is connected.');
            if (self.settings.shouldShowWelcomeView)
                self.LocalJSCall("ShowWelcomeView", []);
            self.settings.shouldShowWelcomeView = false;
            self.SaveSettings();

            self.LocalJSCall("UpdateUserStatus", [Main.loginStates.signedIn]);

            // self.LocalJSCall("UpdateUserProfile", [JSON.stringify(self.buddyThatIsMe)]);

            self.connection.addHandler(self.onMessage, null, 'message', null, null,  null); 
            self.connection.addHandler(self.receivedApiRpcRequest, "screenhero:api:rpc", "iq", "set");

            iq = $iq({type: 'get'}).c('query', {xmlns: 'jabber:iq:roster'});
            self.connection.sendIQ(iq, self.jabberRosterCallback);
        }
        else {
            console.log('Strophe is confused');
        }
    }

    this.onMessage = function(msg) {
        var to = msg.getAttribute('to');
        var from = msg.getAttribute('from');
        var type = msg.getAttribute('type');
        var elems = msg.getElementsByTagName('body');

        if (type == "chat" && elems.length > 0) {
            var body = elems[0];
            from = from.split("/")[0];
            self.LocalJSCall("ReceivedChatMessageFromBuddy", [from, Strophe.getText(body)]);
        }
        // we must return true to keep the handler alive.  
        // returning false would remove it after it finishes.
        return true;
    }

    this.SendProtoBuf = function(pbType, data, handler) {
        var pbUIR = self.builder.build("ServerSideProtocol." + pbType);
        pbUIR = new pbUIR();
        for (var key in data) {
            pbUIR[key] = data[key];
        }        
        $.ajax({
            url: "http://api.screenhero.com/web-protobuf",
            type: "POST",
            data: {
                msgClass: pbType,
                requestBody: pbUIR.encode().toBase64()
            }
        }).then(handler);
    }

    this.DoXmppLogin = function () {
        self.connection.connect(self.settings.buddyThatIsMe.bareJid+"/appsharing.web", md5(self.settings.password), self.onConnect);
    }

    this.ChangeUserStatus = function (newStatus) {
        self.connection.disconnect();
    }

    this.LaunchUrlInBrowser = function(url) {
        window.open(url, "_blank");
    }

    this.SignalReadyForLaunch = function () {
        self.LoadSettings();

        var ProtoBuf = dcodeIO.ProtoBuf;
        $.ajax("../protobuf/ServerSide.proto").then(function (proto) {
            self.builder = ProtoBuf.protoFromString(proto);
            self.connection = new Strophe.Connection(self.BOSH_SERVICE);
            // self.connection.xmlOutput = function (msg) { console.log("Out: " + msg.outerHTML); }
            // self.connection.xmlInput = function (msg) { console.log("In: " + msg.outerHTML); }
            Strophe.log = function (level, msg) {
                if (level > 0)
                    console.log("Strophe (" + level + "): " + msg);
            }

            self.LocalJSCall("EnableDebugging", []);
            self.LocalJSCall("InitializeOptionsManager", [{
                buddyThatIsMe: self.settings.buddyThatIsMe,
                password: self.settings.password,
                isVoiceChatMutedOnScreenShare: self.settings.isVoiceChatMutedOnScreenShare, 
                isRingingMuted: false
            }]);

            LoginView.LaunchWithSignIn();
        });
    }

    this.receivedApiRpcRequest = function (msg) {
        console.log("api got: " + msg.outerHTML);
        var ret = NativeToJSBridge.performJsonRpcWithSource(msg.getElementsByTagName("rpc-request")[0].textContent, NativeToJSBridge.SourceTypes.WebAPI);
        var id = msg.getAttribute('id');
        var to = msg.getAttribute('from');
        //-- target (mac app)
        // <cli:iq id="2877310434" to="xmpp0.powwow.cc" type="result" xmlns:cli="jabber:client">
        //  <rpc:rpc-response xmlns:rpc="screenhero:api:rpc">{"jsonrpc":"2.0","id":1}</rpc:rpc-response>
        // </cli:iq>
        
        //-- Option 1: doesn't have everything, but it does result in an instant return on the webapp
        // var iq = $iq({id: id, to: to, type: 'result'}).c('rpc-response', {"xmlns": 'screenhero:api:rpc'}, ret);

        //-- Option 2: has the rpc: prefix, but it does result in an instant return on the webapp
        var iq = $iq({id: id, to: to, type: 'result'}).c('rpc:rpc-response', {"xmlns:rpc": 'screenhero:api:rpc'}, ret);

        //-- Option 3: has everything (look below!), but it times out!! wtf!?
        // <cli:iq id="616388353" to="xmpp0.powwow.cc" type="result" xmlns:cli="jabber:client">
        //  <rpc:rpc-response xmlns:rpc="screenhero:api:rpc">{"jsonrpc":"2.0","id":1}</rpc:rpc-response>
        // </cli:iq>
        // var iq = new Strophe.Builder("cli:iq", {id: id, to: to, type: 'result', "xmlns:cli": "jabber:client"}).c('rpc:rpc-response', {"xmlns:rpc": 'screenhero:api:rpc'}, ret);

        console.log("api snd: " + iq.tree().outerHTML);
        self.connection.sendIQ(iq, function() {});
        return true;
    }
}
