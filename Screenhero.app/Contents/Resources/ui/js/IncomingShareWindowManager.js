var IncomingShareWindowManager = new function () {
    var self = this;

    this.ParentToChildMessageTypes = {
        InitializeWithData: "InitializeWithData",
        CloseWindow: "CloseWindow"
    };

    this.ChildToParentMessageTypes = {
        IncomingShareWindowDidLaunch: "IncomingShareWindowDidLaunch",
        UserRespondedToShareRequest: "UserRespondedToShareRequest",
        Log: "Log"
    };

    this._incomingShareWindowDict = {};
    this._pendingIncomingShareWindowDict = {};
    this.OpenIncomingShareWindowForBuddy = function (bareJid, shareType) {
        var incomingShareWindow = self._getIncomingShareWindowForJID(bareJid);
        if (incomingShareWindow && incomingShareWindow.closed)
        {
            //shouldn't get here, since this case is checked in _getIncomingShareWindowForJID
        }
        if (incomingShareWindow) {
            console.log("incoming share window found");
            console.log("incoming share window is closed: " + incomingShareWindow.closed);
            //TODO (j) test this in mac/win
            incomingShareWindow.focus();
        }
        else { 
            var incomingShareWindowObj = self._pendingIncomingShareWindowDict[bareJid];
            if (incomingShareWindowObj) {
                // do nothing since it's being made
            }
            else {
                //create it
                console.log("incoming share window not found, creating...");
                var url = "index.htm?launchModuleName=IncomingShareWindow";
                url += "&hasBorder=0";
                url += "&shouldCenter=1";
                url += "&width=260";
                url += "&height=400";
                url += "&alwaysOnTop=1";
                url += "&shouldFocus=1";

                incomingShareWindow = window.open(url);
                if (!incomingShareWindow)
                    console.log("couldn't create incomingShareWindow for " + bareJid);
                else
                    self._pendingIncomingShareWindowDict[bareJid] = {window: incomingShareWindow, shareType: shareType};
            }
        }
    }

    this.CloseIncomingShareWindowForBuddy = function (bareJid) {
        var incomingShareWindow = self._getIncomingShareWindowForJID(bareJid);
        if (incomingShareWindow)
            incomingShareWindow.close();
        self._incomingShareWindowDict[bareJid] = undefined;
    }

    this.postJSMessageToIncomingShareWindowWithJID = function(bareJid, messageType, postedData) {
        var incomingShareWindow = self._getIncomingShareWindowForJID(bareJid);
        if (incomingShareWindow)
        {        
            var data = {};
            data.windowType = WindowManager.WindowTypes.IncomingShareWindow;
            data.messageType = messageType;
            data.postedData = postedData;
            incomingShareWindow.postMessage(data, "*");
        }
    }
    
    // this comes in via WindowManager
    this.ReceivePostedJSMessageFromChild = function (event) {
        if (event.data.messageType==self.ChildToParentMessageTypes.UserRespondedToShareRequest)
            BuddyListManager.UserRespondedToShareRequest(event.data.bareJid, event.data.postedData.didAccept);
        else if (event.data.messageType==self.ChildToParentMessageTypes.IncomingShareWindowDidLaunch)
            self.incomingShareWindowDidLaunch(event)
        else if (event.data.messageType==self.ChildToParentMessageTypes.Log)
            console.log("IncomingShareWindow: " + event.data.postedData.logText);
        else
            console.log("Couldn't find method " + event.data.messageType);
    }

    this.incomingShareWindowDidLaunch = function(event) {
        var incomingShareWindow = event.source;
        var bareJid = undefined;
        var shareType = BuddyListManager.SessionType.None;
        for (var tempjid in self._pendingIncomingShareWindowDict) {
            if (self._pendingIncomingShareWindowDict[tempjid].window == incomingShareWindow) {
                bareJid = tempjid;
                shareType = self._pendingIncomingShareWindowDict[tempjid].shareType;
            }
        }

        if (!bareJid) {
            for (var tempjid in self._incomingShareWindowDict)
                if (self._incomingShareWindowDict[tempjid] == incomingShareWindow)
                    bareJid = tempjid;
        }

        if (bareJid) {
            self._incomingShareWindowDict[bareJid] = incomingShareWindow;
            delete self._pendingIncomingShareWindowDict[bareJid];

            BuddyListManager.GetBuddyWithJID(bareJid, function(buddy) {
                self._incomingShareWindowDidLaunch(buddy, shareType);
            });
        }
    }

    this._incomingShareWindowDidLaunch = function(buddy, shareType) {
        console.log("_incomingShareWindowDidLaunch: buddy=" + buddy.bareJid);
        var data = {};
        data.buddy = buddy;
        data.shareType = shareType;
        self.postJSMessageToIncomingShareWindowWithJID(buddy.bareJid, self.ParentToChildMessageTypes.InitializeWithData, data);
    }

    this._getIncomingShareWindowForJID = function(bareJid) {
        var incomingShareWindow = self._incomingShareWindowDict[bareJid];
        if (incomingShareWindow && incomingShareWindow.closed)
        {
            console.log("incomingShareWindow was closed for jid: " + bareJid);
        	self._incomingShareWindowDict[bareJid] = undefined;
	        return undefined;
        }
        else
        	return incomingShareWindow;
    }
}