var Utils = new function () {
	var self = this;

    this.shouldBlockRightClick = true;
    this.isAwesomiumWin = navigator.userAgent.indexOf("winAwesomium") >= 0;
    this.isAwesomiumMac = navigator.userAgent.indexOf("macAwesomium") >= 0;
    this.isAwesomiumLinux = navigator.userAgent.indexOf("linuxAwesomium") >= 0;
    this.isAwesomium = this.isAwesomiumWin || this.isAwesomiumMac || this.isAwesomiumLinux;
    this.shouldShowBorder = this.isAwesomiumMac;
    this.isDebuggingEnabled = false;
    this.isAutoAcceptEnabled = false;
    this.useFakeXmppServer = false;
    this.shouldLogJsonRpc = false;
    this.shouldDetectChatUrls = true;
    this.apiServerURI = "https://secure.screenhero.com";
    this.billingServerURI = "http://www.screenhero.com";

    if (this.isAwesomiumMac) {
    	console = { 
    		log: function(msg) {
    			JSToNativeBridge.CallNativeFunction("Log", msg); 
    		},
    		warn: function(msg) {
    			JSToNativeBridge.CallNativeFunction("Log", "Warning: " + msg);
    		}
    	};
    }

    this.diffArray = function(b, a) {
        return b.filter(function(i) {return !(a.indexOf(i) > -1);});
    };

    this.copyHash = function(hash) {
    	var newObj = {};
		for( var key in hash )
			newObj[ key ] = hash[ key ];
		return newObj;
    }

	this.getQueryParameterByName = function (name) {
	    name = name.replace(/[\[]/, "\\\[").replace(/[\]]/, "\\\]");
	    var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
	        results = regex.exec(location.search);
	    return results == null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
	}
	this.buddyWithSanitizedProfilePic = function (buddy) {
		if (!buddy)
			return buddy;
		if (!buddy.profilePicURL)
		{
			if (self.isAwesomium)
				buddy.profilePicURL = "img/avatar.svg";
			else
				buddy.profilePicURL = "data:image/svg+xml;base64," + "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4NCjwhLS0gR2VuZXJhdG9yOiBBZG9iZSBJbGx1c3RyYXRvciAxNS4xLjAsIFNWRyBFeHBvcnQgUGx1Zy1JbiAuIFNWRyBWZXJzaW9uOiA2LjAwIEJ1aWxkIDApICAtLT4NCjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+DQo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkxheWVyXzEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4Ig0KCSB3aWR0aD0iMTAwcHgiIGhlaWdodD0iMTAwcHgiIHZpZXdCb3g9IjAgMCAxMDAgMTAwIiBlbmFibGUtYmFja2dyb3VuZD0ibmV3IDAgMCAxMDAgMTAwIiB4bWw6c3BhY2U9InByZXNlcnZlIj4NCjxyZWN0IGZpbGw9IiM5OUQ0RUYiIHdpZHRoPSIxMDAiIGhlaWdodD0iMTAwIi8+DQo8cGF0aCBmaWxsPSIjRkZGRkZGIiBkPSJNNTAuMDAxLDI2Ljk0MWM1Ljg2OCwwLDEwLjY0Miw0Ljc3NCwxMC42NDIsMTAuNjQzYzAsNS44NjgtNC43NzMsMTAuNjQyLTEwLjY0MiwxMC42NDINCgljLTUuODY5LDAtMTAuNjQzLTQuNzc0LTEwLjY0My0xMC42NDJDMzkuMzU4LDMxLjcxNSw0NC4xMzIsMjYuOTQxLDUwLjAwMSwyNi45NDEgTTUwLjAwMSwxOS44NDYNCgljLTkuNzk4LDAtMTcuNzM4LDcuOTQtMTcuNzM4LDE3LjczOGMwLDkuNzk3LDcuOTQsMTcuNzM3LDE3LjczOCwxNy43MzdjOS43OTcsMCwxNy43MzctNy45NCwxNy43MzctMTcuNzM3DQoJQzY3LjczOCwyNy43ODYsNTkuNzk4LDE5Ljg0Niw1MC4wMDEsMTkuODQ2TDUwLjAwMSwxOS44NDZ6Ii8+DQo8cGF0aCBmaWxsPSIjRkZGRkZGIiBkPSJNNTAuMDAxLDU1LjMyMWM5Ljc5NywwLDE3LjczNyw3Ljk0LDE3LjczNywxNy43MzhIMzIuMjYzQzMyLjI2Myw2My4yNjIsNDAuMjAzLDU1LjMyMSw1MC4wMDEsNTUuMzIxDQoJIE01MC4wMDEsNDguMjI2Yy0xMy42OTEsMC0yNC44MzMsMTEuMTQyLTI0LjgzMywyNC44MzNjMCwzLjkxOCwzLjE3Nyw3LjA5NSw3LjA5NSw3LjA5NWgzNS40NzZjMy45MTgsMCw3LjA5NS0zLjE3Nyw3LjA5NS03LjA5NQ0KCUM3NC44MzMsNTkuMzY4LDYzLjY5Miw0OC4yMjYsNTAuMDAxLDQ4LjIyNkw1MC4wMDEsNDguMjI2eiIvPg0KPC9zdmc+DQo=";
		}
		else if (buddy.profilePicURL instanceof dcodeIO.ByteBuffer)
			buddy.profilePicURL = "data:image/png;base64," + buddy.profilePicURL.toBase64();
		if (!buddy.name && buddy.email)
			buddy.name = buddy.email.split("@")[0];
		if (!('isOnline' in buddy))
			buddy.isOnline = false;
		if (!('sharingStatus' in buddy))
			buddy.sharingStatus = BuddyListManager.SharingStatus.None;
		if (!('isSelected' in buddy))
			buddy.isSelected = false;
		return buddy;
	}
	this.getDefaultAvatarPicURL = function() {
		var url = "";
		if (self.isAwesomium)
			url = "img/avatar.svg";
		else
			url = "data:image/svg+xml;base64," + "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4NCjwhLS0gR2VuZXJhdG9yOiBBZG9iZSBJbGx1c3RyYXRvciAxNS4xLjAsIFNWRyBFeHBvcnQgUGx1Zy1JbiAuIFNWRyBWZXJzaW9uOiA2LjAwIEJ1aWxkIDApICAtLT4NCjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+DQo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkxheWVyXzEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4Ig0KCSB3aWR0aD0iMTAwcHgiIGhlaWdodD0iMTAwcHgiIHZpZXdCb3g9IjAgMCAxMDAgMTAwIiBlbmFibGUtYmFja2dyb3VuZD0ibmV3IDAgMCAxMDAgMTAwIiB4bWw6c3BhY2U9InByZXNlcnZlIj4NCjxyZWN0IGZpbGw9IiM5OUQ0RUYiIHdpZHRoPSIxMDAiIGhlaWdodD0iMTAwIi8+DQo8cGF0aCBmaWxsPSIjRkZGRkZGIiBkPSJNNTAuMDAxLDI2Ljk0MWM1Ljg2OCwwLDEwLjY0Miw0Ljc3NCwxMC42NDIsMTAuNjQzYzAsNS44NjgtNC43NzMsMTAuNjQyLTEwLjY0MiwxMC42NDINCgljLTUuODY5LDAtMTAuNjQzLTQuNzc0LTEwLjY0My0xMC42NDJDMzkuMzU4LDMxLjcxNSw0NC4xMzIsMjYuOTQxLDUwLjAwMSwyNi45NDEgTTUwLjAwMSwxOS44NDYNCgljLTkuNzk4LDAtMTcuNzM4LDcuOTQtMTcuNzM4LDE3LjczOGMwLDkuNzk3LDcuOTQsMTcuNzM3LDE3LjczOCwxNy43MzdjOS43OTcsMCwxNy43MzctNy45NCwxNy43MzctMTcuNzM3DQoJQzY3LjczOCwyNy43ODYsNTkuNzk4LDE5Ljg0Niw1MC4wMDEsMTkuODQ2TDUwLjAwMSwxOS44NDZ6Ii8+DQo8cGF0aCBmaWxsPSIjRkZGRkZGIiBkPSJNNTAuMDAxLDU1LjMyMWM5Ljc5NywwLDE3LjczNyw3Ljk0LDE3LjczNywxNy43MzhIMzIuMjYzQzMyLjI2Myw2My4yNjIsNDAuMjAzLDU1LjMyMSw1MC4wMDEsNTUuMzIxDQoJIE01MC4wMDEsNDguMjI2Yy0xMy42OTEsMC0yNC44MzMsMTEuMTQyLTI0LjgzMywyNC44MzNjMCwzLjkxOCwzLjE3Nyw3LjA5NSw3LjA5NSw3LjA5NWgzNS40NzZjMy45MTgsMCw3LjA5NS0zLjE3Nyw3LjA5NS03LjA5NQ0KCUM3NC44MzMsNTkuMzY4LDYzLjY5Miw0OC4yMjYsNTAuMDAxLDQ4LjIyNkw1MC4wMDEsNDguMjI2eiIvPg0KPC9zdmc+DQo=";
		return url;
	}
	this.stringify = function(theString) {
		return theString + "";
	}
	this.objectToReadableString = function(obj) {
		if (Object.prototype.toString.call(obj) === "[object Object]") {
		    var accumulator = [];
		    for (var p in obj) {
		        if (obj.hasOwnProperty(p)) {
		            accumulator.push(p + ': ' + obj[p]);
		        }
		    }
		    var contents = accumulator.join(", ");
			return "{ " + contents + " }";
		}
		else if (Object.prototype.toString.call(obj) === "[object Array]") {
			return "[ " + obj.join(", ") + " ]";
		}
		else
			return obj;
	}
	this.createJsonRpcObjectFromObject = function(obj) {
		obj.jsonrpc = "2.0";
		obj.params = obj.params ? obj.params : [];
		return obj;
	}
	this.isIOS = function(){
	    return (
	        (navigator.platform.indexOf("iPhone") != -1) ||
	        (navigator.platform.indexOf("iPad") != -1) ||
	        (navigator.platform.indexOf("iPod") != -1)
	    );
	}
	this.logJsonRPC = function(jsonRPC, isNative) {
		if (self.shouldLogJsonRpc) {
			var functionsToSkip = ["SetConnectionQuality"];
			if (functionsToSkip.indexOf(jsonRPC.method) != -1)
				return;
			var logtxt = (isNative?"Native->":"JS->") + jsonRPC.method + "(";
			var printableParams = [];
			for (var i=0; i<jsonRPC.params.length; i++) {
				var printableObj = jsonRPC.params[i];
				// if (typeof printableObj == "object")
				printableObj = self.sanitizedObject(printableObj, {keysToSkip: [""], keysToCensor: ["password", "profilePicURL"], returnHumanReadableString: true, shrinkLargeObjects: true});
			    printableParams.push(printableObj);
			}
			logtxt += printableParams.join(", ");
			logtxt += ")";
			// logtxt = logtxt.substring(0,100);
			console.log(logtxt);
		}
	}
	this.sanitizedObject = function(obj, options, level) {
		level = undefined ? 0 : level;
		var keysToSkip = options && options.keysToSkip ? options.keysToSkip : [];
		var keysToCensor = options && options.keysToCensor ? options.keysToCensor : [];
		var returnHumanReadableString = options && options.returnHumanReadableString ? options.returnHumanReadableString : false;
		var shrinkLargeObjects = options && options.shrinkLargeObjects ? options.shrinkLargeObjects : false;
		if (Object.prototype.toString.call(obj) === "[object Object]") {
			var sanitizedObj = {};
			for (var key in obj) {
				if (keysToSkip.indexOf(key) == -1) {
					if (keysToCensor.indexOf(key) != -1)
						sanitizedObj[key] = "[redacted]";
					else if (typeof	obj[key] == "object")
						sanitizedObj[key] = self.sanitizedObject(obj[key], options, level+1);
					else 
						sanitizedObj[key] = obj[key];
				}
			}
			if (returnHumanReadableString)
				return self.objectToReadableString(sanitizedObj);
			else
				return sanitizedObj;
		}
		else if (Object.prototype.toString.call(obj) === "[object Array]") {
			var sanitizedArr = [];
			for (var i = 0; i < obj.length && (!shrinkLargeObjects || i < 2 || obj.length < 10); i++) {
				if (shrinkLargeObjects && i == 1 && obj.length >= 10)
					sanitizedArr.push("... " + (obj.length - 1) + " more...");
				else
					sanitizedArr.push(self.sanitizedObject(obj[i], options, level+1));
			}
			if (returnHumanReadableString)
				return self.objectToReadableString(sanitizedArr);
			else
				return sanitizedArr;
		}
		else
			return obj;
	}
	this.urlify = function(text, callbackFunctionName) {
		if (!self.shouldDetectChatUrls)
			return text;
		//                             (      http|ftp       )? ( {username}       @)?     bit        |(             bit            .|   {username}   @)      bit+ ???   ((   /path           )? ? (query)             (  #(       anchor)*) ?)?<- this /path?query#anchor is all optional  )
		// var urlRegex = /(^\s*|\s+)((([A-Za-z]{3,9}:(?:\/\/)?)(?:[\-;:&=\+\$,\w]+@)?(?:[A-Za-z0-9\.\-](?!\.))+|(?:[A-Za-z][A-Za-z0-9]{0,10}\.|[\-;:&=\+\$,\w]+@)(?:[A-Za-z0-9\.\-](?!\.))+)((?:\/[\+~%\/\.\w\-]*)?(?:\?(?:[\-\+=&;%@\.\w]*))?(?:#(?:[\.\!\/\\\w]*))?)?)/gi;
		///                           (   http|ftp://  )? (     www-53    .      cc                       
		var urlRegex = /(^|[\s;"]+)((?:(https?|ftp):\/\/)?((?:([a-z0-9-]+\.)+(?:[a-z]{2,4}|museum|travel)(?:(?!&lt;)[^"\s])*)))/ig;
	    return text.replace(urlRegex, function(ignore, leading, url) {
			console.log(ignore);
			console.log(url);
	    	url = encodeURI(url);
			url = url.replace(/'/g, "%27"); //because encodeURI will miss some of the single-quotes
			var retval = leading+'<a class="link" onclick="' + callbackFunctionName + '(\''+Utils.prependUrlProtocolToUrl(url)+'\')">'+url+'</a>';
			console.log('************** ' +  retval);
			return retval;
	    });
	    //'$1<a class="link" onclick="' + callbackFunctionName + '(Utils.prependUrlProtocolToUrl(\'$2\'))">$2</a>')
	}

		// if (!self.shouldDetectChatUrls)
		// 	return text;
		// //                             (      http|ftp       )? ( {username}       @)?     bit        |(             bit            .|   {username}   @)      bit+ ???   ((   /path           )? ? (query)             (  #(       anchor)*) ?)?<- this /path?query#anchor is all optional  )
		// // var urlRegex = /(^\s*|\s+)((([A-Za-z]{3,9}:(?:\/\/)?)(?:[\-;:&=\+\$,\w]+@)?(?:[A-Za-z0-9\.\-](?!\.))+|(?:[A-Za-z][A-Za-z0-9]{0,10}\.|[\-;:&=\+\$,\w]+@)(?:[A-Za-z0-9\.\-](?!\.))+)((?:\/[\+~%\/\.\w\-]*)?(?:\?(?:[\-\+=&;%@\.\w]*))?(?:#(?:[\.\!\/\\\w]*))?)?)/gi;
		// ///                           (   http|ftp://  )? (     www-53    .      cc                       
		// var urlRegex = /(^|[\s;"]+)((?:(https?|ftp):\/\/)?((?:([a-z0-9-]+\.)+(?:[a-z]{2,4}|museum|travel)(?:(?!&lt;)[^"\s])*)))/ig;
		// // result = urlRegex.exec(text);
		// // if(result == null) {
		// // 	return text;
		// // }
		// var urlRegex2 = urlRegex;
		// first = text.replace(urlRegex, '$1');
		// myurl = encodeURI(text.replace(urlRegex2, '$2'));
		// myurl = myurl.replace(/'/g, "%27"); //because encodeURI will miss some of the single-quotes
	 //    return first + '<a class="link" onclick="' + callbackFunctionName + '(Utils.prependUrlProtocolToUrl(\'' + myurl + '\'))">' + myurl + '</a>';

	this.prependUrlProtocolToUrl = function(url) {
		var atSplit = url.split("@");
		if (atSplit.length > 1 && atSplit[0].indexOf("://") == -1)
			return "mailto:" + url;

		if (url.indexOf("://") == -1)
			return "http://" + url;

		return url;
	}

	this.htmlEncode = function(value) {
	  //create a in-memory div, set it's inner text(which jQuery automatically encodes)
	  //then grab the encoded contents back out.  The div never exists on the page.
	  return $('<div/>').text(value).html();
	}

	this.htmlDecode = function(value) {
	  return $('<div/>').html(value).text();
	}

	this.postWithAuth = function(path, query, callback, censorLogs) {
		var uri = self.apiServerURI + path
		var basicAuth = Base64.encode(BuddyListManager.GetBareJID() + ":" + BuddyListManager.GetPassword());
		if(query == null || query == undefined || query == "") {
			query = "auth="+basicAuth;
		}
		else {
			query = query.trim() + "&auth="+basicAuth;
		}
		console.log("POST " + uri);
        $.ajax({
	        url: uri,
	        type: "POST",
	        data: query,
	        dataType: 'json',
	        success: function(data) {
            if (censorLogs == true)
                {
                    console.log("CallWebFunction succeeded: [redacted]");
                }
                else
                {
	            console.log("CallWebFunction succeeded: " + data.result);
                }
	            if(callback != undefined) {
	                callback(data.result);
	            }
	        },
	        error: function(jqXHR,textStatus,errorThrown) {
	            console.log("Error calling CallWebFunction: " + textStatus + "; " + errorThrown + "; " + jqXHR.responseText);
	            if(callback != undefined) {
	                callback(null);
	            }
	        }
        });
	}

	this.GetTitleForConnectionQuality = function(cq) {
		var label = "No information about connection";
		if (cq == 1)
			label = "Your connection quality is terrible :("; // Your connection is worse than my grandma's dialup, Your connection is terrible, so is your momma, Are you on a dialup?, Where are you? Siberia?
		else if (cq == 2)
			label = "Your connection quality is meh";
		else if (cq == 3)
			label = "Your connection quality is ok";
		else if (cq == 4)
			label = "Your connection quality is good";
		else if (cq == 5)
			label = "Your connection quality is superb"; // Your connection quality is superb, so is your momma
		return label;
	}

	this.EnableDebugging = function () {
        self.isDebuggingEnabled = true;
       	self.shouldBlockRightClick = false;
        self.shouldLogJsonRpc = true;
        $("body").addClass("enable-debug");
    }
}

jQuery.fn.extend({
  flash: function(ms) {
    return this.each(function() {
		var obj = $(this);
		obj.fadeIn();
		window.setTimeout(function() {
			obj.fadeOut();
		}, ms ? ms : 3000);
    });
  }
});

