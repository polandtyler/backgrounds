var LoginView = new function () {
	var self = this;

	self.connectionTimeout = 5 * 1000;
    self.connectionAttempt = 0;

	this.setTemplate = function (template) {
		if (template)
		{
			self.template = template;
		}
	}

	this.LaunchWithSignIn = function ()
	{
		self.ra.set("didReceiveLaunchSignalFromNative", true);
		var email = self.ra.get("BuddyListManager.OptionsManager.buddyThatIsMe.email");
		var password = self.ra.get("BuddyListManager.OptionsManager.password");
		var shouldSavePassword = self.ra.get("BuddyListManager.OptionsManager.shouldRememberPassword");
		email = email === undefined ? "" : email;
		password = password === undefined ? "" : password;

		self.ra.set("signInEmail", email);
		self.ra.set("signInPassword", password);
		self.ra.set("signInShouldSavePassword", shouldSavePassword);

		if (!self.isEmailValid(email))
			$(".signInEmail").focus();
		else if (!self.isPasswordValid(password))
			$(".signInPassword").focus();
		else if (shouldSavePassword) {
			self.ToggleSignIn();
		}
		else
			$(".signInButton").focus();
	}

	this.LaunchWithSignup = function (name, email)
	{
		self.ra.set("didReceiveLaunchSignalFromNative", true);
		name = name === undefined ? "" : name;
		email = email === undefined ? "" : email;
		self.ra.set("signUpName", name);
		self.ra.set("signUpEmail", email);
		self.ra.set("shouldShowSignUpForm", true, function() {
			if (!self.isNameValid(name))
				$(".signUpName").focus();
			else if (!self.isEmailValid(email))
				$(".signUpEmail").focus();
			else
				$(".signUpPassword").focus();
		});
	}

	this.ShowErrorReason = function (errorReason) {
	    self.ra.set("isCreatingAccount", false);
	    self.ra.set("shouldShowSignUpForm", false);
		self.ra.set("errorText", Main.loginErrorText[errorReason]);
		if (errorReason == Main.loginErrors.badPassword) {
			$(".signInPassword").select();
			$(".signInPassword").focus();
		}
	}

	this.CreateAccountResponse = function (didSucceed, errorText) {
	    if (didSucceed) {
	        self.ra.set("signInEmail", self.ra.get("signUpEmail"));
	        self.ra.set("signInPassword", self.ra.get("signUpPassword"));
            if (self.ra.get("shouldShowSignUpForm"))
                self.ra.fire('toggleSignUpFormClicked');
	        self.ToggleSignIn();
	    }
	    else {
		    self.ra.set("isCreatingAccount", false);
	        self.ra.set("signUpError", errorText);	        	
	    }
	}

	this.Initialize = function() {
		self.ra = new Ractive({
			el: "LoginView-container",
			template: self.template,
			// noIntro: true,
			data: {
				signInEmail: "", 
				signInPassword: "", 
				signInShouldSavePassword: true,
				Main: Main.ra,
				BuddyListManager: BuddyListManager.ra,
				shouldShowSignUpForm: false,
				errorText: "",
				signUpName: "",
				signUpEmail: "",
				signUpPassword: "",
                signUpError: "",
                isCreatingAccount: false,
				ResourceManager: ResourceManager,
				Utils: Utils,
				firstEmailEntryComplete: false,
				firstPasswordEntryComplete: false,
				isEmailValid: self.isEmailValid,
				isPasswordValid: self.isPasswordValid,
				footerInitialized: false,
				reconnectTimer: 0,
				didReceiveLaunchSignalFromNative: false,
				isReachable: undefined,
                isLoggingIn: self.IsLoggingIn
			}
		});
		self.ra.observe('isReachable', function (newVal, oldVal) {
			if (oldVal === undefined)
				return;

			if (newVal && !oldVal) {
				// connected
				self.clearLoginStates();
				self.doSignIn();
			}
			else if (oldVal && !newVal) {
				// disconnected
				self.clearLoginStates();
				self.doSignOut();
			}
		});

		self.ra.on('toggleSignUpFormClicked', function (event) {
			self.ra.set("footerInitialized", true);
			if (!self.ra.get("shouldShowSignUpForm")) {
				//initialize it
				self.ra.set("signUpName", "");
				self.ra.set("signUpEmail", "");
				self.ra.set("signUpPassword", "");
		        self.ra.set("signUpError", "");
			}
			self.ra.set("shouldShowSignUpForm", !self.ra.get("shouldShowSignUpForm"), function () {
				if (self.ra.get("shouldShowSignUpForm"))
					$(".signUpName").focus();
			});
		});
		self.ra.observe("shouldShowSignUpForm", function (newVal, oldVal) {
			if (newVal && !oldVal) {
				self.ra.set("firstEmailEntryComplete", false);
				self.ra.set("firstPasswordEntryComplete", false);
			}
		});
		self.ra.observe("signInShouldSavePassword", function (newVal, oldVal) {
	        self.ra.set("BuddyListManager.OptionsManager.shouldRememberPassword", newVal);
		});

		self.ra.on('signInButtonClicked', self.ToggleSignIn);
		self.ra.on("rememberPasswordLabelClicked", function (evt) {
			self.ra.toggle("signInShouldSavePassword");
		});
		self.ra.on("forgotPasswordLabelClicked", function (evt) {
			JSToNativeBridge.CallNativeFunction("LaunchUrlInBrowser", "https://screenhero.com/reset-password.html?email="+self.ra.get("signInEmail"));
		});
		self.ra.on('signUpButtonClicked', function (event) {
			self.emailFieldDidBlur();
			self.passwordFieldDidBlur();
		    self.ra.set("signUpError", "");
		    if (!self.isEmailValid(self.ra.get("signUpEmail"))) {
		    	$(".signUpEmail").focus();
		        return;
		    }
		    if (self.ra.get("signUpPassword") == "") {
		    	$(".signUpPassword").focus();
		        return;
		    }
		    self.ra.set("isCreatingAccount", true);
		    JSToNativeBridge.CallNativeFunction("CreateAccountWithInfo", Utils.stringify(self.ra.get("signUpName")), Utils.stringify(self.ra.get("signUpEmail")), Utils.stringify(self.ra.get("signUpPassword")));
		});
		self.ra.observe('signUpEmail', function (newVal, oldVal) {
			self.ra.set('signUpEmail', newVal.trim());
		} );
		self.ra.on("loginViewSettingsButtonClicked", function (evt) { Main.ShowDropdownForEvent("#settings-dropdown", evt, "#loginview-container"); });
	}

	this.ResetFormState = function () {
		self.ra.set("shouldShowSignUpForm", false, function () {
			self.ra.set("isCreatingAccount", false);
		});
	}

	this.clearLoginStates = function () {
		self.ra.set("errorText", "");
		self.ra.set("reconnectTimer", 0);
		if (self.reconnectTimer)
			clearTimeout(self.reconnectTimer);
		self.reconnectTimer = undefined;
	}

    this.IsLoggingIn = function() {
        return self.ra.get("Main.loginState") == Main.loginStates.signingIn;
    }

	this.ToggleSignIn = function () {
		self.clearLoginStates();

		if (!self.IsLoggingIn())
			self.doSignIn();
		else
			self.doSignOut();
	}

	this.doSignIn = function () {
		if (!self.isEmailValid(self.ra.get("signInEmail"))){
			$(".signInEmail").focus();
			Main.HandleStatusReason(Main.loginErrors.badUsername);
			return;
		}
		self.ra.set("Main.loginState", Main.loginStates.signingIn);
		self.getJidAndLogin();
	}

	this.doSignOut = function () {
        self.ra.set("Main.loginState", Main.loginStates.signingOut);
		XmppManager.ChangeUserStatus(Main.loginStates.signedOut);		
	}

	this.SetIsReachable = function (isReachable) {
		self.ra.set("isReachable", isReachable);
	}

	this.getJidAndLogin = function () {
        self.connectionAttempt++;
        var thisAttempt = self.connectionAttempt;
		ProtobufManager.SendProtoBuf(
            "AgentUserInfoRequest", 
            {
                buddyEmail: self.ra.get("signInEmail"),
                wantsProfilePic: false
            }, 
            function (jsonOutputStr) {
                var jsonOutput = JSON.parse(jsonOutputStr)
                var pbClass = jsonOutput.classType;
                var pbData = jsonOutput.pbData;
                if (pbClass == "AgentUserInfoResponse") {
	                var pbUIR = ProtobufManager.DecodeProtoBuf("ServerSideProtocol.AgentUserInfoResponse", pbData);
	                var buddyThatIsMe = {};
	                buddyThatIsMe.email = pbUIR.buddyEmail;
	                buddyThatIsMe.bareJid = pbUIR.buddyJID;
	                buddyThatIsMe.name = pbUIR.buddyName;
	                buddyThatIsMe.profilePicURL = pbUIR.buddyProfilePicURL;
	                buddyThatIsMe.paymentType = pbUIR.paymentType;
	                buddyThatIsMe.xmppJid = pbUIR.buddyJID + "/appsharing.web"; // Hack but works
			        BuddyListManager.SetBuddyThatIsMe(buddyThatIsMe);
			        BuddyListManager.SetLoginCredentials((Utils.stringify(self.ra.get("signInPassword"))), self.ra.get("signInShouldSavePassword"));

                    if (buddyThatIsMe.email != BuddyListManager.ra.get("lastSignedInEmail"))
                        BuddyListManager.ra.set("buddyList", []);

			        if (Utils.isAwesomium || !Utils.useFakeXmppServer)
					    XmppManager.DoXmppLogin();
					else
						browserNativeObject.DoXmppLogin();
				}
				else { // error
					self.ra.set("Main.loginState", Main.loginStates.signedOut);
					Main.HandleStatusReason(Main.loginErrors.badUsername);
					$(".signInEmail").focus();
				}
			},
			self.startOrTickReconnectTimer
        );
        setTimeout(function() {
            if (self.connectionAttempt == thisAttempt && self.ra.get("Main.loginState") == Main.loginStates.signingIn)
                self.startOrTickReconnectTimer();
        }, self.connectionTimeout);
	}

	this.startOrTickReconnectTimer = function () {
		if (self.IsLoggingIn()) {
			if (self.ra.get("isReachable") === false) {
				self.ra.set("Main.loginState", Main.loginStates.signedOut);
				Main.HandleStatusReason(Main.loginErrors.noInternet);
				return;
			}
			var currentTimer = self.ra.get("reconnectTimer");
			var newTimer;
			if (currentTimer == 0)
				newTimer = 6;
			else 
				newTimer = currentTimer - 1;
			if (newTimer > 0)
				self.reconnectTimer = setTimeout(self.startOrTickReconnectTimer, 1000);
			else {
				if (self.reconnectTimer)
					clearTimeout(self.reconnectTimer);
				self.reconnectTimer = undefined;
				self.getJidAndLogin();
			}
			switch(newTimer) {
				case 0:
					Main.HandleStatusReason(Main.loginErrors.success);
					break;
				case 6:
					Main.HandleStatusReason(Main.loginErrors.networkError);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					Main.HandleStatusReason(Main.loginErrors.reconnectIn1 + (newTimer - 1));
					break;
			}
			self.ra.set("reconnectTimer", newTimer);
		}
	}

	this.emailFieldDidBlur = function () {
		self.ra.set("firstEmailEntryComplete", true);
	}

	this.isEmailValid = function (email) {
	    var indexOfAt = email.indexOf("@");
	    var indexOfDot = email.lastIndexOf(".");
	    return (indexOfAt > 0) && (indexOfAt < email.length - 4) && (indexOfDot > indexOfAt + 1) && (indexOfDot < email.length - 2);
    }

	this.passwordFieldDidBlur = function () {
		self.ra.set("firstPasswordEntryComplete", true);
	}

    this.isNameValid = function(name) {
    	return Utils.stringify(name).length > 0;
    }

    this.isPasswordValid = function(password) {
    	return Utils.stringify(password).length > 0;
    }
}

