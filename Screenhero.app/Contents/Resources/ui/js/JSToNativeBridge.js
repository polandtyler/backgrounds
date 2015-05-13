var JSToNativeBridge = (function () {
    var nativeObject = null;
    var upstreamQueue = [];

    var public = {
        Init: function(newNativeObject) {
            nativeObject = newNativeObject;
        },

        CallWebFunction: function (funcName, args, callback) {
            //JSToNativeBridge.CallWebFunction("function", [0,1,2,3], function(response){console.log(response);})
            //This calls a post method in a private area of the public API
            // The method takes two parameters:
            //    1) a JSONRPC string
            //    2) an HMAC digest of the string as a cryptographic signature
            // For security, this JSONRPC object is accompanied by a cryptographic signature
            //  that is signed with a secret shared between us and the server,
            //  namely, the hash of the current user's password.
            // So, there is a bit of setup involved.
            //var method = eval("nativeObject." + funcName);
            var censorLogs = false;
            var params = [];
            for (var i=0; i<args.length; i++)
                params.push(encodeURIComponent(args[i]));
            var jsonRPC = Utils.createJsonRpcObjectFromObject({method: funcName, params: params});

            //start setting up the parts to be digested
            var requestStr = "req="+JSON.stringify(jsonRPC);
            
            //now let's use this hash to create an HMAC digest to sign the request with
            var path = "/v1/client/rpc"

            // var basicAuth = Base64.encode(BuddyListManager.GetBareJID() + ":" + BuddyListManager.GetPassword()); //This is from Strophe.
            // console.log(basicAuth);
            //console.log(nonce)
            //console.log(digest)
            //And, let's post that sucker!
            if (funcName == "sessionKey")
            {
                censorLogs = true;
            }
            Utils.postWithAuth(path, requestStr, callback, censorLogs);
        },

        CallNativeFunction: function (funcName) {
            if (nativeObject)
            {
                var shouldLog = (funcName != "Log");
                var method = eval("nativeObject." + funcName);
                var params = [];
                for (var i=1; i<arguments.length; i++)
                    params.push(arguments[i]);
                var jsonRPC = Utils.createJsonRpcObjectFromObject({method: funcName, params: params});
                if (shouldLog)
                    Utils.logJsonRPC(jsonRPC, true);
                if (Utils.isAwesomium) {
                    try {
                        nativeObject.CallNativeFunction(JSON.stringify(jsonRPC));
//                        if (shouldLog)
//                            console.log("Call complete : "+funcName);
                    }
                    catch (e) {
                        console.log("Exception in JS->Native: " + e);
                    }
                }
                else
                    nativeObject.CallNativeFunction(JSON.stringify(jsonRPC));
            }
            // else
            //     alert("oops: " + funcName + " + " + arguments);
        },
        // ACCOUNT CREATION

        // 1) this is the first thing that happens: js tells c# "hey, i've loaded, you can send me credentials now"
        SignalReadyForLaunch: function () {
            // tells c# it can now call launch with credentials

            if (window.nativeObject) {
                public.Init(window.nativeObject);
                window.nativeObject = undefined;
            }

            if (nativeObject && nativeObject.CallNativeFunction)
                nativeObject.CallNativeFunction(JSON.stringify(Utils.createJsonRpcObjectFromObject({method: "SignalReadyForLaunch"})));
            else (window.setTimeout(function () { 
                public.SignalReadyForLaunch();
            }, 50));
                // console.log("no nativeObject :(");
        },
    }
    return public;
})();