var BuddyList = new function () {
    var self = this;

    this.timeoutToShowCantConnectDialog = 5000;
    this.timeoutToShowPopup = 5000;

    this.CantConnectReasons = {
        BuddyIsBusy: 0,
        BuddyIsOnOldVersion: 1,
        TheyAreUnpaid: 2
    };

    this.CantConnectModel = function (buddy, cantConnectReason) {
        this.buddy = buddy;
        this.reason = cantConnectReason;
    }

    this.FriendRequestModel = function (buddy) {
        this.buddy = Utils.buddyWithSanitizedProfilePic(buddy);
        this.type = "friendRequest";
    }

    this.DialogModel = function (dialogObj) { //uuid, tag, title, body, labelArray, defaultIndex, shouldhideArray) {
        this.type = "dialog";
        this.source = dialogObj.source ? dialogObj.source : "nativeRequest";
        this.uuid = dialogObj.uuid;
        this.tag = dialogObj.tag;
        this.title = dialogObj.title;
        this.body = dialogObj.body;
        this.labelArray = dialogObj.labelArray;
        this.defaultIndex = dialogObj.defaultIndex;
        this.shouldhideArray = dialogObj.shouldhideArray;
    }

    this.PopupModel = function (popupObj) {
        this.kind = popupObj.kind ? popupObj.kind : "info";
        this.body = popupObj.body;
        //we either timeout, or show a dismiss button for timeout = 0
        this.timeout = (popupObj.timeout !== undefined) ? popupObj.timeout : self.timeoutToShowPopup;
        this.hasLabel = (this.timeout > 0 || popupObj.hideButtons) ? false : true;
        console.log("Creating popup "+this.body+" with timeout " + this.timeout + " and hasLabel " + this.hasLabel + " and hideButtons " + popupObj.hideButtons);
        this.hide = false;
    }

    this.SetUpdateIsDownloading = function(isDownloading) {
        self.ra.set("isUpdateDownloading", isDownloading);
    }

    this.SetInstallationDidStart = function(hasStarted) {
        self.ra.set("hasUpdateInstallationStarted", hasStarted);
    }

    // BuddyList.ShowDialog({source: "webRequest", uuid:"fdksfdskfjdkls", tag:"webRequest", title:"Yes?", body:"Hell yeah!", labelArray:["Ok", "Bah"], defaultIndex:0, shouldhideArray:[1, 1]})
    this.ShowDialog = function(dialog) {
        console.log('Showing dialog ' + dialog);
        var newDia = new self.DialogModel(dialog);
        self.ra.get("dialogs").unshift(newDia);
        JSToNativeBridge.CallNativeFunction("ShowMainWindow");
    }

    this.ClearDialogsWithUUID = function(uuid) {
        console.log("Clearing dialogs with uuid: " + uuid);
        if (!self.ra.get("dialogs"))
            return;

        for (var i = 0; i < self.ra.get("dialogs").length; i++)
        {
            var dialog = self.ra.get("dialogs")[i];
            if (dialog.uuid == uuid)
                self.ra.get("dialogs").splice(i, 1); // remove that dialog
        }
    }

    this.ShowFriendRequest = function(buddy) {
        JSToNativeBridge.CallNativeFunction("ShowMainWindow");
        var fr = new self.FriendRequestModel(buddy);
        self.ra.get("dialogs").unshift(fr);
    }

    this.ShowPopup = function(popupObj) {
        var popup = new self.PopupModel(popupObj)
        if (self.ra.get("popups").length == 0) {
            if(popup.timeout > 0) {
                console.log("Setting popup timeout to " + popup.timeout);
                setTimeout(self.ClosePopup, popup.timeout);
            }
            else {
                console.log("not setting popup timeout");
            }
        }
        self.ra.get("popups").unshift(popup);
        JSToNativeBridge.CallNativeFunction("ShowMainWindow");
    }

    this.ClosePopup = function() {
        self.ra.set("popups.0.hide", true, function() {
            self.ra.get("popups").shift();
            if (self.ra.get("popups").length != 0) {
                popup = self.ra.get("popups")[0];
                if(popup.timeout > 0) {
                    console.log("Setting popup timeout to " + popup.timeout);
                    setTimeout(self.ClosePopup, popup.timeout);
                }
                else {
                    console.log("not setting popup timeout");
                }
            }
        });
    }

    this.ShowCantConnectDialog = function(buddy, cantConnectReason) {
        var cantConnectModel = new self.CantConnectModel(buddy, cantConnectReason);
        JSToNativeBridge.CallNativeFunction("ShowMainWindow");
        self.ra.set("cantConnectModel", cantConnectModel);
        setTimeout(function() {
            self.ra.set("cantConnectModel", null);
        }, self.timeoutToShowCantConnectDialog);
    }

    this.setTemplate = function (template) {
        if (template)
            self.template = template;
    }

    this.Initialize = function() {
        self.ra = new Ractive({
            el: "BuddyList-container",
            template: self.template,
            data: {
                BuddyListManager: BuddyListManager.ra,
                dialogs: [],
                popups: [],
                selectedBuddy: null,
                stringify: function(str) {return JSON.stringify(str);},
                ResourceManager: ResourceManager,
                ChatHistoryManager: ChatHistoryManager.ra,
                Main: Main.ra,
                Utils: Utils,
                cantConnectModel: null,
                isUpdateDownloading: false,
                Reasons: self.CantConnectReasons,
                SessionType: BuddyListManager.SessionType,
                sort: function ( array ) {
                    array = array.slice(); // clone, so we don't modify the underlying data
                    return array.sort( function ( a, b ) {
                        if (a.isOnline && !b.isOnline)
                            return -1;
                        else if (!a.isOnline && b.isOnline)
                            return 1;
                        else
                            return a.name.toUpperCase() < b.name.toUpperCase() ? -1 : 1;
                    });
                },
                unreadChatCountForbuddy: function (hash, jid) {
                    jid = jid.split("@")[0];
                    var val = hash[jid];
                    if (val > 99)
                        val = "99+";
                    if (val == 0)
                        val = "";
                    return val;
                },
                versionStringToInt: function(str) {
                    var num = 0;
                    var arr = str.split(".");
                    for (var i=0; i<arr.length; i++)
                        num += arr[arr.length - 1 - i]*Math.pow(10,i);
                    return num;
                },
                newArray: function(n) { return new Array(n); },
                GetBuddyListWithSharingStateMask: BuddyListManager.GetBuddyListWithSharingStateMask,
                GetBuddyListLengthWithSharingStateMask: BuddyListManager.GetBuddyListLengthWithSharingStateMask,
                GetSelectedBuddies: BuddyListManager.GetSelectedBuddies,
                getPaymentTextForType: function(t) {
                    var PaymentType = self.ra.get("BuddyListManager.PaymentType");
                    if (t == PaymentType.NoBillingData) return  "Pre-trial";
                    if (t == PaymentType.Active) return  "Active";
                    if (t == PaymentType.Trialing) return  "In trial";
                    if (t == PaymentType.GracePeriod) return  "Credit card issue";
                    if (t == PaymentType.Delinquent) return  "Credit card expired";
                    if (t == PaymentType.TrialExpired) return  "Trial expired";
                    if (t == PaymentType.Canceled) return  "Canceled";
                    if (t == PaymentType.CancelPending) return  "Cancel pending";
                },
                getPaymentActionTextForType: function(t) {
                    var PaymentType = self.ra.get("BuddyListManager.PaymentType");
                    if (t == PaymentType.NoBillingData) return  "Account...";
                    if (t == PaymentType.Active) return  "Account...";
                    if (t == PaymentType.Trialing) return  "Upgrade my account";
                    if (t == PaymentType.GracePeriod) return  "Account...";
                    if (t == PaymentType.Delinquent) return  "Account...";
                    if (t == PaymentType.TrialExpired) return  "Account...";
                    if (t == PaymentType.Canceled) return  "Account...";
                    if (t == PaymentType.CancelPending) return  "Account...";
                },
                IsPaidUser: BuddyListManager.IsPaidUser,
                ShouldShowNagFooter: self.ShouldShowNagFooter,
                GetProfilePicBackgroundStyleForBuddy: BuddyListManager.GetProfilePicBackgroundStyleForBuddy,
                clearInfoOnSignOut: false,
                ShouldShowNagFooter1: self.ShouldShowNagFooter1,
                ShouldShowNagFooter2: self.ShouldShowNagFooter2,
                maxSharingBuddiesToShow: 6,
                HaveTooManyBuddiesToShow: function() {
                    var totalSharingPendingBuddies = BuddyListManager.GetBuddyListLengthWithSharingStateMask(BuddyListManager.SharingStatus.Pending | BuddyListManager.SharingStatus.Sharing);
                    // console.log("HaveTooManyBuddiesToShow totalSharingPendingBuddies = " + totalSharingPendingBuddies);
                    return totalSharingPendingBuddies > self.ra.get("maxSharingBuddiesToShow");
                }
            }
        });

        // TODO: J, this might need to go?
        self.ra.observe("BuddyListManager.buddyList", self._setBuddyListHeight, {defer: true});
        self.ra.observe("dialogs", self._setBuddyListHeight, {defer: true});
        self.ra.observe("popups", self._setBuddyListHeight, {defer: true});
        self.ra.observe("cantConnectModel", self._setBuddyListHeight, {defer: true});

        self.ra.observe("Main.loginState", function(newval, oldval) {
            if (newval == Main.loginStates.signedOut && (oldval == Main.loginStates.signedIn || oldval == Main.loginStates.signingOut)) {
                if (self.ra.get("clearInfoOnSignOut")) {
                    BuddyListManager.OnUserChoseSignOut();
                    self.ra.set("dialogs", []);
                    self.ra.set("popups", []);
                    self.ra.set("clearInfoOnSignOut", false);
                }
            }
        }, {defer: true});

        self.ra.on("signOutClicked", self._userChoseSignOut);
        self.ra.on("change", self._setBuddyListHeight); //TODO (j) must be a better way to do this

        self.ra.on( 'closeDisplayedDialog', function ( event ) {
            if (event.node.getAttribute("data-type")=="friendRequest")
            {
                if (event.node.getAttribute("data-action")=="accept")
                    XmppManager.RespondToInvitation(event.context.buddy.bareJid, true);
                else if (event.node.getAttribute("data-action")=="reject")
                    XmppManager.RespondToInvitation(event.context.buddy.bareJid, false);
            }
            else
            {
                if(event.node.getAttribute("data-source") == "nativeRequest")
                {
                    console.log("Sending dialog response to native code: " + event.node.getAttribute("data-uuid") + " " + event.node.getAttribute("data-tag") + " " + event.node.getAttribute("data-index"));
                    JSToNativeBridge.CallNativeFunction("DialogResult", event.node.getAttribute("data-uuid"), parseInt(event.node.getAttribute("data-tag")), parseInt(event.node.getAttribute("data-index")));
                }
                else if(event.node.getAttribute("data-source") == "webRequest")
                {
                    console.log("Sending dialog response to web code: " + event.node.getAttribute("data-uuid") + " " + event.node.getAttribute("data-tag") + " " + event.node.getAttribute("data-index"));
                    NativeToJSBridge.WebDialogCallback(event.node.getAttribute("data-uuid"), parseInt(event.node.getAttribute("data-tag")), parseInt(event.node.getAttribute("data-index")));
                }
                else if (event.node.getAttribute("data-source") == "jsRequest")
                {
                    console.log("Sending dialog response to js code: " + event.node.getAttribute("data-uuid") + " " + event.node.getAttribute("data-tag") + " " + event.node.getAttribute("data-index"));
                    var method = eval(event.node.getAttribute("data-uuid"));
                    method.call(undefined, parseInt(event.node.getAttribute("data-tag")), parseInt(event.node.getAttribute("data-index")));
                }
            }


            if (self.ra.get("dialogs").length > 0)
            {
                if (event.node.getAttribute("data-shouldhide") != "0")
                {
                    self.ra.set("dialogs.0.hide", true, function () {
                        self.ra.get("dialogs").shift();
                    });
                }
            }
        });

        self.ra.on( 'closeDisplayedPopup', function ( event ) {
            console.log("closing popup");
            if (self.ra.get("popups").length > 0)
            {
                self.ra.set("popups.0.hide", true, function () {
                    self.ra.get("popups").shift();
                    if (self.ra.get("popups").length != 0) {
                        popup = self.ra.get("popups")[0];
                        if(popup.timeout > 0) {
                            console.log("new popup " + popup.body)
                            console.log("Setting popup timeout to " + popup.timeout);
                            setTimeout(self.ClosePopup, popup.timeout);
                        }
                        else {
                            console.log("not setting popup timeout " + popup.timeout);
                        }
                    }
                });
            }
        });

        //header
        self.ra.on("addBuddyClicked", function (evt) {
            JSToNativeBridge.CallNativeFunction("ShowAddBuddyPanel");
        });

        //share-row
        self.ra.on("shareBuddyVoiceMuteClicked", function (evt) {
            BuddyListManager.ToggleVoiceChatMute();
        });

        self.ra.on("shareBuddyScreenHoldClicked", function (evt) {
            BuddyListManager.ToggleScreenShareMute();
        });

        self.ra.on("shareBuddyChatClicked", function (evt) {
            var buddyJid = evt.context.bareJid;
            if (!buddyJid)
                buddyJid = BuddyListManager.GetBuddyListWithSharingStateMask(BuddyListManager.SharingStatus.Sharing)[0].bareJid;
            ChatWindowManager.OpenChatWindowForBuddy(buddyJid);
        });

        //selection instructions row
        self.ra.on("deselectBuddiesClicked", function (evt) {
            self.ra.set("BuddyListManager.selectedBuddies", []);
        });

        //buddy-row
        self.ra.on("buddyChatClicked", function (evt) {
            // if (evt.context.isOnline)
                ChatWindowManager.OpenChatWindowForBuddy(evt.context.bareJid);
        });
        self.ra.on( "buddyCallClicked", function(evt) {
            BuddyListManager.ToggleShareWithBuddy(evt.context.bareJid, BuddyListManager.SessionType.Voice);
        });
        self.ra.on( "buddyShareClicked", function(evt) {
            BuddyListManager.ToggleShareWithBuddy(evt.context.bareJid, BuddyListManager.SessionType.Screen);
        });
        self.ra.on( "buddyAddClicked", function(evt) {
            console.log("buddyAddClicked: " + evt.context.bareJid);
            if (evt.context.isOnline)
                BuddyListManager.AddBuddyToSession(evt.context.bareJid);
        });
        self.ra.on("buddyDeleteClicked", function (evt) {
            XmppManager.RemoveBuddyFromList(evt.context.bareJid);
        });
        self.ra.on( "myBuddyNameClicked", function(evt) { 
            JSToNativeBridge.CallNativeFunction("ShowUserProfilePanel");
            //window.open("index.htm");
        });
        self.ra.on( "profilePicClicked", function(evt) { 
            JSToNativeBridge.CallNativeFunction("ShowUserProfilePanel");
            //window.open("index.htm");
        });
        self.ra.on( "myBuddyStatusClicked", function(evt) { 
            window.setTimeout(function () {
                $('#online-dropdown').dropdown('toggle');
            }, 0);
        });
        self.ra.on( "addContactClicked", function(evt) { JSToNativeBridge.CallNativeFunction("ShowAddBuddyPanel"); });
        self.ra.on("buddyDoubleClicked", function(evt) {
            ChatWindowManager.OpenChatWindowForBuddy(evt.context.bareJid);
        });
        self.ra.on("buddyClicked", function(evt) {
            try {
                for (var element = evt.original.srcElement; element != evt.node; element = element.parentElement)
                    if ($(element).hasClass("btn-icon"))
                        return;
            }
            catch (e) {
                return;
            }
            // don't allow selections if in any sort of share
            if (BuddyListManager.GetBuddyListWithSharingStateMask(BuddyListManager.SharingStatus.Pending | BuddyListManager.SharingStatus.Sharing).length == 0 && evt.context.isOnline)
            {
                if (evt.context.show == BuddyListManager.JabberStatusShow.DoNotDisturb)
                {
                    BuddyList.ShowCantConnectDialog(evt.context, BuddyList.CantConnectReasons.BuddyIsBusy);
                }
                else
                {
                    var jid = evt.context.bareJid;
                    var buddyList = self.ra.get("BuddyListManager.buddyList");
                    for (var i = buddyList.length - 1; i >= 0; i--) {
                        if (buddyList[i].bareJid == jid) {
                            self.ra.toggle("BuddyListManager.buddyList." + i + ".isSelected");
                            var numSelectedBuddies = self.ra.get("BuddyListManager.numSelectedBuddies");
                            numSelectedBuddies = numSelectedBuddies + (self.ra.get("BuddyListManager.buddyList." + i + ".isSelected") ? 1 : -1);
                            self.ra.set("BuddyListManager.numSelectedBuddies", numSelectedBuddies);
                        }
                    };

                    if (self.ra.get("buddyClickNeedsCancel")) {
                        self.ra.set("buddyClickNeedsCancel", false);
                        evt.original.cancelBubble = true;
                    }
                }
            }
        });
        self.ra.on("buddyRightClicked", function(evt) {
            if (evt.original.ctrlKey)
                self.ra.set("buddyClickNeedsCancel", true);
            self.ra.set("selectedBuddy", evt.context);
            Main.ShowDropdownForEvent("#buddy-dropdown", evt, "#buddylist-container");
        });
        self.ra.on("buddyKickClicked", function(evt) {
            var buddyToKick = evt.context;
            // JSToNativeBridge.CallNativeFunction("kickBuddy", buddyToKick.bareJid);
        });

        self.ra.on("loveButtonClicked", function (evt) { JSToNativeBridge.CallNativeFunction("ShowLovePanel"); });
        self.ra.on("showSharingBuddiesClicked", function (evt) { 
            var dropdown = $("#sharing-buddies-dropdown");
            // on showing the more buddies list, hide the "n more people" tooltip, and disable it for now. 
            // also, keep the hover state for the disclosure button active (blue) while the dropdown is displayed
            dropdown.parent().one("show.bs.dropdown", function() {
                $(".sharing-buddies-disclosure").tooltip('hide');
                $(".sharing-buddies-disclosure").data('bs.tooltip').options.title = "";
                $(".more-buddies").addClass("active");
            });
            // once the dropdown is hidden, reset the tooltip so it can be activated again, and also remove the active state on the disclosure button
            dropdown.parent().one("hidden.bs.dropdown", function() {
                $(".sharing-buddies-disclosure").data('bs.tooltip').options.title = $(".sharing-buddies-disclosure").attr("data-title");
                $(".more-buddies").removeClass("active");
            });

            // Main.ShowDropdownForEvent("#sharing-buddies-dropdown", evt, "#buddylist-container");
            evt.original.cancelBubble = true;
            dropdown.dropdown("toggle");
            dropdown.parent().parent().css({right: 21, top: 110});
        });
        self.ra.on("settingsButtonClicked", function (evt) { Main.ShowDropdownForEvent("#settings-dropdown", evt, "#buddylist-container"); setTimeout(function() {$("input").focus();}, 10); });
        self.ra.on("settingsBillingClicked", function (evt) { self.ShowSubscribePage(); });
        self.ra.on("settingsAboutClicked", function (evt) { JSToNativeBridge.CallNativeFunction("ShowAboutPanel"); });
        self.ra.on("settingsSettingsClicked", function (evt) { JSToNativeBridge.CallNativeFunction("ShowSettingsPanel"); });
        self.ra.on("settingsUpgradeToDevClicked", function (evt) {
            var dialog = {};
            dialog.title = "Beware! Here be dragons!";
            dialog.body = "Screenhero 2.0 beta includes group screen sharing/voice calling, and improved connection reliability/performance. Note that you will only be able to share with others that are using the beta (v1.9.*).";
            dialog.labelArray = ["Bring it on", "Cancel"];
            dialog.shouldhideArray = [true, true];
            // dialog.shouldhideArray = [0];
            dialog.source = "jsRequest";
            dialog.uuid = "BuddyList.UpgradeToDevDialogClosed";
            dialog.tag = "1";
            dialog.defaultIndex = 0;
            self.ShowDialog(dialog);
        });
        self.ra.on("settingsFeedbackClicked", function (evt) { JSToNativeBridge.CallNativeFunction("ShowFeedbackPanel"); });
        self.ra.on("settingsSendCrashReportClicked", function (evt) { JSToNativeBridge.CallNativeFunction("ShowCrashReportPanel"); });
        self.ra.on("settingsDebugClicked", function (evt) { JSToNativeBridge.CallNativeFunction("ShowDebugPanel"); });
        self.ra.on("settingsUpdateClicked", function (evt) { JSToNativeBridge.CallNativeFunction("CheckForUpdates"); });
        self.ra.on("settingsProfileClicked", function (evt) { JSToNativeBridge.CallNativeFunction("ShowUserProfilePanel"); });      
        self.ra.on("settingsJSDebugClicked", function (evt) { ChatWindowManager.OpenChatWindowForBuddy(ChatWindowManager.debuggerWindowJID); });
        self.ra.on("settingsSignoutClicked", function (evt) { self._userChoseSignOut(); });              
        self.ra.on("settingsQuitClicked", function (evt) { JSToNativeBridge.CallNativeFunction("QuitApp"); });
        self.ra.on("enterEvalCode", function (evt) { console.log(eval(self.ra.get("evalCode"))); });

        self.ra.observe("BuddyListManager.OptionsManager.buddyThatIsMe.paymentType", function(newval, oldval) {
            if (newval != oldval) {
                oldval = oldval === undefined ? null : oldval;
                newval = newval === undefined ? null : newval;
                var PaymentType = BuddyListManager.ra.get("PaymentType");
                if (newval == PaymentType.Active) {
                    self.ClearDialogsWithUUID("BuddyList.SubscribeDialogClosed");
                    if (oldval == PaymentType.Trialing || oldval == PaymentType.TrialExpired) {
                        self.ShowPopup({kind:"success", body:"Thanks for upgrading! We really appreciate it. :)"});
                    } else if (oldval == PaymentType.Canceled) {
                        self.ShowPopup({kind:"success", body:"Thanks for coming back! You're just the best! :)"});
                    } else if (oldval == PaymentType.GracePeriod || oldval == PaymentType.Delinquent) {
                        self.ShowPopup({kind:"success", body:"Thanks for updating your billing information! We really appreciate it. :)"});
                    }
                }
                else if (BuddyListManager.IsPaidUser(newval) && !BuddyListManager.IsPaidUser(oldval)) { // went from unpaid to paid
                    self.ClearDialogsWithUUID("BuddyList.SubscribeDialogClosed");
                }
                else if (BuddyListManager.IsPaidUser(oldval) && !BuddyListManager.IsPaidUser(newval)) { // went from paid to unpaid
                    var dialog = {};
                    switch (self.ra.get("BuddyListManager.OptionsManager.buddyThatIsMe.paymentType")) {
                        case PaymentType.Delinquent:
                            dialog.title = "Your payment failed";
                            dialog.body = "Please update your credit card information to continue using Screenhero.";
                            dialog.labelArray = ["Update payment details"];
                            dialog.shouldhideArray = [false];
                            break;
                        case PaymentType.Canceled:
                            if(oldval === null) return;
                            dialog.title = "Your subscription was canceled";
                            dialog.body = "You canceled your subcription or left a team subscription. You can stay on free Guest Plan and share only with paid users or upgrade and share with anyone.";
                            dialog.labelArray = ["Upgrade", "Dismiss"];
                            dialog.shouldhideArray = [true, true];
                            break;
                        case PaymentType.TrialExpired:
                        default:
                            if(oldval === null) return;
                            dialog.title = "Your trial has expired";
                            dialog.body = "You can stay on free Guest Plan and share only with paid users or upgrade and share with anyone.";
                            dialog.labelArray = ["Upgrade", "Dismiss"];
                            dialog.shouldhideArray = [true, true];
                            break;
                    }
                    // dialog.shouldhideArray = [0];
                    dialog.source = "jsRequest";
                    dialog.uuid = "BuddyList.SubscribeDialogClosed";
                    dialog.tag = "1";
                    dialog.defaultIndex = 0;
                    self.ShowDialog(dialog);
                }
            }
        });

        /* Watching change for change in tooltips */
        self.ObserveTooltipChanges(self.ra);

        self.ra.on('onUpgradeClicked', function() {
            self.ShowSubscribePage();
        });
    };

    this.SubscribeDialogClosed = function(tag, idx) {
        // console.log("tag = " + tag);
        // console.log("idx = " + idx);
        if(idx == 0) {
            self.ShowSubscribePage();
        }
    }

    this.UpgradeToDevDialogClosed = function(tag, idx) {
        if(idx == 0) {
            JSToNativeBridge.CallNativeFunction("UpgradeToDevVersion");
        }
    }

    this.ShowSubscribePage = function() {
        JSToNativeBridge.CallWebFunction("sessionKey", [self.ra.get("BuddyListManager.OptionsManager.buddyThatIsMe.bareJid"), self.ra.get("BuddyListManager.OptionsManager.password")], function(session_key) {
            JSToNativeBridge.CallNativeFunction("LaunchUrlInBrowser", Utils.billingServerURI + "/account/?tab=3&session_key=" + session_key + "&active=" + BuddyListManager.isPaymentTypeActive(self.ra.get("BuddyListManager.OptionsManager.buddyThatIsMe.paymentType")));
        });
    }

    /* Update tooltip */
    this.ObserveTooltipChanges = function(ra) {
        ra.observe("BuddyListManager.connectionQuality", self.UpdateTooltips, {defer: true});
        ra.observe("BuddyListManager.OptionsManager.isWaitingForScreenShare", self.UpdateTooltips, {defer: true});
        ra.observe("BuddyListManager.OptionsManager.isScreenShareMuted", self.UpdateTooltips, {defer: true});
        ra.observe("BuddyListManager.OptionsManager.isVoiceChatMuted", self.UpdateTooltips, {defer: true});
        ra.observe("BuddyListManager.savedSessionStates", self.UpdateTooltips, {defer: true});
        ra.observe("BuddyListManager.activeSessionId", self.UpdateTooltips, {defer: true});
        ra.observe("BuddyListManager.numSelectedBuddies", self.UpdateTooltips, {defer: true});
    }

    this.UpdateTooltips = function(newval, oldval, keypath) {
        var jqclasses = [];
        if (keypath == "BuddyListManager.savedSessionStates" || keypath == "BuddyListManager.activeSessionId") {
            jqclasses.push(".buddypic-group-pic-and-spinner-holder");
            jqclasses.push(".sharing-buddies-disclosure");
        }
        if (keypath == "BuddyListManager.OptionsManager.isScreenShareMuted")
            jqclasses.push(".btn-toggle.share");
        if (keypath == "BuddyListManager.OptionsManager.isVoiceChatMuted")
            jqclasses.push(".btn-toggle.voice");
        if (keypath == "BuddyListManager.connectionQuality")
            jqclasses.push(".signal-bar");
        if (keypath == "BuddyListManager.numSelectedBuddies")
            jqclasses.push(".btn-add-to-share");
        if (jqclass != "") {
            for (var i=0; i<jqclasses.length; i++) {
                var jqclass = jqclasses[i];
                $.each($(jqclass), function(index, tooltip) {
                    var tooltipdata = $(tooltip).data('bs.tooltip');
                    if (tooltipdata && tooltipdata.options)
                    {
                        $(tooltip).data('bs.tooltip').options.title = $(tooltip).attr("data-title");
                        $(tooltip).tooltip('hide');
                        // J: this is stupid, just always hide stuff
                        // if ($(tooltip).data('bs.tooltip').tip().hasClass('in')) // if visible
                        //     $(tooltip).tooltip('show');
                        // else
                        //     $(tooltip).tooltip('hide');
                    }
                });
            }
        }
    }

    this._userChoseSignOut = function () {
        self.ra.set("clearInfoOnSignOut", true);
        if (Utils.useFakeXmppServer)
            browserNativeObject.ChangeUserStatus(Main.loginStates.signedOut);
        else
            XmppManager.ChangeUserStatus(Main.loginStates.signedOut);
    }

    this.ShouldShowNagFooter1 = function(paymentType) {
        return paymentType == self.ra.get("BuddyListManager.PaymentType.Canceled") || paymentType == self.ra.get("BuddyListManager.PaymentType.TrialExpired");
    }

    this.ShouldShowNagFooter2 = function(paymentType) {
        return paymentType == self.ra.get("BuddyListManager.PaymentType.Trialing");
    }

    this._setBuddyListHeight = function () {
        self._doSetBuddyListHeight();
        setTimeout(self._doSetBuddyListHeight, 401);
    }

    this._doSetBuddyListHeight = function () {
        var height = $(".buddylist-content-holder").height();
        if (!height)
            return;
        // if there are > 1 dialogs, on closing one, we first hide it, then show the next.
        // this is achieved by setting dialogs[0] = null, so here we check to make sure
        // that the length > 0 and that [0] != null for the height to be shrunk by the dialogs height

        // if (self.ShouldShowNagFooter1(self.ra.get("BuddyListManager.OptionsManager.buddyThatIsMe.paymentType")) || self.ShouldShowNagFooter2(self.ra.get("BuddyListManager.OptionsManager.buddyThatIsMe.paymentType")))
        //     height -= $(".buddylist-bugbox").outerHeight();

        if (self.ra.get("dialogs").length>0 && self.ra.get("dialogs.0.hide") !== true)
            height -= $(".dialog").outerHeight();

        if ($(".sharing-buddy-row"))
            height -= $(".sharing-buddy-row").outerHeight();

        $(".buddy-row-holder").css({
            height: height
        });
    }
}