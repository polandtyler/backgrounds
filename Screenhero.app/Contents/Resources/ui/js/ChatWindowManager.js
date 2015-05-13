var ChatWindowManager = new function () {
    var self = this;

    this.debuggerWindowJID = "debuggerWindowJID";

    this.ParentToChildMessageTypes = {
        BuddyListManagerDataChanged: "BuddyListManagerDataChanged",
        ReceivedChatMessageFromBuddy: "ReceivedChatMessageFromBuddy",
        InitializeWithData: "InitializeWithData",
        FocusWindow: "FocusWindow"
    };

    this.ChildToParentMessageTypes = {
        SendChatMessageToBuddy: "SendChatMessageToBuddy",
        ChatWindowDidLaunch: "ChatWindowDidLaunch",
        ShareButtonClicked: "ShareButtonClicked",
        AddButtonClicked: "AddButtonClicked",        
        CallButtonClicked: "CallButtonClicked",
        EndShareButtonClicked: "EndShareButtonClicked",
        ScreenHoldButtonClicked: "ScreenHoldButtonClicked",
        VoiceMuteButtonClicked: "VoiceMuteButtonClicked",
        UserRequestedUrl: "UserRequestedUrl",
        Log: "Log"
    };

    this.NumberOfOpenChatWindows = function() {
        this.pruneDeadChatWindows();
        return Object.keys(this._chatWindowDict).length + Object.keys(this._pendingChatWindowDict).length;
    }

    this.pruneDeadChatWindows = function() {
        var jids = Object.keys(this._chatWindowDict);
        for (var i = 0; i < jids.length; i++) {
            this._getChatWindowForJID(jids[i]);
        }
    }

    this.Initialize = function() {
        self.ra = new Ractive({
            data: {
                BuddyListManager: BuddyListManager.ra
            }
        });

        self.ra.on("change", function() {
            for (var bareJid in self._chatWindowDict) {
                self._updateChatWindowBuddyListManagerData(bareJid);
            };
        });
    }

    this._chatWindowDict = {};
    this._pendingChatWindowDict = {};
    this.OpenChatWindowForBuddy = function (bareJid, notifyOnLaunch) {
        var chatWindow = self._getChatWindowForJID(bareJid);
        if (chatWindow && chatWindow.closed)
        {

        }
        if (chatWindow) {
            console.log("chat window found");
            console.log("chat window is closed: " + chatWindow.closed);
            self.postJSMessageToChatWindowWithJID(bareJid, self.ParentToChildMessageTypes.FocusWindow);
        }
        else { 
            chatWindow = self._pendingChatWindowDict[bareJid];
            if (chatWindow) {
                // do nothing since it's being made
            }
            else {
                //create it
                console.log("chat window not found, creating...");

                var url = "index.htm?launchModuleName=ChatWindow";
                url += "&hasBorder=1";
                url += "&shouldCenter=0";
                url += "&minWidth=315";
                url += "&minHeight=150";
                url += "&width=400";
                url += "&height=300";
                url += "&alwaysOnTop=0";
                url += "&shouldFocus=" + (notifyOnLaunch ? "0" : "1");

                chatWindow = window.open(url);

                if (chatWindow)
                {
                    chatWindow.addEventListener("focus", self._handleChatWindowGotFocus, false);
                    self._pendingChatWindowDict[bareJid] = {window: chatWindow, notifyOnLaunch: notifyOnLaunch};
                    //JSToNativeBridge.CallNativeFunction("BringAppToFront");  // make sure native app is brought to front so that window always shows after open
                }
                else
                    console.log("couldn't create chatWindow for " + bareJid);
            }
        }
    }

    this.postJSMessageToChatWindowWithJID = function(bareJid, messageType, postedData) {
        var chatWindow = self._getChatWindowForJID(bareJid);
        if (chatWindow)
        {        
            var data = {};
            data.windowType = WindowManager.WindowTypes.ChatWindow;
            data.messageType = messageType;
            data.postedData = postedData;
            chatWindow.postMessage(data, "*");
        }
    }
    
    // this comes in via WindowManager
    this.ReceivePostedJSMessageFromChild = function (event) {
        if (event.data.messageType==self.ChildToParentMessageTypes.SendChatMessageToBuddy)
            self.SendChatMessageToBuddy(event.data);
        else if (event.data.messageType==self.ChildToParentMessageTypes.ChatWindowDidLaunch)
            self.chatWindowDidLaunch(event);
        else if (event.data.messageType==self.ChildToParentMessageTypes.ShareButtonClicked)
            BuddyListManager.ToggleShareWithBuddy(event.data.bareJid, BuddyListManager.SessionType.Screen);
        else if (event.data.messageType==self.ChildToParentMessageTypes.AddButtonClicked)
            BuddyListManager.AddBuddyToSession(event.data.bareJid);
        else if (event.data.messageType==self.ChildToParentMessageTypes.CallButtonClicked)
            BuddyListManager.ToggleShareWithBuddy(event.data.bareJid, BuddyListManager.SessionType.Voice);
        else if (event.data.messageType==self.ChildToParentMessageTypes.EndShareButtonClicked)
            JSToNativeBridge.CallNativeFunction("StopShare");
        else if (event.data.messageType==self.ChildToParentMessageTypes.VoiceMuteButtonClicked)
            BuddyListManager.ToggleVoiceChatMute();
        else if (event.data.messageType==self.ChildToParentMessageTypes.UserRequestedUrl)
            JSToNativeBridge.CallNativeFunction("LaunchUrlInBrowser", event.data.postedData.url);
        else if (event.data.messageType==self.ChildToParentMessageTypes.ScreenHoldButtonClicked)
            BuddyListManager.ToggleScreenShareMute();            
        else if (event.data.messageType==self.ChildToParentMessageTypes.Log)
            console.log("ChildWindow: " + event.data.postedData.logText);
        else
            console.log("ChatWindowManager: Couldn't find method " + event.data.messageType);
    }

    this.SendChatMessageToBuddy = function(obj) {
        if (obj.bareJid != self.debuggerWindowJID) {
            var bareJid = obj.bareJid;
            var msgTxt = obj.postedData + "";
            var chatHistory = ChatHistoryManager.GetChatHistoryForBuddy(bareJid)
            chatHistory.push(new ChatHistoryManager.ChatMessageModel(msgTxt, $.now(), true));
            XmppManager.SendChatMessageToBuddy(bareJid, msgTxt);
        }
        else {
            var evalOutput = "";
            var js = obj.postedData;
            js = js.replace(/”/g, "\"");
            js = js.replace(/“/g, "\"");
            js = js.replace(/‘/g, "\'");
            js = js.replace(/’/g, "\'");
            try {
                evalOutput = eval(js) + "";
            }
            catch (err)
            {
                evalOutput = "Error: " + err;
            }
            // if (typeof evalOutput == "object")
            //     evalOutput = Utils.stringify(evalOutput);
            self.ReceivedChatMessageFromBuddy(obj.bareJid, evalOutput);
        }
    }

    this.ReceivedChatMessageFromBuddy = function(bareJid, message) {
        var chatHistory = ChatHistoryManager.GetChatHistoryForBuddy(bareJid)
        chatHistory.push(new ChatHistoryManager.ChatMessageModel(message, $.now(), false));

        if (Utils.isDebuggingEnabled) {
            if (message.indexOf("callmee") == 0)
            {
                BuddyListManager.ToggleShareWithBuddy(bareJid, BuddyListManager.SessionType.Screen);
                return;
            }
            else if (message == "callmemaybe")
            {
                var responseArr = ["k", "you got it, buddy", "sure thing", "just a sec", "ummm k",
                                    "sorry", "i'm busy", "not now", "no", "go away"];
                var rnd = Math.floor(Math.random() * 10);
                if (rnd < 5)
                    BuddyListManager.ToggleShareWithBuddy(bareJid, BuddyListManager.SessionType.Screen);
                XmppManager.SendChatMessageToBuddy(bareJid, responseArr[rnd]);
                return;
            }
            else if (message.indexOf("js:")==0) 
            {
                XmppManager.SendChatMessageToBuddy(bareJid, eval(message.substring(3))+"");
                return;
            }
        }

        // The rules when receiving a message:
        // 1) if window is not showing, show it
        // 2) if window is showing and in front just post the chat msg.  if not in front, don't bring it to front and do the following:
        // a) show growl/notification center/system tray bubble message. if click, open chat window.
        // b) bounce/flash dock icon
        // c) play sound
        // d) show unread message count in buddy list
        var chatWindow = self._getChatWindowForJID(bareJid);
        if (chatWindow) 
        {
            self.postJSMessageToChatWindowWithJID(bareJid, self.ParentToChildMessageTypes.ReceivedChatMessageFromBuddy, message);

            if (!chatWindow.document.hasFocus())  // don't show notifications if user is already focused in chat window
                self._showNotificationsForChatMessage(bareJid, message);
        }
        else if (!self._pendingChatWindowDict[bareJid])
        {
            self.OpenChatWindowForBuddy(bareJid, true);
        }

        // note the coolness of this -- if we just opened a chat window, we don't need to worry about
        // sending the new window this current message since it's appended to the chat history,
        // which will be sent over once the new window launches and is initialized!

        UpdateManager.EventOccurred();
    }

    this._showNotificationsForChatMessage = function(bareJid, msgTxt) {
        JSToNativeBridge.CallNativeFunction("ShowSystemNotification", bareJid, msgTxt);  // show growl/Notification Center/whatever-on-windows

        JSToNativeBridge.CallNativeFunction("BounceDockIcon");  // bounce (on mac)
        self.postJSMessageToChatWindowWithJID(bareJid, self.ParentToChildMessageTypes.BounceDockIcon);  // or flash (on windows)

        JSToNativeBridge.CallNativeFunction("IncrementDockIconBadgeForBuddy", bareJid);  // increment dock icon badge (if relevant on native OS)
        ChatHistoryManager.IncrementUnreadMessageCountForBuddy(bareJid);

        ResourceManager.playSound("chat.wav");
    }

    this.ShowChatWindowForBuddy = function(bareJid) {
        var chatWindow = self._getChatWindowForJID(bareJid);
        if (!chatWindow)
            self.OpenChatWindowForBuddy(bareJid);
        else
        {
//            chatWindow.focus();
            self.postJSMessageToChatWindowWithJID(bareJid, self.ParentToChildMessageTypes.FocusWindow);
        }
    }

    this._handleChatWindowGotFocus = function(event) {
        var chatWindow = event.target;
        var bareJid = self._getJIDForChatWindow(chatWindow);
        if (bareJid) {
            JSToNativeBridge.CallNativeFunction("DecrementDockIconBadgeForBuddy", bareJid);
            ChatHistoryManager.ResetUnreadMessageCount(bareJid);
        }
    }

    this.chatWindowDidLaunch = function(event) {
        var chatWindow = event.source;
        var bareJid = undefined;
        var notifyOnLaunch = false;
        for (var tempjid in self._pendingChatWindowDict) {
            if (self._pendingChatWindowDict[tempjid].window == chatWindow) {
                bareJid = tempjid;
                notifyOnLaunch = self._pendingChatWindowDict[tempjid].notifyOnLaunch;
            }
        }
        if (!bareJid) {
            for (var tempjid in self._chatWindowDict)
                if (self._chatWindowDict[tempjid] == chatWindow)
                    bareJid = tempjid;
        }
        if (bareJid) {
            console.log("chatWindow did launch for bareJid: " + bareJid);
            self._chatWindowDict[bareJid] = chatWindow;
            delete self._pendingChatWindowDict[bareJid];
            var data = {};
            data.buddyJID = bareJid;
            data.chatHistory = ChatHistoryManager.GetChatHistoryForBuddy(bareJid);
            self.postJSMessageToChatWindowWithJID(bareJid, self.ParentToChildMessageTypes.InitializeWithData, data);
            self._updateChatWindowBuddyListManagerData(bareJid);
            if (notifyOnLaunch)
                self._showNotificationsForChatMessage(bareJid, data.chatHistory[data.chatHistory.length-1].msg);
        }
    }
    this._updateChatWindowBuddyListManagerData = function(bareJid) {
        var rawdata = self.ra.get("BuddyListManager").data;
        var data = {};
        for (var key in rawdata)
            if (typeof rawdata[key] != "function")
                data[key] = rawdata[key];
        self.postJSMessageToChatWindowWithJID(bareJid, self.ParentToChildMessageTypes.BuddyListManagerDataChanged, data);
    }
    this._getChatWindowForJID = function(bareJid) {
        var chatWindow = self._chatWindowDict[bareJid];
        if (chatWindow && chatWindow.closed)
        {
            console.log("chatWindow was closed for jid: " + bareJid);
        	delete self._chatWindowDict[bareJid];
            UpdateManager.EventOccurred();
	        return undefined;
        }
        else
        	return chatWindow;
    }

    this._getJIDForChatWindow = function(chatWindow) {
        for (var jid_iter in self._chatWindowDict)
            if (self._chatWindowDict[jid_iter] == chatWindow)
                return jid_iter;

        return undefined;
    }
}