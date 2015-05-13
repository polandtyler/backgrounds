var ChatWindow = new function () {
	var self = this;

	this.scrollTimer = null;
	this.delayBeforeScroll = 50;

	this.setTemplate = function (template) {
		if (template)
		{
			self.template = template;
		}
	}

	this.InitializeWithData = function(data) {
		self.ra = new Ractive({
			el: "ChatWindow-container",
			template: self.template,
			noIntro: true,
			data: {
				BuddyListManager: BuddyListManager.ra,
				SessionType: BuddyListManager.SessionType,
				buddyJID: data.buddyJID,
				buddy: BuddyListManager.GetBuddyWithJID(data.buddyJID),
				history: data.chatHistory,
				newMessage: "",
				sanitizeBuddyPic: function (url) { return url ? url : "img/avatar.svg" },
				sanitizeTimestamp: function (ms) {
					var date = new Date(ms);
					var hours = date.getHours();
					var mins = date.getMinutes();
					var ampm = hours >= 12 ? "PM" : "AM";
					hours = hours % 12;
					hours = hours == 0 ? 12 : hours;
					mins = mins < 10 ? "0" + mins : mins;
					return hours + ":" + mins + " " + ampm;
				},
				isMultiLine: function (msg) { 
					return true;
					// return (msg.indexOf("\n")>=0 || ($(".chatwindow-newmessage")[0].scrollHeight > $(".chatwindow-newmessage")[0].clientHeight) || $(".chatwindow-newmessage")[0].clientHeight > 30) && msg.length > 0;
				},
				ResourceManager: ResourceManager,
				allowShare: function() { 
					return self.ra.get("buddy.isOnline") && !self.ra.get("BuddyListManager.sharingBuddy") && !self.ra.get("BuddyListManager.pendingSharingBuddy"); 
				},
				historyIndex: -1,
				cachedNewMessage: "",
				Utils: Utils,
				GetBuddyListWithSharingStateMask: BuddyListManager.GetBuddyListWithSharingStateMask,
				GetBuddyListLengthWithSharingStateMask: BuddyListManager.GetBuddyListLengthWithSharingStateMask,
                GetProfilePicBackgroundStyleForBuddy: BuddyListManager.GetProfilePicBackgroundStyleForBuddy
			}
		});

		self.ra.observe("history", function() {
			self._checkScrollToEnd();
			// setTimeout(function() { prettyPrint(); }, 10);
		});
		self.ra.on("callButtonClicked", function(evt) {
			self.postJSMessageToParent(ChatWindowManager.ChildToParentMessageTypes.CallButtonClicked);
		});
		self.ra.on("shareButtonClicked", function(evt) {
			self.postJSMessageToParent(ChatWindowManager.ChildToParentMessageTypes.ShareButtonClicked);
		});
		self.ra.on("addButtonClicked", function(evt) {
			self.postJSMessageToParent(ChatWindowManager.ChildToParentMessageTypes.AddButtonClicked);
		});
		self.ra.on("endShareButtonClicked", function(evt) {
			self.postJSMessageToParent(ChatWindowManager.ChildToParentMessageTypes.EndShareButtonClicked);
		});
		self.ra.on("shareBuddyVoiceMuteClicked", function(evt) {
			self.postJSMessageToParent(ChatWindowManager.ChildToParentMessageTypes.VoiceMuteButtonClicked);
		});
		self.ra.on("shareBuddyScreenHoldClicked", function(evt) {
			self.postJSMessageToParent(ChatWindowManager.ChildToParentMessageTypes.ScreenHoldButtonClicked);
		});
		self.ra.on("evalCode", function(evt) {
			eval(self.ra.get("evalCode"));
		});
		self.ra.observe("buddy.isOnline", function (newval, oldval) {
			$(".chatwindow-newmessage").prop("disabled", !newval);
			if (newval)
				$(".chatwindow-newmessage").focus();
		});
		self.ra.on("newMessageKeyDown", function(evt) {
			if ((evt.original.keyCode == 38 || evt.original.keyCode == 40) && (evt.original.ctrlKey && !evt.original.altKey && !evt.original.shiftKey && !evt.original.metaKey))
			{
				var isUp = (evt.original.keyCode == 38 ? 1 : -1);
				var messages = self.ra.get("history");
				var historyIndex = self.ra.get("historyIndex");
				if (historyIndex == -1)
					self.ra.set("cachedNewMessage", self.ra.get("newMessage"));
				// if (!(isUp && historyIndex == messages.length - 1))
				evt.original.preventDefault();
				historyIndex = Math.max(-1, Math.min(messages.length - 1, historyIndex + isUp));
				while (historyIndex > -1 && historyIndex < messages.length - 1)
				{
					if (messages[messages.length - 1 - historyIndex].fromMe)
						break;
					historyIndex = Math.max(-1, Math.min(messages.length - 1, historyIndex + isUp));
				}
				if ((historyIndex >= 0 && messages[messages.length - 1 - historyIndex].fromMe) || historyIndex == -1)
				{			
					self.ra.set("historyIndex", historyIndex);
					self.ra.set("newMessage", historyIndex < 0 ? self.ra.get("cachedNewMessage") : messages[messages.length - 1 - historyIndex].msg);
					$(".chatwindow-newmessage")[0].selectionStart = $(".chatwindow-newmessage")[0].selectionEnd = $(".chatwindow-newmessage")[0].value.length;
				}
			}
			else if (evt.original.keyCode == 13 && !evt.original.altKey && !evt.original.metaKey && !evt.original.ctrlKey && !evt.original.shiftKey) {
				self.SendMessage();
				evt.original.preventDefault();	
			}
			// if (self.ra.get("buddyJID") == ChatWindowManager.debuggerWindowJID)
			// {
			// 	if ((evt.original.keyCode == 38 || evt.original.keyCode == 40) && (!evt.original.ctrlKey && !evt.original.altKey && !evt.original.shiftKey && !evt.original.metaKey))
			// 	{
			// 		var messages = self.ra.get("history");
			// 		if (self.ra.get("historyIndex") == -1)
			// 			self.ra.set("cachedNewMessage", self.ra.get("newMessage"));
			// 		var historyIndex = self.ra.get("historyIndex") + (evt.original.keyCode == 38?2:-2);
			// 		historyIndex = Math.max(-1, Math.min(messages.length - 1, historyIndex));
			// 		self.ra.set("historyIndex", historyIndex);
			// 		self.ra.set("newMessage", historyIndex < 0 ? self.ra.get("cachedNewMessage") : messages[messages.length - 1 - historyIndex].msg);
			// 		$(".chatwindow-newmessage")[0].selectionStart = $(".chatwindow-newmessage")[0].selectionEnd = $(".chatwindow-newmessage")[0].value.length;
			// 		return false;
			// 	}
			// }
		});
		
		BuddyList.ObserveTooltipChanges(self.ra);
		
		self._doScrollToEnd();
		self._updateBuddyListManagerData(data.buddyListManagerData);
		$(".chatwindow-newmessage").focus();
		$("#ChatWindow-container").css("width", "100%");
		$("#ChatWindow-container").mouseup(function() {
			setTimeout(function() {
				if (document.getSelection().type!="Range")
					$(".chatwindow-newmessage").focus();
			}, 10);
		});

		window.addEventListener("dragover",function(e) {
		  e = e || event;
		  e.preventDefault();
		}, false);
		window.addEventListener("drop",function(e) {
		  e = e || event;
		  e.preventDefault();
		}, false);

	}

	this.postJSMessageToParent = function (type, postedData) {
		var data = {};
		data.postedData = postedData;
		data.windowType = WindowManager.WindowTypes.ChatWindow;
		data.messageType = type;
		if (self.ra)
			data.bareJid = self.ra.get("buddy.bareJid");
		opener.postMessage(data, "*");
	}

	this.Log = function (txt) {
		self.postJSMessageToParent("Log", {logText: txt});
	}

	this.SignalReadyForLaunch = function () {
		window.addEventListener("message", self._receivePostedJSMessageFromParent, false);
		self.postJSMessageToParent(ChatWindowManager.ChildToParentMessageTypes.ChatWindowDidLaunch);
	}

	this.SendMessage = function() {
		var msgTxt = self.ra.get("newMessage") + "";
		if (msgTxt.length > 0) {	
			self.AddMessageToHistory(new ChatHistoryManager.ChatMessageModel(msgTxt, $.now(), true));
			self.postJSMessageToParent(ChatWindowManager.ChildToParentMessageTypes.SendChatMessageToBuddy, msgTxt);
			self.ra.set("newMessage", "");
			self.ra.set("cachedNewMessage", "");
			self.ra.set("historyIndex", -1);
		}
	}

	this.UserRequestedUrl = function(url) {
		self.postJSMessageToParent("UserRequestedUrl", {url: url});		
	}

	this.ReceivedChatMessageFromBuddy = function(msgTxt) {
		self.AddMessageToHistory(new ChatHistoryManager.ChatMessageModel(msgTxt, $.now(), false));
	}

	this.AddMessageToHistory = function(msgModel) {
		self.ra.get("history").push(msgModel);
	}

	this._updateBuddyListManagerData = function(newBLMdata) {
		for (var key in newBLMdata) {
			self.ra.set("BuddyListManager."+key, newBLMdata[key]);
		}
		var buddy = BuddyListManager.GetBuddyWithJID(self.ra.get("buddyJID"));
		if (buddy)
		{
			self.ra.set("buddy", buddy);
			document.title = "Chat with " + self.ra.get("buddy.name");
		}
		else // buddy has gone
		{
			if (self.ra.get("buddy"))
				self.ra.set("buddy.isOnline", false);
		}
	}

    this._receivePostedJSMessageFromParent = function (event) {
        if (event.data.messageType == ChatWindowManager.ParentToChildMessageTypes.ReceivedChatMessageFromBuddy)
            self.ReceivedChatMessageFromBuddy(event.data.postedData);
        else if (event.data.messageType == ChatWindowManager.ParentToChildMessageTypes.InitializeWithData)
        	self.InitializeWithData(event.data.postedData);
        else if (event.data.messageType == ChatWindowManager.ParentToChildMessageTypes.BuddyListManagerDataChanged)
        	self._updateBuddyListManagerData(event.data.postedData);
        else if (event.data.messageType == ChatWindowManager.ParentToChildMessageTypes.FocusWindow)
        	self._focusWindow();
        else if (event.data.messageType == ChatWindowManager.ParentToChildMessageTypes.BounceDockIcon)
        	self._bounceDockIcon();
        else
            console.log("ChatWindow: couldn't find method " + event.data.messageType);
    }

    this._focusWindow = function() {
    	if (Utils.isAwesomium) {
	    	if (window.nativeChildWindowController)
	    		nativeChildWindowController.Focus();
    	}
    	else
    		window.focus();

    	$(".chatwindow-newmessage").focus();  // focus input text field    	
    }

    this._bounceDockIcon = function() {
    	if (Utils.isAwesomium) {
    		if (window.nativeChildWindowController)
    			nativeChildWindowController.BounceDockIcon();
    	}
    }

    this._checkScrollToEnd = function() {
    	var differential = $(".chatwindow-history").scrollTop() == ($(".chatwindow-history")[0].scrollHeight - $(".chatwindow-history").height());
    	if (Math.abs(differential) < 5)
	    	self._doScrollToEnd();
    }

    this._doScrollToEnd = function() {
    	if (self.scrollTimer)
    		clearTimeout(self.scrollTimer);
    	self.scrollTimer = setTimeout(function() {
	    	$(".chatwindow-history").animate({scrollTop:$(".chatwindow-history")[0].scrollHeight}, 100);    		
    	}, self.delayBeforeScroll);
    }

}
