var IncomingShareWindow = new function () {
	var self = this;

	this.setTemplate = function (template) {
		if (template)
		{
			self.template = template;
		}
	}

	this.InitializeWithData = function(data) {
		self.ra = new Ractive({
			el: "IncomingShareWindow-container",
			template: self.template,
			noIntro: true,
			data: {
				buddy: data.buddy,
				shareType: data.shareType,
				SessionTypes: BuddyListManager.SessionType,
				ResourceManager: ResourceManager,
				GetProfilePicBackgroundStyleForBuddy: BuddyListManager.GetProfilePicBackgroundStyleForBuddy
			}
		});

		self.ra.on("userRespondedToShareRequest", function(event) {
			console.log("userRespondedToShareRequest");
			self.UserRespondedToShareRequest(event.node.getAttribute("data-action")=="accept");
		});

		self.ra.on("onkeydown", function(event) { 
			if (event.original.keyCode == 27) {
				self.UserRespondedToShareRequest(false);
			}
		});
		document.title = "Incoming call from " + self.ra.get("buddy.name");
		$("#focusbutton").focus();
	}

	this.UserRespondedToShareRequest = function(didAccept) {
		$("#focusbutton").prop("disabled", true);
		$("#ignorebutton").prop("disabled", true);
		self.postJSMessageToParent(IncomingShareWindowManager.ChildToParentMessageTypes.UserRespondedToShareRequest, {didAccept: didAccept});
		if (Utils.isAwesomium) {
			if (window.nativeChildWindowController)
				nativeChildWindowController.CloseMe();
		}
		else // chrome
			window.close();
	}

	this.postJSMessageToParent = function (type, postedData) {
		var data = {};
		data.postedData = postedData;
		data.messageType = type;
		data.windowType = WindowManager.WindowTypes.IncomingShareWindow;
		if (self.ra)
			data.bareJid = self.ra.get("buddy.bareJid");
		opener.postMessage(data, "*");
	}

	this.Log = function (txt) {
		self.postJSMessageToParent("Log", {logText: txt});
	}

	this.SignalReadyForLaunch = function () {
		window.addEventListener("message", self._receivePostedJSMessageFromParent, false);
		self.postJSMessageToParent(IncomingShareWindowManager.ChildToParentMessageTypes.IncomingShareWindowDidLaunch);
	}

    this._receivePostedJSMessageFromParent = function (event) {
		if (event.data.messageType == IncomingShareWindowManager.ParentToChildMessageTypes.InitializeWithData)
        	self.InitializeWithData(event.data.postedData);
        else
            console.log("Couldn't find method " + event.data.messageType);
    }
}
