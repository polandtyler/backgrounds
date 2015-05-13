var browserNativeObject = new function () {
    var self = this;

    self.SessionType = { None: 0, Screen: 1, Voice: 2, Video: 3 };
    self.settings = {
        buddyThatIsMe: {
            // email: "j@powwow.cc"
            email: "j@iteleportmobile.com"
            // email:"faraz+2@screenhero.com"
        },
        password: "a",
        shouldRememberPwd: true,
        isVoiceChatMutedOnScreenShare: false,
        shouldShowWelcomeView: false,
        isSlave: false, // set this to true to test incoming shares
        sessionType: self.SessionType.Screen,
        buddyStates: {},
        sessionId: 1
    };
    self.UpdateType = { None: 0, Minor: 1, Major: 2};
    self.constraints = {
        'mandatory': {
            'OfferToReceiveAudio': true,
            'OfferToReceiveVideo': true
         },
         'optional': 
             [{'RtpDataChannels': true},
             {'DtlsSrtpKeyAgreement': true}
          ]
    };
    self.iceServers = { iceServers: [{url: "turn:165.225.139.11:443", username: "powwie", password: "***"}] };


    // self.shouldUseNgrokServer = true; // whether to use the ngrok dev server for protobuf + api
    // self.launchWithSignup = true; // whether LoginView should show signup page
    // self.shouldShowWelcomeView = true; // show welcome view as if it's the user's first launch
    self.useFakeXmppServer = true; // use this file!
    self.timeToSignIn = 1000; // how long the cancel spinner is visible for
    self.timeToSignOut = 1000; // how long the server takes to disconnect and say we have disconnected
    self.timeToLoadBuddies = 100; // how long the buddy list takes to load
    self.timeToCreateAccount = 500; // how long the sign up spinner is visible for
    self.timeToSwitchPresenter = 1000; // how long switch presenter should take
    self.shouldEchoChatMessages = true; // whether we should echo chat messages
    self.timeToAcceptShare = 1500; // how long a buddy takes to accept a share
    self.showIncomingShareInsteadOfChat = false; // hotwire the chat button to show incoming shares instead
    self.zoom = 1; // zoom level for DPI emulation
    self.setZoomDelay = 500; // time to delay set zoom call
    self.updateAvailable = self.UpdateType.None;
    self.shouldLoadSettings = true; // load settings from cookies
    // self.simulateNoBuddies = true; // like it says

    // Utils.shouldShowBorder = true; // set the mac border around the chrome
    // Utils.shouldBlockRightClick = false;

    this.OnLogin = function() {
        // self.LocalJSCall("ShowInvitation", [{name: "J Bond", email: "j@bond.com", bareJid:"j@bond.com", jid: "jid"}]);
        // self.LocalJSCall("ShowDialog", [{uuid: "UUID", tag: 0, title: "Screenhero is now in your status bar", body: "Buddies in the bar woohoo! 2/4", labelArray: ["OK", "Don't Hide"], defaultIndex: 0, shouldhideArray: [1, 0]}]);
        // self.LocalJSCall("ShowIncomingShare", ["J Sherwani"]);
        // self.LocalJSCall("ShowPopup", [{kind:"info", body:"Oh bloody hell!"}]);
        // self.LocalJSCall("ShowPopup", [{kind:"warning", body:"not again!";
        if (self.settings.isSlave) {
            self.sessionId++;
            var isInCall = Object.keys(browserNativeObject.settings.buddyStates).length > 0;
            var shareBuddyJid = "Faraz Khan@xmpp0.powwow.cc";
            self.settings.buddyStates[shareBuddyJid] = BuddyListManager.SharingStatus.Pending;
            self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
            self.LocalJSCall("SetSessionIdToReady", [self.settings.sessionId]);
            self.LocalJSCall("SwitchToSessionStateId", [self.settings.sessionId]);
            self.LocalJSCall("SessionDidStart", [self.settings.sessionType, false]);

            if (!isInCall) {
                var a = a;
                self.LocalJSCall("ShowIncomingShare", [shareBuddyJid, self.settings.sessionType, false]);
            }
            else {
                setTimeout(function() {
                    self.settings.buddyStates[shareBuddyJid] = BuddyListManager.SharingStatus.Sharing;                    
                    self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
                }, self.timeToAcceptShare);
            }
        }
        // self.LocalJSCall("ShowPopup", [{kind:"info", body:"Oh bloody hell!", timeout:0}]);
        // self.LocalJSCall("ShowPopup", [{kind:"success", body:"yay!", timeout:500}]);
        // self.LocalJSCall("ShowPopup", [{kind:"warning", body:"not again!"}]);
        // self.LocalJSCall("ShowPopup", [{kind:"warning", body:"There seem to something happening which is difficult to answer and we need to use this message for it.", timeout:2000}]);
        // BuddyListManager.ToggleShareWithBuddy("Faraz Khan");
        // BuddyList.ShowBusyDialog(Utils.buddyWithSanitizedProfilePic({name: "J Sherwani", bareJID: "J Sherwani");
        // Main.SetLoginState(Main.loginStates.signedOut);
        // Main.UpdateUserStatusReason(Main.loginErrors.networkError);
    }

    this.CallNativeFunction = function(jsonStr) {
        var jsonrpc = jQuery.parseJSON(jsonStr);
        var method = eval("self." + jsonrpc.method);
        if (method)
            method.apply(this, jsonrpc.params);
        else
            console.log("Native->" + jsonrpc.method + "() not implemented in Config.local.js");
    }

    this.LocalJSCall = function(funcName, paramArray) {
        NativeToJSBridge.performJsonRpcWithSource(JSON.stringify(Utils.createJsonRpcObjectFromObject({method:funcName, params: paramArray, id: self.jsRpcID++})), NativeToJSBridge.SourceTypes.Native);
    }

    this.UpdateOptionsManager = function(updateObj) {
        for (var key in updateObj) {
            self.settings[key] = updateObj[key];
        }
    }

    this.LoadBuddies = function () {
        var buddies = [
                {name: "J Sherwani", email: "j@screenhero.com", bareJid: "J Sherwani@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.DoNotDisturb},
                {name: "Dan GoodmanWilson", email: "don@screenhero.com", bareJid: "Don GoodmanWilson@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "Jason DiCioccio", email: "jd@screenhero.com", bareJid: "Jason DiCioccio@xmpp0.powwow.cc", profilePicURL: "", isOnline: false, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "1ason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason DiCioccio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "2ason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason DiCioccio@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "3ason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason DiCiocci2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "4ason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason DiCiocco2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "5ason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason DiCiocio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "6ason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason DiCiocio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "7ason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason DiCiccio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "8ason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason DiCoccio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "9ason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason Diioccio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "Aason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason DCioccio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "Bason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jason iCioccio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "Cason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "JasonDiCioccio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "Dason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jaso DiCioccio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "Eason DiCioccio", email: "JasonDiCioccio@screenhero.com", bareJid: "Jasn DiCioccio2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "Faraz Khan", email: "faraz@screenhero.com", bareJid: "Faraz Khan@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online},
                {name: "Don GoodmanWilson", email: "DonGoodmanWilson@screenhero.com", bareJid: "Don GoodmanWilson2@xmpp0.powwow.cc", profilePicURL: "", isOnline: true, version: BuddyListManager.ra.get("OptionsManager.version"), show: BuddyListManager.JabberStatusShow.Online}
            ];
        if (self.simulateNoBuddies)
            self.LocalJSCall("ShowNoBuddiesView", []);
        else
            self.LocalJSCall("RefreshBuddyList", [buddies]);

        setTimeout(self.OnLogin, 1000);
    }

    this.SimulateBigGroupCall = function() {
        BuddyListManager.ToggleShareWithBuddy(BuddyListManager.ra.get("buddyList.3.bareJid"), BuddyListManager.SessionType.Voice);
        for (var i = 4; i < 10; i++)
            BuddyListManager.AddBuddyToSession(BuddyListManager.ra.get("buddyList."+i+".bareJid"));
    }

    this.SimulateIncomingGroupCall = function() {
        browserNativeObject.LocalJSCall("ResetAllSessionStates", []);
        browserNativeObject.LocalJSCall("SetBuddyStates", [{ "49a019e3f0a74c04a3e4ffae308a19b0@xmpp0.powwow.cc": 1 }, 107202385552048])
        browserNativeObject.LocalJSCall("SetSessionIdToReady", [107202385552048])
        browserNativeObject.LocalJSCall("SwitchToSessionStateId", [107202385552048])
        browserNativeObject.LocalJSCall("SessionDidStart", [2, false])
        browserNativeObject.LocalJSCall("ShowIncomingShare", ["49a019e3f0a74c04a3e4ffae308a19b0@xmpp0.powwow.cc", 2, false])
        browserNativeObject.LocalJSCall("SessionDidStart", [2, false])
        browserNativeObject.LocalJSCall("ScreenShareDidStart", [])
        browserNativeObject.LocalJSCall("SessionDidStart", [2, false])
        browserNativeObject.LocalJSCall("SetBuddyStates", [{ "49a019e3f0a74c04a3e4ffae308a19b0@xmpp0.powwow.cc": 2 }, 107202385552048])
        browserNativeObject.LocalJSCall("SetBuddyStates", [{ "d61bafe260d7dde45fc766ed32c0bfa0@xmpp0.powwow.cc": 2 }, 107202385552048])        
    }

    this.SendChatMessageToBuddy = function (bareJid, msgTxt) {
        if (self.shouldEchoChatMessages)
            self.LocalJSCall("ReceivedChatMessageFromBuddy", [bareJid, "echo: " + msgTxt]);
    }

    this.DoXmppLogin = function () {
        Main.SetLoginState(Main.loginStates.signingIn);
        window.setTimeout(function () {
            if (self.settings.password != "error") {
                if (self.shouldShowWelcomeView)
                    self.LocalJSCall("ShowWelcomeView", []);
                Main.SetLoginState(Main.loginStates.signedIn);
                window.setTimeout(function() {
                    self.LoadBuddies();
                }, self.timeToLoadBuddies);
            }
            else {
                Main.SetLoginState(Main.loginStates.signedOut);
                Main.UpdateUserStatusReason(4);
            }
        }, self.timeToSignIn);
    }

    this.CreateAccountWithInfo = function (name, email, password) {
        window.setTimeout(function () {
            if (password=="error")
                self.LocalJSCall("CreateAccountResponse", [false, "An error occurred."]);
            else {
                self.settings.nickname = name;
                self.settings.username = email;
                self.settings.password = password;
                self.LocalJSCall("CreateAccountResponse", [true]);
            }
        }, self.timeToCreateAccount);
    }

    this.ChangeUserStatus = function (newStatus) {
        setTimeout(function() {
            Main.SetLoginState(newStatus);
        }, self.timeToSignOut);
    }

    this.StartSessionWithBuddies = function (buddyJids, sessionType) {
        if (self.useFakeXmppServer || true) {
            self.settings.sessionType = sessionType;
            self.settings.buddyStates = {};
            buddyJids = buddyJids.map(function(jid) {return jid.split("/")[0]});
            buddyJids.forEach(function(buddyJid) {
                self.settings.buddyStates[buddyJid] = BuddyListManager.SharingStatus.Pending;
            });

            self.LocalJSCall("SwitchToSessionStateId", [self.settings.sessionId]);
            self.LocalJSCall("SetSessionIdToReady", [self.settings.sessionId]);
            self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
            self.LocalJSCall("SessionDidStart", [sessionType, true]);

            setTimeout(function() { 
                //if (Math.random() > 0.5)
                //    self.LocalJSCall("SetPendingSharingBuddies", [[jid], false]);  // test reject
                //else
                    // self.LocalJSCall("SetSessionIdToReady", [self.settings.sessionId]);
                    buddyJids.forEach(function(buddyJid) {
                        self.settings.buddyStates[buddyJid] = BuddyListManager.SharingStatus.Sharing;
                    });
                    self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
            }, self.timeToAcceptShare);
        }
        else {
            self.StartWebRTCCall(buddyJids[0]);
        }
    }

    this.AddBuddyToSession = function(buddyJid) {
        self.settings.sessionId++;
        self.LocalJSCall("SetSessionIdToReady", [self.settings.sessionId]);

        var oldSharingBuddies = Object.keys(self.settings.buddyStates);

        self.settings.buddyStates[buddyJid] = BuddyListManager.SharingStatus.Pending;
        oldSharingBuddies.forEach(function(jid) {self.settings.buddyStates[jid] = BuddyListManager.SharingStatus.Pending; });
        self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
        self.LocalJSCall("SessionDidStart", [self.settings.sessionType, true]);

        self.LocalJSCall("SwitchToSessionStateId", [self.settings.sessionId]);

        oldSharingBuddies.forEach(function(jid) {
            self.settings.buddyStates[jid] = BuddyListManager.SharingStatus.Sharing; 
            // var obj = {};
            // obj[jid] = BuddyListManager.SharingStatus.Sharing;
            // self.LocalJSCall("SetBuddyStates", [obj, self.settings.sessionId]);
        });
        self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);

        self.LocalJSCall("SetSessionIdToReady", [self.settings.sessionId]);

        self.didEnd = false;
        setTimeout(function() { 
            if (!self.didEnd) {
                self.settings.buddyStates[buddyJid] = BuddyListManager.SharingStatus.Sharing;
                self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
            }
        }, self.timeToAcceptShare);
    }

    this.StopShare = function () {
        self.didEnd = true;
        Object.keys(self.settings.buddyStates).forEach(function(buddyJid) {
            self.settings.buddyStates[buddyJid] = BuddyListManager.SharingStatus.None;
            var obj = {};
            obj[buddyJid] = BuddyListManager.SharingStatus.None;
            self.LocalJSCall("SetBuddyStates", [obj, self.settings.sessionId]);
        });
        // self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
        self.LocalJSCall("ResetSessionState", [self.settings.sessionId]);

        self.settings.sessionId--;
        self.LocalJSCall("SetSessionIdToReady", [self.settings.sessionId]);
        Object.keys(self.settings.buddyStates).forEach(function(buddyJid) {
            self.settings.buddyStates[buddyJid] = BuddyListManager.SharingStatus.None;
            // var obj = {};
            // obj[buddyJid] = BuddyListManager.SharingStatus.None;
            // self.LocalJSCall("SetBuddyStates", [obj, self.settings.sessionId]);
        });
        self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
        self.settings.sessionId++;
    }

    this.AcceptShareRequestFromBuddy = function (bareJid) {
        setTimeout(function() {
            self.settings.buddyStates[bareJid] = BuddyListManager.SharingStatus.Sharing;
            self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
            self.LocalJSCall("SessionDidStart", [self.settings.sessionType, false]);
        }, self.timeToAcceptShare);
    }

    this.RejectShareRequestFromBuddy = function (bareJid) {
        self.settings.buddyStates[bareJid] = BuddyListManager.SharingStatus.None;
        self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
    }

    this.LaunchUrlInBrowser = function(url) {
        window.open(url, "_blank");
    }

    this.StartChooseScreen = function() {
        // switch presenter
        setTimeout(function() {
            self.settings.sessionId++;
            self.LocalJSCall("ChangeActiveSessionId", [self.settings.sessionId]);
            self.LocalJSCall("SwitchToSessionStateId", [self.settings.sessionId]);
            self.LocalJSCall("SetSessionIdToReady", [self.settings.sessionId]);
            self.LocalJSCall("SetBuddyStates", [self.settings.buddyStates, self.settings.sessionId]);
            self.LocalJSCall("SessionDidStart", [self.settings.sessionType, true]);
            self.LocalJSCall("ShowPopup", [{body: "You started sharing your screen!", timeout: 5000, kind: "success"}]);
        }, self.timeToSwitchPresenter);
    }

    this.SilentCheckForUpdates = function() {
        if (self.updateAvailable != self.UpdateType.None)
            self.LocalJSCall("UpdateAvailable", [self.updateAvailable == self.UpdateType.Major]);
    }

    this.SignalReadyForLaunch = function () {
        self.LocalJSCall("EnableDebugging", []);
        if (self.shouldLoadSettings)
            self.LoadSettings();
        self.LocalJSCall("InitializeOptionsManager", [self.settings]);
        if (self.launchWithSignup)
            self.LocalJSCall("LaunchWithSignup", [self.settings.nickname, self.settings.username]);
        else
            self.LocalJSCall("LaunchWithSignIn", []);
    }

    this.SaveSettings = function() {
        localStorage.setItem("settings", JSON.stringify(Utils.sanitizedObject(self.settings, {keysToSkip: ["profilePicURL"]})));
    }

    this.LoadSettings = function() {
        var jsonStr = localStorage.getItem("settings");
        if (jsonStr)
            self.settings = JSON.parse(jsonStr);
    }

    this.sendWebRTCMessage = function(msg) {
       self.LocalJSCall("SendSessionMessageToJidOnChannel", [JSON.stringify(msg), self.connectedjid, 3]);
    }

    this.StartWebRTCCall = function(jid) {
        self.connectedjid = jid;
        navigator.webkitGetUserMedia({audio: true, video: {
            mandatory: {},
            optional: []
        }}, function(video_stream) {
              try {
                // Create an webkitRTCPeerConnection via the polyfill (adapter.js).
                self.pc = new webkitRTCPeerConnection(self.iceServers, self.constraints);
                self.pc.onicecandidate = function(event) {
                  if (event.candidate) {
                    self.sendWebRTCMessage({type: 'candidate',
                                 sdpMLineIndex: event.candidate.sdpMLineIndex,
                                 sdpMid: event.candidate.sdpMid,
                                 candidate: event.candidate.candidate});
                  } else {
                    // trace('End of candidates.');
                  }
                };
              } catch (e) {
                console.log('Failed to create PeerConnection, exception: ' + e.message);
                return;
              }
              self.pc.onaddstream = function(event) {
                  // trace('Remote stream added.');
                $("#remoteVideo").css("display", "block");
                  $("#remoteVideo")[0].src = URL.createObjectURL(event.stream);
                  self.remoteStream = event.stream;
                };
            self.pc.addStream(video_stream);
            self.pc.createOffer(self.SetLocalAndSendMessage, function() {}, self.constraints);

          // $("#localVideo")[0].src = URL.createObjectURL(video_stream);
        }, function(e) {
            console.log("error in get user media: " + e);
        });
    }

    this.SetLocalAndSendMessage = function(offer) {
        self.pc.setLocalDescription(offer, function() { console.log("Set local description successfully");}, function() { console.log ("Error setting local desc");});
        self.sendWebRTCMessage(offer);
    }

    this.ReceivedSessionMessageFromJidOnChannel = function(jid, msg, channel) {
        if (msg == "--HELLOLADIES--")
        {
              // self.pc.onremovestream = onRemoteStreamRemoved;
              // self.pc.onsignalingstatechange = onSignalingStateChanged;
              // self.pc.oniceconnectionstatechange = onIceConnectionStateChanged;

            // navigator.webkitGetUserMedia({audio: false, video: {
            //     mandatory: {},
            //     optional: []
            // }}, function(video_stream) {
            //     answerer.addStream(video_stream);
            // }, function(e) {
            //     console.log("error in get user media: " + e);
            // });

            // answerer.onaddstream = function (event) {
            //     $("#buddy-video")[0].src = URL.createObjectURL(event.stream);
            //     $("#buddy-video")[0].play();
            // };

            // answerer.onicecandidate = function (event) {
            //     if (!event || !event.candidate) return;
            //     NativeToJSBridge.SendSessionMessageToJidOnChannel(event.candidate, jid, channel);
            // };
        }
        else if (channel == 3)
        {
            var message = "";
            try
            {
              var message = JSON.parse(msg);
            }
            catch(e)
            {
                console.log("Exception parsing: "+e.toString());
                return;
            }

          if (message.type === 'offer') {
            self.connectedjid = jid;
              try {
                // Create an webkitRTCPeerConnection via the polyfill (adapter.js).
                self.pc = new webkitRTCPeerConnection(self.iceServers, self.constraints);
                self.pc.onicecandidate = function(event) {
                  if (event.candidate) {
                    self.sendWebRTCMessage({type: 'candidate',
                                 sdpMLineIndex: event.candidate.sdpMLineIndex,
                                 sdpMid: event.candidate.sdpMid,
                                 candidate: event.candidate.candidate});
                  } else {
                    // trace('End of candidates.');
                  }
                };
              } catch (e) {
                console.log('Failed to create PeerConnection, exception: ' + e.message);
                return;
              }
              self.pc.onaddstream = function(event) {
                  // trace('Remote stream added.');
                  console.log("On remote stream!");
                $("#remoteVideo").css("display", "block");
                  $("#remoteVideo")[0].src = URL.createObjectURL(event.stream);
                  self.remoteStream = event.stream;
                };

            self.pc.setRemoteDescription(new RTCSessionDescription(message), function(e) 
                {
                 console.log("Successfully set remote description");
                  },
             function(e) { console.log("Error setting remote description: " +e.toString()); });
            navigator.webkitGetUserMedia({audio: true, video: {
                mandatory: {},
                optional: []
            }}, function(video_stream) {
                self.pc.addStream(video_stream);
              self.pc.createAnswer(self.SetLocalAndSendMessage, function(e) { 
                console.log("Error creating answer! :"+e.toString()); 
            }, self.constraints);

              // $("#localVideo")[0].src = URL.createObjectURL(video_stream);
            }, function(e) {
                console.log("error in get user media: " + e);
            });
          } else if (message.type === 'answer') {
            self.pc.setRemoteDescription(new RTCSessionDescription(message), function() {}, function() {});
          } else if (message.type === 'candidate') {
            var candidate = new RTCIceCandidate({sdpMLineIndex: message.sdpMLineIndex,
                                                 candidate: message.candidate,
                                                sdpMid: message.sdpMid});
            // noteIceCandidate('Remote', iceCandidateType(message.candidate));
            self.pc.addIceCandidate(candidate,
                               function(e) { 
                                console.log("Successfully added candidate"); 
                            }, function(e) { 
                                console.log(e);
                                 });
          } else if (message.type === 'bye') {
            // onRemoteHangup();
          }
        }
    }

    self.jsRpcID = 0;
}

$(document).ready(function () {
    if (!Utils.isAwesomium) {
        Utils.useFakeXmppServer = browserNativeObject.useFakeXmppServer;
        NativeToJSBridge.setNativeObject(browserNativeObject);
        if (Utils.shouldShowBorder) {
            $("body").css("background", "black");
            Utils.isAwesomiumMac = true;
        }
        $("video").css("display", "block");
        setTimeout(function() {
            browserNativeObject.LocalJSCall("SetZoom", [browserNativeObject.zoom]);
        }, browserNativeObject.setZoomDelay);

        $(window).focus(function() {
            browserNativeObject.LocalJSCall("MainWindowActivated", [true]);
        });

        $(window).blur(function() {
            browserNativeObject.LocalJSCall("MainWindowActivated", [false]);
        });
    }
    if (browserNativeObject.shouldUseNgrokServer) {
        Utils.apiServerURI = "https://screenhero.ngrok.com";
        Utils.billingServerURI = "http://localhost:4000";
    }
});