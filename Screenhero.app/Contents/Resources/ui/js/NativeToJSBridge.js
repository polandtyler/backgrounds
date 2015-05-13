// using private / public module pattern as described in http://addyosmani.com/largescalejavascript/

var NativeToJSBridge = (function () {

    var APIVersion = 3;

    var SourceTypes = {
        Native: 0,
        WebAPI: 1
    };

    var ErrorCodes = {
        OK: 0,
        JSONParseError: 1,
        NotJSONRPCObject: 2,
        InvalidJSONRPCObject: 3,
        CallDoesNotExist: 4,
        CallNotPermitted: 5,
        CallRaisedException: 6
    };

    // public
    var public = {
        SourceTypes: SourceTypes,

        ErrorCodes: ErrorCodes,

        performJsonRpcWithSource: function(jsonRPCString, sourceType) {
            if(sourceType == undefined) { //if left off, assume the worst
                sourceType = SourceTypes.WebAPI;
            }

            //validate returns either an JSONRPC error response, or our deserialized JSONRPC call.
            var jsonRPC = validateAndParseJSONRPC(jsonRPCString);
            if(jsonRPC.hasOwnProperty("error")) {
                //this means we got invalid JSON
                return JSON.stringify(jsonRPC);
            }

            var jsonRPCResponse = {
                jsonrpc: "2.0",
                id: jsonRPC.id
            }
            //just in case we need it
            var jsonRPCError = {
                code: ErrorCodes.OK,
                message: "OK"
            }
            
            //now, check if we are permitted to call this function
            if(!permittedMethods[sourceType].hasOwnProperty(jsonRPC.method)) {
                console.log(jsonRPC.method + " not permitted from source " + sourceType);
                jsonRPCError.code = ErrorCodes.CallNotPermitted;
                jsonRPCError.message = "Call not permitted";
                jsonRPCResponse.error = jsonRPCError;
                return JSON.stringify(jsonRPCResponse);
            }

            //Finally, we call the thing
            //performJSONRPC returns
            //setTimeout(performJSONRPC(jsonRPC), 10);
            jsonRPCResponse = performJSONRPC(jsonRPC, sourceType);
            return JSON.stringify(jsonRPCResponse);
        },

        setNativeObject: function(newNativeObject) {
            JSToNativeBridge.Init(newNativeObject);
        },

        WebDialogCallback: function (uuid, tag, index) {
            //use the UUID and index to look up the URL to hit
            var responseArray = PopupHash[uuid];
            delete PopupHash[uuid];
            if(responseArray)
            {
                Utils.postWithAuth(responseArray[index]["path"], decodeURIComponent(responseArray[index]["query"]));
            }
        }
    }
             
    var permittedMethods = {};
    //by default, methods not enumerated here are treated as false;
    permittedMethods[SourceTypes.Native] = {};
    permittedMethods[SourceTypes.Native]["EnableDebugging"] = Utils.EnableDebugging;
    permittedMethods[SourceTypes.Native]["ShowWelcomeView"] = Main.ShowWelcomeView;
    permittedMethods[SourceTypes.Native]["SetUpdateIsDownloading"] = BuddyList.SetUpdateIsDownloading;
    permittedMethods[SourceTypes.Native]["SetInstallationDidStart"] = BuddyList.SetInstallationDidStart;
    permittedMethods[SourceTypes.Native]["SetConnectionQuality"] = BuddyListManager.SetConnectionQuality;
    permittedMethods[SourceTypes.Native]["ShowChatWindowForBuddy"] = ChatWindowManager.ShowChatWindowForBuddy;
    permittedMethods[SourceTypes.Native]["SetBuddyStates"] = BuddyListManager.SetBuddyStates;    
    permittedMethods[SourceTypes.Native]["ChangeActiveSessionId"] = BuddyListManager.ChangeActiveSessionId;    
    permittedMethods[SourceTypes.Native]["ResetSessionState"] = BuddyListManager.ResetSessionState;
    permittedMethods[SourceTypes.Native]["SwitchToSessionStateId"] = BuddyListManager.SwitchToSessionStateId;
    permittedMethods[SourceTypes.Native]["SetSessionIdToReady"] = BuddyListManager.SetSessionIdToReady;
    permittedMethods[SourceTypes.Native]["ResetAllSessionStates"] = BuddyListManager.ResetAllSessionStates;
    permittedMethods[SourceTypes.Native]["DisableGroupSharing"] = BuddyListManager.DisableGroupSharing;    
    permittedMethods[SourceTypes.Native]["SetZoom"] = function (newZoom) { $("body").css("zoom", newZoom); };
    permittedMethods[SourceTypes.Native]["RefreshBuddyList"] = BuddyListManager.SetBuddyList;
    permittedMethods[SourceTypes.Native]["ShowDialog"] = BuddyList.ShowDialog;
    permittedMethods[SourceTypes.Native]["ShowPopup"] = BuddyList.ShowPopup;
    permittedMethods[SourceTypes.Native]["ShowIncomingShare"] = BuddyListManager.IncomingShareReceivedForBuddy;
    permittedMethods[SourceTypes.Native]["LaunchWithSignIn"] = LoginView.LaunchWithSignIn;
    permittedMethods[SourceTypes.Native]["LaunchWithSignup"] = LoginView.LaunchWithSignup;
    permittedMethods[SourceTypes.Native]["InitializeOptionsManager"] = BuddyListManager.InitializeOptionsManager;
    permittedMethods[SourceTypes.Native]["CreateAccountResponse"] = LoginView.CreateAccountResponse;
    permittedMethods[SourceTypes.Native]["SessionDidStart"] = BuddyListManager.SessionDidStart;
    permittedMethods[SourceTypes.Native]["SetSessionType"] = BuddyListManager.SetSessionType;
    permittedMethods[SourceTypes.Native]["ShowNoBuddiesView"] = BuddyListManager.ShowNoBuddiesView;
    permittedMethods[SourceTypes.Native]["ChooseScreenCancelled"] = BuddyListManager.ChooseScreenCancelled;
    permittedMethods[SourceTypes.Native]["ScreenShareDidStart"] = BuddyListManager.ScreenShareDidStart;
    permittedMethods[SourceTypes.Native]["UpdateAvailable"] = UpdateManager.UpdateAvailable;
    permittedMethods[SourceTypes.Native]["MainWindowActivated"] = Main.MainWindowActivated;
    permittedMethods[SourceTypes.Native]["ChangeEmail"] = function (email) {
        JSToNativeBridge.CallWebFunction("changeEmail", [email], function(result) {
            if(result == 'ok') {
                BuddyList.ShowPopup({body: "We've sent you an email to verify your new email address.", title: "Verification email sent"});
            }
            else {
                BuddyList.ShowPopup({body: "We encountered an error attempting to update yoru email address to "+email+". Please try again.", title: "Error changing email", kind: "error", timeout:0});
            }
        });
    };
    permittedMethods[SourceTypes.Native]["SendSessionMessageToJidOnChannel"] = XmppManager.SendSessionMessageToJidOnChannel;
    permittedMethods[SourceTypes.Native]["SendBuddyInviteToJid"] = XmppManager.SendBuddyInviteToJid;
    permittedMethods[SourceTypes.Native]["UpdateNetworkLocation"] = XmppManager.UpdateNetworkRegions;
    permittedMethods[SourceTypes.Native]["SetIsReachable"] = LoginView.SetIsReachable;
    permittedMethods[SourceTypes.Native]["TemporaryDisconnection"] = BuddyListManager.HandleTemporaryDisconnection;
    permittedMethods[SourceTypes.Native]["Reconnection"] = BuddyListManager.HandleReconnection;

    permittedMethods[SourceTypes.WebAPI] = {};
    permittedMethods[SourceTypes.WebAPI]["ToggleSharingSession"] = true;
    permittedMethods[SourceTypes.WebAPI]["ToggleVoiceSession"] = true;
    permittedMethods[SourceTypes.WebAPI]["IsBuddy"] = true;
    permittedMethods[SourceTypes.WebAPI]["GetClientProtocolVersion"] = true;
    permittedMethods[SourceTypes.WebAPI]["ShowWebPopup"] = true;
    permittedMethods[SourceTypes.WebAPI]["ShowWebDialog"] = true;
    permittedMethods[SourceTypes.WebAPI]["GetAPIVersion"] = true;
    permittedMethods[SourceTypes.WebAPI]["WebDialogCallback"] = true;
    permittedMethods[SourceTypes.WebAPI]["InviteBuddy"] = true;
    permittedMethods[SourceTypes.WebAPI]["UpdatePaymentStatus"] = BuddyListManager.SetPaymentType;

    //ping(), changeEmail(new_email)

    var validateAndParseJSONRPC = function (requestObjString) {
        //just in case we need it
        var jsonRPCError = {
            code: ErrorCodes.OK,
            message: "OK"
        }

        var jsonRPCResponse = {
            jsonrpc: "2.0",
            id: 0,
        }

        var requestObj = {};
        try{
            requestObj = jQuery.parseJSON(requestObjString);
        }
        catch(e)
        {
            jsonRPCError.code = ErrorCodes.JSONParseError;
            jsonRPCError.message = "invalid JSON";
            jsonRPCResponse.error = jsonRPCError;
            return jsonRPCResponse;
        }

        if(!requestObj.hasOwnProperty('id') ) {
            jsonRPCError.code = ErrorCodes.InvalidJSONRPCObject;
            jsonRPCError.message = "missing id property";
            jsonRPCResponse.error = jsonRPCError;
            return jsonRPCResponse;
        }

        jsonRPCResponse.id = requestObj.id; //we have established that there is a valid ID, so we must use it

        if(!requestObj.hasOwnProperty('jsonrpc') || parseFloat(requestObj.jsonrpc) < 2.0 ) {
            jsonRPCError.code = ErrorCodes.NotJSONRPCObject;
            jsonRPCError.message = "missing or invalid (!=2.0) jsonrpc property";
            jsonRPCResponse.error = jsonRPCError;
            return jsonRPCResponse;
        }

        if(!requestObj.hasOwnProperty('method') ) {
            jsonRPCError.code = ErrorCodes.InvalidJSONRPCObject;
            jsonRPCError.message = "missing method property";
            jsonRPCResponse.error = jsonRPCError;
            return jsonRPCResponse;
        }
        

        return requestObj;
    }

    var performJSONRPC = function (requestObj, sourceType) {
        // requestObj is a JSON-RPC object that compiles with
        //   http://www.jsonrpc.org/specification
                        
        var jsonRPCResponse = {
            jsonrpc: "2.0",
            id: requestObj.id
        }
        //just in case we need it
        var jsonRPCError = {
            code: ErrorCodes.OK,
            message: "OK"
        }

        Utils.logJsonRPC(requestObj, false);
        var methodPointer = permittedMethods[sourceType][requestObj.method]
        if (typeof(methodPointer) == "boolean")
            methodPointer = eval("" + requestObj.method);
        if (methodPointer == null)
        {
            jsonRPCError.code = ErrorCodes.CallDoesNotExist;
            jsonRPCError.message = "no method named " + requestObj.method;
            jsonRPCResponse.error = jsonRPCError;
            return jsonRPCResponse;
        }

       // console.log("starting call to "+ requestObj.method);
        if (Utils.isAwesomium) {
            try {
                retval = methodPointer.apply(this, requestObj.params);
                //everything is okey-dokey!
                jsonRPCResponse.result = retval;
            }
            catch(e) {
                console.log("Exception in JS->Native: " + e);
                jsonRPCError.code = ErrorCodes.CallRaisedException;
                jsonRPCError.message = "" + e;
                jsonRPCResponse.error = jsonRPCError;
                return jsonRPCResponse;
            }
        }
        else {
            retval = methodPointer.apply(this, requestObj.params);
            jsonRPCResponse.result = retval;            
        }

//        console.log("Call complete : " + requestObj.method)
        return jsonRPCResponse;
    }

    /* -----------------------------------*/
    /* --------->>> Cloud API <<<---------*/
    /* -----------------------------------*/

    //TODO want a way to associate a unique identifier with this share.
    var ToggleSharingSession = function (jidToShareWith) {
        JSToNativeBridge.CallNativeFunction("ShowMainWindow");        
        BuddyListManager.ToggleShareWithBuddy(jidToShareWith, BuddyListManager.SessionType.Screen);
    }

    var ToggleVoiceSession = function (jidToTalkTo) {
        JSToNativeBridge.CallNativeFunction("ShowMainWindow");        
        BuddyListManager.ToggleShareWithBuddy(jidToTalkTo, BuddyListManager.SessionType.Voice);
    }

    var GetClientProtocolVersion = function () {
        return BuddyListManager.GetClientProtocolVersion();
    }

    var GetAPIVersion = function () {
        return APIVersion;
    }

    var IsBuddy = function (jidToCheck) {
        buddy = BuddyListManager.GetBuddyWithJID(jidToCheck);
        if(buddy == null) {
            return false;
        }
        return true;
    }

    var PopupHash = {}

    // NativeToJSBridge.ShowWebPopup("Yowza!", "I can't believe you really want this.", ["Yes", "Hells yes"], [{path:"/v1/client/authorize", query:"ugh=0"}, {path:"/v1/client/authorize", query:"ugh=1"}]);
    // NativeToJSBridge.performJsonRpcWithSource('{"jsonrpc": "2.0", "method": "ShowWebPopup", "params": ["Yowza!", "I cannot believe you really want this.", ["Yes", "Hells yes"], [{"path":"/v1/client/authorize", "query":"ugh=0"}, {"path":"/v1/client/authorize", "query":"ugh=1"}], "fdsjklfjdsklfjlkds"], "id":1}', 1);

    var ShowWebDialog = function (title, message, labelArray, responseArray, uuid) {
        PopupHash[uuid] = responseArray;
        
        var dialog = {type:"dialog", source:"webRequest", uuid:uuid, tag:"webRequest", title:title, body:message, labelArray:labelArray, defaultIndex:0};
        BuddyList.ShowDialog(dialog);
    }

    var ShowWebPopup = function(body, kind, timeout) {
        var popupObj= {body: body, kind: kind, timeout: timeout};
        BuddyList.ShowPopup(popupObj);
    }

    var InviteBuddy  = function (jidToAdd) {
        JSToNativeBridge.CallNativeFunction("AddBuddyToList", jidToAdd);
    }

    return public;
})();