var Main = new function () {
	var self = this;

	this.loginStates = {
		signedOut: 0,
		signedIn: 1,
		signingIn: 2,
		signingOut: 3,
		signedOutAndReconnecting: 4
	};

	this.loginErrors = {
	    success: 0,
	    networkError: 1,
	    XMPPError: 2,
	    badUsername: 3,
	    badPassword: 4,
	    unknownError: 5,
	    reconnectIn1: 6,
	    reconnectIn2: 7,
	    reconnectIn3: 8,
	    reconnectIn4: 9,
	    reconnectIn5: 10,
	    signedInElsewhere: 11,
	    noInternet: 12
	};

	this.loginErrorText = [
        "",
        "A network error occurred.",
        "A server error occurred.",
        "Invalid email.",
        "Incorrect password.",
        "An unknown error occurred.",
        "Reconnecting in 1 second...",
        "Reconnecting in 2 seconds...",
        "Reconnecting in 3 seconds...",
        "Reconnecting in 4 seconds...",
        "Reconnecting in 5 seconds...",
        "You've signed in at another location.",
        "Your Internet connection is disconnected."
	];

	this.setTemplate = function (template) {
		if (template)
		{
			self.template = template;
		}
	}

	this.HandleStatusReason = function (statusReason) {
        LoginView.ShowErrorReason(statusReason);
	}

	this.ShowWelcomeView = function()
	{
		// TODO
		self.ra.set("shouldShowWelcomeView", true);
	}

	this.Initialize = function () {
        self.ra = new Ractive({
			el: "Main-container",
			template: self.template,
			noIntro: true,
            data: {
				loginState: self.loginStates.signedOut,
				loginStates: self.loginStates,
				shouldShowWelcomeView: false,
            	BuddyListManager: BuddyListManager.ra,
            	ResourceManager: ResourceManager,
		    	Utils: Utils
            }
        });

        self.ra.observe("loginState", function (newState, oldState) {
			if (newState == self.loginStates.signedIn)
				LoginView.ResetFormState();
			if (newState == self.loginStates.signedOut)
		        BuddyListManager.ra.set("lastSignedInEmail", BuddyListManager.ra.get("OptionsManager.buddyThatIsMe.email"));
        });
	}

	this.SetLoginState = function (newState) {
		self.ra.set("loginState", newState);
		JSToNativeBridge.CallNativeFunction("LoginStateChanged", newState);
	}

    this.GetLoginState = function () {
        if(self.ra.get("loginState"))
            return self.ra.get("loginState");
        else
            return self.loginStates.signedOut;
    }

    this.MainWindowActivated = function (isActive) {
        UpdateManager.MainWindowActivated(isActive);
        if (!isActive)
        	$(".dropdown").dropdown('toggle');
    }


	this.ShowDropdownForEvent = function (dropdown, evt, containerID) {
    	console.log("evt: ("+evt.x+", " + evt.y+"), orig: ("+evt.original.x+", " + evt.original.y+")");
        var offset = { left: evt.x, top: evt.y };
        if (offset.left == undefined)
            offset = { left: evt.original.x, top: evt.original.y };
        if (!(evt.original.button == 0 && !evt.original.ctrlKey)) { // hide if it wasn't a click
	        $(dropdown).parent().removeClass('open');
		}
    	evt.original.cancelBubble = true;
        $(dropdown).dropdown('toggle');
        offset.left = Math.min(offset.left / $("body").css("zoom"), $(containerID).width() - $(dropdown).siblings(0).width() - 5);
        offset.top = Math.min(offset.top / $("body").css("zoom"), $(containerID).height() - $(dropdown).siblings(0).height() - 25);
        $(dropdown).parent().parent().css(offset);
    	console.log("evt: ("+evt.x+", " + evt.y+"), orig: ("+evt.original.x+", " + evt.original.y+"), offset: ("+offset.left+", " + offset.top+")");
	}
}
