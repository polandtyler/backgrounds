// console.logCopy = console.log.bind(console);

// console.log = function(data)
// {
//     var currentDate = '[' + new Date().toUTCString() + '] ';
//     this.logCopy(currentDate, data);
// };

var BuddyListManager = new function () {
    var self = this;
    
    this.AppModel = function(name, iconURL) {
        this.name = name;
        this.iconURL = iconURL;
    }

    this.SharingStatus = {
        None: 0,
        Pending: 1,
        Sharing: 2
        // make sure the next one is a 4 (J says: trust me on this)
    }

    this.SessionType = {
        None: 0,
        Screen: 1,
        Voice: 2,
        Video: 3
    }

    this.JabberStatusShow = {
        None: 0,
        Offline: 1,
        ExtendedAway: 2,
        Away: 3,
        DoNotDisturb: 4,
        Online: 5,
        Chat: 6
    }
    
    this.BuddyState = {
        None: 0,
        Pending: 1,
        Sharing: 2
    }

    this.SessionState = {
        Active: 0,
        Pending: 1
    }

    this.Initialize = function() {
        // console.log("inside function Initialize");
        self.ra = new Ractive({
            data: {
                buddyList: [],
                buddyWithJid: self.GetBuddyWithJID,
                OptionsManager: {
                    buddyThatIsMe: {
                        email: ""                        
                    },
                    password: "",
                    shouldRememberPassword: true,
                    isRingingMuted: false,
                    version: "7.0.0.0"
                },
                payDialog: {},
                previousOptionsManager: {},
                connectionQuality: 0,
                isSlave: false,
                sessionType: BuddyListManager.SessionType.None,
                isUpdatingOptionsManager: true,
                showNoBuddiesView: false,
                isWaitingForScreenShare: false,
                JabberStatusShow: self.JabberStatusShow,
                GetBuddyListWithSharingStateMask: self.GetBuddyListWithSharingStateMask,
                GetBuddyListLengthWithSharingStateMask: self.GetBuddyListLengthWithSharingStateMask,
                SharingStatus: self.SharingStatus,
                PaymentType: ProtobufManager.builder.lookup("ServerSideProtocol.AgentUserInfoResponse.PaymentType").build(),
                savedSessionStates: {},
                numSelectedBuddies: 0,
                isReconnecting: false,
                activeSessionId: 0,
                updateUIsignal: false
            },
            modifyArrays: false
        });

        self.nextSessionId = 0;
        self.saveBuddyListTimeoutHandle = 0;
        self.isPlayingShareSound = false;
        self.wasInShare = false;

        if (ResourceManager.isMainModule())
            self.ra.observe("activeSessionId savedSessionStates", self.UpdateSoundAndPresence, {defer: true});

        self.ra.observe("OptionsManager", function(newval, oldval) {
            oldval = self.ra.get("previousOptionsManager");
            var updateObj = null;
            for (var key in newval) {
                if (oldval[key] == undefined || newval[key] != oldval[key]) {
                    if (!updateObj)
                        updateObj = {};
                    updateObj[key] = newval[key];
                }
                self.ra.set("previousOptionsManager." + key, newval[key]);
            }

            if (updateObj && !self.ra.get("isUpdatingOptionsManager"))
            {
                console.log("version = " + self.ra.get("OptionsManager.version"));
                updateObj["version"] = self.ra.get("OptionsManager.version");  // always set protocol version
                JSToNativeBridge.CallNativeFunction("UpdateOptionsManager", updateObj);
            }
        });

        self.ra.observe("isReconnecting", function(newval, oldval) {
            if (!ResourceManager.launchModuleName) { // don't do any share sounds unless main module
                setTimeout(function() {
                    if (newval)
                        BuddyList.ShowPopup({kind:"warning", body:"The connection was lost, reconnecting...", timeout:-1, hideButtons:true});
                    else
                        BuddyList.ClosePopup();
                }, 0);
            }
        }, {init: false});
    };

    this.UpdateSoundAndPresence = function(newval, oldval) {
        var isInShare = self.IsInShare();
        if (!isInShare)
            self.ra.set("isReconnecting", false);
        
        var oneOrMorePendingAndNoSharing = self.GetBuddyListLengthWithSharingStateMask(self.SharingStatus.Pending)>0 &&
             self.GetBuddyListLengthWithSharingStateMask(self.SharingStatus.Sharing)==0 && Object.keys(self.ra.get("savedSessionStates")).length==1;
        var previousShow = self.ra.get("OptionsManager.buddyThatIsMe.show");
        var newShow = (isInShare || oneOrMorePendingAndNoSharing) ? BuddyListManager.JabberStatusShow.DoNotDisturb : BuddyListManager.JabberStatusShow.Online;
        if (previousShow != newShow) {
            self.ra.set("OptionsManager.buddyThatIsMe.show", newShow);
            if (!Utils.useFakeXmppServer)
                XmppManager.SendPresence();
        }

        // console.log("UpdateSoundAndPresence. playsound:"+self.isPlayingShareSound+" pendingnosharing:"+oneOrMorePendingAndNoSharing+" pendingnum:"+self.GetBuddyListLengthWithSharingStateMask(self.SharingStatus.Pending)+" sharingnum: "+self.GetBuddyListLengthWithSharingStateMask(self.SharingStatus.Sharing)+" keyslength:"+Object.keys(self.ra.get("savedSessionStates")).length);

        if (!self.isPlayingShareSound && oneOrMorePendingAndNoSharing)
            self.StopShareSound(false);
        else if (self.isPlayingShareSound && !oneOrMorePendingAndNoSharing)
            self.StopShareSound(true);            

        self.wasInShare = isInShare;
    }

    this.InitializeOptionsManager = function(obj) {
        // console.log("inside function InitializeOptionsManager");
        self.ra.set("isUpdatingOptionsManager", true);
        for (var key in obj) {
            if (key == "username") {
                self.ra.set("OptionsManager.buddyThatIsMe.email", obj[key]);
            }
            // else if (key == "buddyList")
            //     self.SetBuddyList(obj[key]);
            else
            {
                //console.log("setting OptionsManager key=" + key + ", value=" + obj[key]);
                self.ra.set("OptionsManager." + key, obj[key]);
            }
        }
        self.ra.set("lastSignedInEmail", self.ra.get("OptionsManager.buddyThatIsMe.email"));

        if(self.ra.get("OptionsManager.shouldRecordAnalytics") === false) {

            var dialog = {
                title: "Privacy Policy Update",
                body: "Our privacy policy has changed. Continued use of Screenhero requires that you acknowledge and agree to this new policy.",
                labelArray: ["I Agree", "View Policy"],
                shouldhideArray: [1, 0],
                source: "jsRequest",
                uuid: "BuddyListManager.UpdateShouldRecordAnalytics",
                tag: "1",
                defaultIndex: 0
            };
            BuddyList.ShowDialog(dialog);
        }

        self.ra.set("isUpdatingOptionsManager", false);
    };

    this.UpdateShouldRecordAnalytics = function(tag, index) {
        // console.log("inside function UpdateShouldRecordAnalytics");
        console.log("" + tag + " "+index);
        if(index === 0) {
            //They agree to the change. Update OptionsManager
            self.ra.set("OptionsManager.shouldRecordAnalytics", true);
        }
        else if (index === 1) {
            //show the privacy policy
            JSToNativeBridge.CallNativeFunction("LaunchUrlInBrowser", "https://screenhero.com/privacy.html");
        }
    };

    this.UpgradeToBetaClicked = function (tag, index) {
        console.log("" + tag + " "+index);
        if(index === 1) {
            setTimeout(
                function() {BuddyList.ra.fire('settingsUpgradeToDevClicked');},
                1000); //TODO THIS IS A FUCKING HACK! The problem is that the dialog response function hides the FIRST dialog, not the one actually clicked on. Fucker.
        }
        console.log("======= done");
    };

    this.IsPaidUser = function(optionalPaymentType) {
        // console.log("inside function IsPaidUser");
        if (optionalPaymentType === undefined)
            optionalPaymentType = self.ra.get("OptionsManager.buddyThatIsMe.paymentType");
        return self.isPaymentTypeActive(optionalPaymentType);
    }

    this.isPaymentTypeActive = function(paymentType) {
        // console.log("inside function isPaymentTypeActive");
        var PaymentType = self.ra.get("PaymentType");
        var isActive =  paymentType == PaymentType.NoBillingData || 
                        paymentType == PaymentType.Active || 
                        paymentType == PaymentType.Trialing || 
                        paymentType == PaymentType.GracePeriod ||
                        paymentType == PaymentType.CancelPending ||
                        paymentType == null;
        return isActive;
    }

    this.SetPaymentType = function(paymentType) {
        // console.log("inside function SetPaymentType");
        self.ra.set("OptionsManager.buddyThatIsMe.paymentType", paymentType);
    }

    this.SetConnectionQuality = function(floatval) {
        // console.log("inside function SetConnectionQuality");
        self.ra.set("connectionQuality", Math.max(1,Math.min(5,Math.round(floatval*5))));
    }

    this.GetBuddyWithJID = function(bareJid, callbackFunction) {
        // console.log("inside function GetBuddyWithJID");
        // console.log("GetBuddyWithJID called on " + bareJid + " with callback: " + callbackFunction);
        if (bareJid == "" || bareJid == null)
            return null;

        if (bareJid == ChatWindowManager.debuggerWindowJID)
            return Utils.buddyWithSanitizedProfilePic({name: "Debugger", bareJid: bareJid, isOnline: true});

        var buddyList = self.ra.get("buddyList");
        var buddy;
        for (var i = buddyList.length - 1; i >= 0; i--) 
        {
            if (buddyList[i].bareJid == bareJid)
            {
                buddy = buddyList[i];
                break;
            }
        }

        if (callbackFunction) {
            if (!buddy)
            {
                XmppManager.LoadProfileForJidWithCallback(bareJid, function(buddy) {
                    console.log("created temp buddy: " + buddy.bareJid);
                    buddy.hidden = true;
                    BuddyListManager.AddBuddyToList(buddy);
                    callbackFunction.apply(self, [buddy]);
                });
            }
            else
            {
                callbackFunction.apply(self, [buddy]);
            }            
        }

        return buddy ? buddy : null;
    }

    this.GetIndexForBuddyWithJID = function(bareJid) {
        // console.log("inside function GetIndexForBuddyWithJID");
        if (bareJid == "" || bareJid == null)
            return -1;

        var buddyList = self.ra.get("buddyList");
        for (var i = buddyList.length - 1; i >= 0; i--) {
            var buddy = buddyList[i];
            if (buddy.bareJid == bareJid)
                return i;
        }

        return -1;
    }

    this.IncomingShareReceivedForBuddy = function(invitingBuddyJID, shareType, isAutoAccept) {
        // console.log("inside function IncomingShareReceivedForBuddy");
        self.ra.set("isSlave", true);
        self.ra.set("OptionsManager.isScreenShareMuted", true);
        self.ResetSelectedBuddies();

        if (shareType == BuddyListManager.SessionType.Voice)
            self.ra.set("OptionsManager.isVoiceChatMuted", false);  // always unmute for voice-only calls
        else if (!isAutoAccept)
            self.ra.set("OptionsManager.isVoiceChatMuted", self.ra.get("OptionsManager.isVoiceChatMutedOnScreenShare"));

        if (isAutoAccept)  // this came from the protobuf invite request (probably switch presenter)
        {
            self.ra.set("OptionsManager.isWaitingForScreenShare", true);
            JSToNativeBridge.CallNativeFunction("AcceptShareRequestFromBuddy", invitingBuddyJID);
        }
        else
        {
            if (Utils.isAutoAcceptEnabled)  // this is for JS debugging purposes only
                self.UserRespondedToShareRequest(invitingBuddyJID, true);
            else
            {
                IncomingShareWindowManager.OpenIncomingShareWindowForBuddy(invitingBuddyJID, shareType);
            }
        }
    }

    this.IsInShare = function() {
        // console.log("inside function IsInShare");
        return (self.GetBuddyListLengthWithSharingStateMask(self.SharingStatus.Pending | self.SharingStatus.Sharing) > 0);
    }

    this.IsInGroupShare = function() {
        // console.log("inside function IsInGroupShare");
        return (self.GetBuddyListLengthWithSharingStateMask(self.SharingStatus.Pending | self.SharingStatus.Sharing) > 1);
    }

    this.ToggleShareWithBuddy = function(newSharingBuddyJID, sessionType) {
        // console.log("inside function ToggleShareWithBuddy");
        console.log("ToggleShareWithBuddy, sessionType=" + sessionType);

        if (!self.IsInShare())
        {
            var selectedBuddies = self.GetSelectedBuddies();
            if (selectedBuddies.length == 0)
                selectedBuddies = [self.GetBuddyWithJID(newSharingBuddyJID)];

            // check busy state and version of all selected buddies before starting share
            for (var i=0; i < selectedBuddies.length; i++)
            {
                var buddyInfo = selectedBuddies[i];
                console.log("buddyJid=" + buddyInfo.bareJid + ", version=" + buddyInfo.version + ", OptionsManager.version=" + self.ra.get("OptionsManager.version"));
                var canBuddyBeSharedWith = self.CanBuddyBeSharedWith(buddyInfo);
                if (!canBuddyBeSharedWith)
                    return;
            }

            // all clear, blast off!
            self.StartSessionWithBuddies(selectedBuddies, sessionType);
            self.ResetSelectedBuddies();
        }
        else {
            if (self.ra.get("pendingShareIsIncoming"))
                JSToNativeBridge.CallNativeFunction("RejectShareRequestFromBuddy", newSharingBuddyJID);
            else
                JSToNativeBridge.CallNativeFunction("StopShare");
        }
    }

    this.ResetSelectedBuddies = function() {
        // console.log("inside function ResetSelectedBuddies");
        var buddyList = self.ra.get("buddyList");
        for (var i = buddyList.length - 1; i >= 0; i--) {
            if (buddyList[i].isSelected)
                self.ra.set("buddyList." + i + ".isSelected", false);
        };
        self.ra.set("numSelectedBuddies", 0);
    }

    this.CanBuddyBeSharedWith = function(buddyInfo) {
        // console.log("inside function CanBuddyBeSharedWith");
        if (buddyInfo.show == BuddyListManager.JabberStatusShow.DoNotDisturb)
        {
            console.log("ToggleShare: busy for: " + buddyInfo.bareJid);
            JSToNativeBridge.CallNativeFunction("ShowMainWindow");
            BuddyList.ShowCantConnectDialog(buddyInfo, BuddyList.CantConnectReasons.BuddyIsBusy);
            return false;
        }
        else if (buddyInfo.version != self.ra.get("OptionsManager.version"))
        {
            console.log("ToggleShare: version mismatch for:" + buddyInfo.bareJid);
            JSToNativeBridge.CallNativeFunction("ShowMainWindow");
            BuddyList.ShowCantConnectDialog(buddyInfo, BuddyList.CantConnectReasons.BuddyIsOnOldVersion);
            return false;            
        }
        else if (!self.IsPaidUser(buddyInfo.paymentType) && !self.IsPaidUser()) // they are unpaid and we are unpaid
        {
            JSToNativeBridge.CallNativeFunction("ShowMainWindow");
            BuddyList.ShowCantConnectDialog(buddyInfo, BuddyList.CantConnectReasons.TheyAreUnpaid);
            return false;
        }

        return true;
    }

    this.AddBuddyToSession = function(buddyJID) {
        // console.log("inside function AddBuddyToSession");
        var buddyInfo = self.GetBuddyWithJID(buddyJID);            
        if (!buddyInfo.isOnline)
            return;

        var canBuddyBeSharedWith = self.CanBuddyBeSharedWith(buddyInfo);
        if (!canBuddyBeSharedWith)
            return;

        JSToNativeBridge.CallNativeFunction("AddBuddyToSession", buddyJID);
    }

    this.UserRespondedToShareRequest = function(invitingBuddyJID, didAccept) {
        // console.log("inside function UserRespondedToShareRequest");
        self.ra.set("pendingShareIsIncoming", false);
        self.StopShareSound(true);        
        if (didAccept)
        {
            if (self.ra.get("OptionsManager.sessionType") == BuddyListManager.SessionType.Voice)
                JSToNativeBridge.CallNativeFunction("ShowMainWindow");

            JSToNativeBridge.CallNativeFunction("AcceptShareRequestFromBuddy", invitingBuddyJID);
        }
        else
        {
            JSToNativeBridge.CallNativeFunction("RejectShareRequestFromBuddy", invitingBuddyJID);
        }
    }

    this.StartSessionWithBuddies = function(selectedBuddies, sessionType) {
        // console.log("inside function StartSessionWithBuddies");
        self.ra.set("OptionsManager.isWaitingForScreenShare", false);
        self.ResetAllSessionStates();

        if (sessionType == BuddyListManager.SessionType.Voice)
        {
            self.ra.set("OptionsManager.isScreenShareMuted", true);
            self.ra.set("OptionsManager.isVoiceChatMuted", false);
        }
        else
        {
            self.ra.set("OptionsManager.isScreenShareMuted", false);
            self.ra.set("OptionsManager.isVoiceChatMuted", self.ra.get("OptionsManager.isVoiceChatMutedOnScreenShare"));
        }

        JSToNativeBridge.CallNativeFunction("StartSessionWithBuddies", selectedBuddies.map(function(buddy){return buddy.xmppJid ? buddy.xmppJid : buddy.bareJid}), sessionType);
    }

    this.SessionDidStart = function(sessionType, isMaster) {
        // console.log("inside function SessionDidStart");
        self.ra.set("OptionsManager.sessionType", sessionType);
        self.ra.set("isSlave", !isMaster);
        if (sessionType == BuddyListManager.SessionType.Screen && isMaster)
        {
            self.ra.set("isUpdatingOptionsManager", true);
            self.ra.set("OptionsManager.isScreenShareMuted", false);
            self.ra.set("isUpdatingOptionsManager", false);
        }
    }

    this.SetSessionType = function(sessionType) {
        console.log("SetSessionType: " + sessionType);
        self.ra.set("OptionsManager.sessionType", sessionType);
    }

    this.ChangeActiveSessionId = function(newSessionId) {
        // console.log("inside function ChangeActiveSessionId");
        self.SanitizeSessionStates(newSessionId);
        self.ra.set("savedSessionStates." + newSessionId + ".buddies", Utils.copyHash(self.ra.get("savedSessionStates."+self.ra.get("activeSessionId")+".buddies")));
        self.nextSessionId = newSessionId;
    }
    
    this.ChooseScreenCancelled = function() {
        console.log("ChooseScreenCancelled");
        self.ra.set("OptionsManager.isWaitingForScreenShare", false);
    }

    this.ScreenShareDidStart = function() {
        console.log("ScreenShareDidStart");
        self.ra.set("OptionsManager.isWaitingForScreenShare", false);
    }

    this.SetSessionIdToReady = function(sessionId) {
        // console.log("inside function SetSessionIdToReady");
        self.SanitizeSessionStates(sessionId);
        if (self.ra.get("savedSessionStates."+sessionId+".state") == 0)
        {
            console.log("Transitioning session " + sessionId + " from not ready to ready");
            self.ra.set("savedSessionStates."+sessionId+".state", 1);
            if (self.IsSessionIdNextAndReady(sessionId))
                self.SwapUIStates();
        }
        else
            console.log("Not transitioning to ready state since already ready :"+sessionId);
        
    }

    this.ReinstatePreviousSessionStatesToUI = function() {
        self._actualSwapUIStatesToSessionId(self.ra.get("activeSessionId"));
    }

    this.SwapUIStates = function()  {
        // console.log("inside function SwapUIStates");
        if (self.nextSessionId == self.ra.get("activeSessionId"))
        {
            console.log("Ignoring swap since session id already swapped : " + self.nextSessionId);
            return;
        }

        console.log("UI Swapping out state : " + self.ra.get("activeSessionId") + " with new state : " +self.nextSessionId);
        console.log("Saved session states are: "+Utils.objectToReadableString(self.ra.get("savedSessionStates")));
        
        this._actualSwapUIStatesToSessionId(self.nextSessionId);
        self.ra.set("activeSessionId", self.nextSessionId);
        self.nextSessionId = 0;
    }

    this._actualSwapUIStatesToSessionId = function(sessionID) {
        var newBuddyStates = self.ra.get("savedSessionStates." + sessionID + ".buddies");
        if (newBuddyStates !== undefined)
        {
            var buddyList = self.ra.get("buddyList");
            buddyList.forEach(function(buddy) {
                if (!(buddy.sharingStatus == BuddyListManager.SharingStatus.Sharing && newBuddyStates[buddy.bareJid] == BuddyListManager.SharingStatus.Pending))
                    buddy.sharingStatus = newBuddyStates[self.JidToRactiveFriendlyKey(buddy.bareJid)];
            });
            self.ra.set("buddyList", buddyList);
        }        
    }

    this.SwitchToSessionStateId = function(sessionId) {
        // console.log("inside function SwitchToSessionStateId");
        if (sessionId <= 0)
        {
            console.log("Cannot switch to session Id  : "+sessionId);
            return;
        }
        
        console.log("Switching to Session Id " + sessionId);
        self.SanitizeSessionStates(sessionId);
        if (sessionId == self.ra.get("activeSessionId") && self.nextSessionId == 0)
        {
            console.log("Not switching sessions since this one is already active : " + self.ra.get("activeSessionId"));
            return;
        }

        self.nextSessionId = sessionId;
        if (self.IsSessionIdNextAndReady(sessionId))
            self.SwapUIStates();
    }

    this.IsSessionIdNextAndReady = function(sessionId) {
        // console.log("inside function IsSessionIdNextAndReady");
        if (self.ra.get("savedSessionStates."+sessionId) !== undefined)
        {
            var isactive = ((self.nextSessionId == sessionId) && (self.ra.get("savedSessionStates."+sessionId+".state") == 1));
            console.log("Session id " + sessionId + "is active: "+isactive);
            return isactive;
        }
        else
        {
            console.log("Session id " + sessionId + "is definitely not active");
            return false;
        }
    }

    this.SanitizeSessionStates = function(sessionId) {
        // console.log("inside function SanitizeSessionStates");
        console.log("Santizing session state "+sessionId);
        if (self.ra.get("savedSessionStates." + sessionId) === undefined)
        {
            self.ra.set("savedSessionStates."+sessionId, {});
            var buddyStates = {};
            self.ra.get("buddyList").forEach(function(buddy) {
                buddyStates[self.JidToRactiveFriendlyKey(buddy.bareJid)] = self.SharingStatus.None;
            });
            self.ra.set("savedSessionStates."+sessionId+".buddies", buddyStates);
            self.ra.set("savedSessionStates."+sessionId+".state", 0);
            console.log("Session id "+sessionId+" doesnt exist so creating one");
        }
        else
        {
            console.log("Not sanitizing session id "+sessionId);
        }
    }


    this.ResetSessionState = function(sessionId) {
        // console.log("inside function ResetSessionState");
        console.log("Resetting session id : "+sessionId);

        if (self.ra.get("savedSessionStates."+sessionId) !== undefined)
        {
            var sss = self.ra.get("savedSessionStates");
            delete sss[sessionId];
            self.ra.set("savedSessionStates", sss);
        }

        // self.SanitizeSessionStates(sessionId);
        if (sessionId == self.ra.get("activeSessionId"))
        {
            console.log("Active session just died with id : "+sessionId);
            self.ra.set("activeSessionId", 0);
        }
    }

    this.ResetAllSessionStates = function() {
        // console.log("inside function ResetAllSessionStates");
        console.log("Reset all session states");
        self.ra.set("savedSessionStates", {});
        self.ra.set("activeSessionId", 0);
        self.nextSessionId = 0;
    }

    this.JidToRactiveFriendlyKey = function (jid) {
        return jid.replace("xmpp0.powwow.cc", "xmpp0powwowcc");
    }

    this.RactiveFriendlyKeyToJid = function (key) {
        return key.replace("xmpp0powwowcc", "xmpp0.powwow.cc");
    }

    this.SetBuddyStates = function(buddyStates, sessionId) { // {jid1: state1, jid2: state2, ...}
    // console.log("inside function SetBuddyStates");
        self.SanitizeSessionStates(sessionId);

        var sss = self.ra.get("savedSessionStates");
        var activeBuddyList = self.ra.get("buddyList");
        Object.keys(buddyStates).forEach(function(buddyJid) {
            var callbackFunction = function(buddy) {
                // console.log("inside function callbackFunction");
                sss[sessionId]["buddies"][self.JidToRactiveFriendlyKey(buddyJid)] = buddyStates[buddyJid];

                // if we're in the active session, modify the real buddy list, but don't set a currently sharing buddy to pending
                // if (self.IsSessionIdNextAndReady(sessionId)) {
                if (self.ra.get('activeSessionId') == sessionId) //this should be the current session, since otherwise the incoming share window would never get closed!
                {
                    if (buddyStates[buddyJid] == BuddyListManager.SharingStatus.None)
                        IncomingShareWindowManager.CloseIncomingShareWindowForBuddy(buddyJid);
                    for (var i = activeBuddyList.length - 1; i >= 0; i--) {
                        if (activeBuddyList[i].bareJid == buddyJid) {
                            if (activeBuddyList[i].sharingStatus == BuddyListManager.SharingStatus.Sharing && buddyStates[buddyJid] == BuddyListManager.SharingStatus.Pending)
                                console.log("Not setting pending buddy since session is active : "+self.ra.get("activeSessionId")+" != "+sessionId);
                            else if (activeBuddyList[i].sharingStatus != buddyStates[buddyJid])
                                activeBuddyList[i].sharingStatus = buddyStates[buddyJid];
                        }
                    };
                }
                self.ra.toggle("updateUIsignal"); // trigger ractive, maybe a better way to do this
            };

            BuddyListManager.GetBuddyWithJID(buddyJid, callbackFunction);
        });
        self.ra.set("buddyList", activeBuddyList);
        self.ra.set("savedSessionStates", sss);
    }

    // this.GetBuddyListWithSharingStateMask = function(sharingMask, buddyList) {
        // console.log("inside function GetBuddyListWithSharingStateMask");
    //     if (!buddyList)
    //         buddyList = self.ra.get("buddyList");
    //     return buddyList.filter(function (buddy) { 
    //         return (buddy.sharingStatus & sharingMask);
    //     });
    // }

    this.GetBuddyListWithSharingStateMask = function(sharingMask) {
        // console.log("inside function GetBuddyListWithSharingStateMask");
        if (self.ra.get("activeSessionId") == 0)   //FIXME: Check what happens in the beginning of time...(First share)
            return [];
        var jidsToStates = self.ra.get("savedSessionStates."+self.ra.get("activeSessionId")+".buddies");
        var filteredJids = Object.keys(jidsToStates).filter(function(jid) {
            return (jidsToStates[jid] & sharingMask);
        });
        var filteredBuddies = filteredJids.map(function(jid) {
            return self.GetBuddyWithJID(self.RactiveFriendlyKeyToJid(jid));
        });
        return filteredBuddies;
    }

    this.GetBuddyListLengthWithSharingStateMask = function(sharingMask) {
        // console.log("inside function GetBuddyListLengthWithSharingStateMask");
        var length = 0;
        if (self.ra.get("activeSessionId") > 0) {
            var jidsToStates = self.ra.get("savedSessionStates."+self.ra.get("activeSessionId")+".buddies");
            if (jidsToStates !== undefined) {
                var jids = Object.keys(jidsToStates);
                for (var i = jids.length - 1; i >= 0; i--) {
                    if (jidsToStates[jids[i]] & sharingMask) {
                        length++;
                    }
                }
            }
        }
        return length;
    }

    this.GetProfilePicBackgroundStyleForBuddy = function(buddy) {
        var style = "background-image: "
        if (buddy) {
            // if (buddy.bareJid)
            //     style += "url('https://screenhero-avatars.s3.amazonaws.com/" + buddy.bareJid.split("@")[0] + ".png'), ";
            // if (buddy.email)
            //     style += "url('http://www.gravatar.com/avatar/" + (md5(buddy.email)) + "?d=404'), ";
            if (buddy.profilePicURL)
                style += "url('" + (buddy.profilePicURL) + "'), ";
            if (self.isAwesomium)
                style += "url('img/avatar.svg')";
            else
                style += "url('data:image/svg+xml;base64," + "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4NCjwhLS0gR2VuZXJhdG9yOiBBZG9iZSBJbGx1c3RyYXRvciAxNS4xLjAsIFNWRyBFeHBvcnQgUGx1Zy1JbiAuIFNWRyBWZXJzaW9uOiA2LjAwIEJ1aWxkIDApICAtLT4NCjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+DQo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkxheWVyXzEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4Ig0KCSB3aWR0aD0iMTAwcHgiIGhlaWdodD0iMTAwcHgiIHZpZXdCb3g9IjAgMCAxMDAgMTAwIiBlbmFibGUtYmFja2dyb3VuZD0ibmV3IDAgMCAxMDAgMTAwIiB4bWw6c3BhY2U9InByZXNlcnZlIj4NCjxyZWN0IGZpbGw9IiM5OUQ0RUYiIHdpZHRoPSIxMDAiIGhlaWdodD0iMTAwIi8+DQo8cGF0aCBmaWxsPSIjRkZGRkZGIiBkPSJNNTAuMDAxLDI2Ljk0MWM1Ljg2OCwwLDEwLjY0Miw0Ljc3NCwxMC42NDIsMTAuNjQzYzAsNS44NjgtNC43NzMsMTAuNjQyLTEwLjY0MiwxMC42NDINCgljLTUuODY5LDAtMTAuNjQzLTQuNzc0LTEwLjY0My0xMC42NDJDMzkuMzU4LDMxLjcxNSw0NC4xMzIsMjYuOTQxLDUwLjAwMSwyNi45NDEgTTUwLjAwMSwxOS44NDYNCgljLTkuNzk4LDAtMTcuNzM4LDcuOTQtMTcuNzM4LDE3LjczOGMwLDkuNzk3LDcuOTQsMTcuNzM3LDE3LjczOCwxNy43MzdjOS43OTcsMCwxNy43MzctNy45NCwxNy43MzctMTcuNzM3DQoJQzY3LjczOCwyNy43ODYsNTkuNzk4LDE5Ljg0Niw1MC4wMDEsMTkuODQ2TDUwLjAwMSwxOS44NDZ6Ii8+DQo8cGF0aCBmaWxsPSIjRkZGRkZGIiBkPSJNNTAuMDAxLDU1LjMyMWM5Ljc5NywwLDE3LjczNyw3Ljk0LDE3LjczNywxNy43MzhIMzIuMjYzQzMyLjI2Myw2My4yNjIsNDAuMjAzLDU1LjMyMSw1MC4wMDEsNTUuMzIxDQoJIE01MC4wMDEsNDguMjI2Yy0xMy42OTEsMC0yNC44MzMsMTEuMTQyLTI0LjgzMywyNC44MzNjMCwzLjkxOCwzLjE3Nyw3LjA5NSw3LjA5NSw3LjA5NWgzNS40NzZjMy45MTgsMCw3LjA5NS0zLjE3Nyw3LjA5NS03LjA5NQ0KCUM3NC44MzMsNTkuMzY4LDYzLjY5Miw0OC4yMjYsNTAuMDAxLDQ4LjIyNkw1MC4wMDEsNDguMjI2eiIvPg0KPC9zdmc+DQo=')";
        }
        // style += "url('https://screenhero.com/img/default.png')";
        return style;
    }

    this.GetSelectedBuddies = function() {
        // console.log("inside function GetSelectedBuddies");
        return self.ra.get("buddyList").filter(function (buddy) {
            return buddy.isSelected; 
        });
    }

    this.SetBuddyThatIsMe = function(newBuddyThatIsMe) {
        // console.log("inside function SetBuddyThatIsMe");
        newBuddyThatIsMe = Utils.buddyWithSanitizedProfilePic(newBuddyThatIsMe);
        self.ra.set("OptionsManager.buddyThatIsMe", newBuddyThatIsMe);
    }

    this.SetLoginCredentials = function(password, shouldSavePassword) {
        // console.log("inside function SetLoginCredentials");
        self.ra.set("OptionsManager.password", password);
        self.ra.set("OptionsManager.shouldRememberPassword", shouldSavePassword);
    }

    this.SetBuddyList = function(newBuddyList) {
        // console.log("inside function SetBuddyList");
        console.log("setting n buddies:" + newBuddyList.length);
        for (var i = newBuddyList.length - 1; i >= 0; i--) {
            newBuddyList[i] = Utils.buddyWithSanitizedProfilePic(newBuddyList[i]);
        };
        self.ra.set("buddyList", newBuddyList);
    }

    this.AddBuddyToList = function(buddyToAdd) {
        // console.log("inside function AddBuddyToList");
        var found = false;
        var buddyList = self.ra.get("buddyList");
        for (var i = buddyList.length - 1; i >= 0 && !found; i--) {
            var buddy = buddyList[i];
            if (buddy.bareJid == buddyToAdd.bareJid) {
                self.ra.set("buddyList." + i + ".name", buddyToAdd.name);
                self.ra.set("buddyList." + i + ".email", buddyToAdd.email);
                self.ra.set("buddyList." + i + ".profilePicURL", buddyToAdd.profilePicURL);

                found = true;
            }
        }
        if (!found) {
            buddyList.push(buddyToAdd);
            self.ra.set("buddyList", buddyList);
        }
    }

    this.RemoveBuddyFromList = function(jid) {
        // console.log("inside function RemoveBuddyFromList");
        var buddyList = self.ra.get("buddyList");
        for (var i = buddyList.length - 1; i >= 0; i--) {
            var buddy = buddyList[i];
            if (buddy.bareJid == jid) {
                buddyList.splice(i, 1);
                self.ra.set("buddyList", buddyList);                
            }
        };
    }

    this.UpdateBuddyList = function(newBuddyList) {
        // console.log("inside function UpdateBuddyList");
        if (self.ra.get("buddyList").length == 0) {
            // console.log("setting buddy list since len = 0");
            self.SetBuddyList(newBuddyList);
        }
        else {
            // console.log("updating buddy list since len > 0");
            var buddyList = self.ra.get("buddyList");
            var dirty = false;
            newBuddyList.forEach(function (newBuddy) {
                newBuddy = Utils.buddyWithSanitizedProfilePic(newBuddy);
                var found = false;
                for (var i=0; i<buddyList.length; i++) {
                    if (buddyList[i].bareJid == newBuddy.bareJid) {
                        if (newBuddy.profilePicURL != Utils.getDefaultAvatarPicURL() && buddyList[i].profilePicURL != newBuddy.profilePicURL) {
                            buddyList[i].profilePicURL = newBuddy.profilePicURL;
                            dirty = true;
                        }
                        if (buddyList[i].paymentType != newBuddy.paymentType) {
                            buddyList[i].paymentType = newBuddy.paymentType;
                            dirty = true;
                        }
                        found = true;
                    }
                }
                if (!found) {
                    buddyList.push(newBuddy);
                    dirty = true;
                }
            });
            if (dirty)
                self.ra.set("buddyList", buddyList);
        }
        self.SaveBuddyList();
    }

    this.SaveBuddyList = function() {
        // console.log("inside function SaveBuddyList");
        if (self.saveBuddyListTimeoutHandle)
            clearTimeout(self.saveBuddyListTimeoutHandle);
        var buddyList = self.ra.get("buddyList");
        self.saveBuddyListTimeoutHandle = setTimeout(function() {
            JSToNativeBridge.CallNativeFunction("UpdateOptionsManager", {buddyList: buddyList});
            JSToNativeBridge.CallNativeFunction("SaveSettings");
        }, 1000);
    }

    this.ToggleVoiceChatMute = function() {
        // console.log("inside function ToggleVoiceChatMute");
        self.ra.toggle("OptionsManager.isVoiceChatMuted");

        if (self.ra.get("OptionsManager.sessionType") == BuddyListManager.SessionType.Screen)  // only change persisted mute setting if in a screen share
            self.ra.toggle("OptionsManager.isVoiceChatMutedOnScreenShare");
    }

    this.ToggleScreenShareMute = function() {
        console.log("ToggleScreenShareMute, sessionType = " + self.ra.get("OptionsManager.sessionType") + ", isSlave=" + self.ra.get("isSlave") + ", isWaitingForScreenShare: " + self.ra.get("OptionsManager.isWaitingForScreenShare"));
        if ((self.ra.get("OptionsManager.sessionType") == BuddyListManager.SessionType.Screen && self.ra.get("isSlave")) || // switch presenter
            (self.ra.get("OptionsManager.sessionType") == BuddyListManager.SessionType.Voice)) // voice call
        {
            if (!self.ra.get("OptionsManager.isWaitingForScreenShare"))
            {
                self.ra.set("OptionsManager.isWaitingForScreenShare", true);
                JSToNativeBridge.CallNativeFunction("StartChooseScreen");
            }
        }
        else
            self.ra.toggle("OptionsManager.isScreenShareMuted");
    }

    this.OnUserChoseSignOut = function() 
    {
        if (self.IsInShare())
        {
            if (self.ra.get("pendingShareIsIncoming"))
                JSToNativeBridge.CallNativeFunction("RejectShareRequestFromBuddy", newSharingBuddyJID);
            else
                JSToNativeBridge.CallNativeFunction("StopShare");
        }
        else 
        {
            self.ResetAllSessionStates();            
        }   

        self.ra.set("OptionsManager.buddyThatIsMe.paymentType", self.ra.get("PaymentType.NoBillingData"));
        self.ra.set("OptionsManager.buddyThatIsMe", null, function () {
            self.ra.set("showNoBuddiesView", false);
            self.ResetSelectedBuddies();
        });
    }

    this.XmppDidDisconnect = function() {
        // console.log("inside function XmppDidDisconnect");
    }

    this.ShowNoBuddiesView = function() {
        // console.log("inside function ShowNoBuddiesView");
        self.ra.set("showNoBuddiesView", true);
    }

    this.GetClientProtocolVersion = function() {
        // console.log("inside function GetClientProtocolVersion");
        return self.ra.get("OptionsManager.version");
    }

    this.GetPassword = function() {
        // console.log("inside function GetPassword");
        return self.ra.get("OptionsManager.password");
    }

    this.GetBareJID = function() {
        // console.log("inside function GetBareJID");
        return self.ra.get("OptionsManager.buddyThatIsMe.bareJid").split('@', 1);
    }

    this.HandleTemporaryDisconnection = function() {
        if (!self.ra.get("isReconnecting"))
        {
            self.ra.set("isReconnecting", true);
        }
    }

    this.HandleReconnection = function() {
        if (self.ra.get("isReconnecting"))
        {
            self.ra.set("isReconnecting", false);        
        }
    }

    this.StopShareSound = function(shouldStopSound) {
        console.log("StopShareSound: " + shouldStopSound);
        if (!ResourceManager.launchModuleName) { // don't do any share sounds unless main module
            if (!shouldStopSound) {
                if (!self.ra.get("OptionsManager.isRingingMuted")) {
                    self.isPlayingShareSound = true;
                    ResourceManager.playSound("bells1.wav", true);
                }
            }
            else if (self.isPlayingShareSound && shouldStopSound) {
                self.isPlayingShareSound = false;
                ResourceManager.stopSound("bells1.wav");  // stopping sound because share ended
            }
        }
    }
}
