var ResourceManager = new function () {
	var self = this;

	this.launchModuleName = Utils.getQueryParameterByName("launchModuleName");
	this.ActiveWindow = null;
	this.pendingLoads = 0;
	this.noMoreLoadsWillBeRequested = false;
	this.useWebAudioAPI = window.webkitAudioContext !== undefined;
	if (Utils.isAwesomiumMac)
		this.useWebAudioAPI = false;

	this.isMainModule = function() {
		return self.launchModuleName == "";
	}

	this.Initialize = function () {

	    self.InitializeProtoBufManager();
	    ChatHistoryManager.Initialize();

	    self.loadSVG("avatar.svg");
	    self.loadSVG("spinner.svg");
	    self.loadSVG("ic-signal-status-0.svg");
	    self.loadSVG("ic-signal-status-1.svg");
	    self.loadSVG("ic-signal-status-2.svg");
	    self.loadSVG("ic-signal-status-3.svg");
	    self.loadSVG("ic-signal-status-4.svg");
	    self.loadSVG("ic-signal-status-5.svg");
	    self.loadSVG("btn-share.svg");
	    self.loadSVG("btn-cancel-selection.svg");
	    self.loadSVG("btn-call.svg");
	    self.loadSVG("btn-share-combined.svg");
	    self.loadSVG("btn-share-switch.svg");	    
	    self.loadSVG("btn-mic-combined.svg");
	    self.loadSVG("btn-mic.svg");
	    self.loadSVG("pic-add_buddy.svg");
	    self.loadSVG("pic-arrow.svg");
	    self.loadSVG("btn-add.svg");
	    if (self.isMainModule()) {
	    	// main window
		    UpdateManager.Initialize();
		    XmppManager.Initialize();

		    self.loadSVG("ic-more.svg");
		    self.loadSVG("ic-cross.svg");
		    self.loadSVG("screenhero-logo.svg");
		    self.loadSVG("btn-add_contact.svg");
		    self.loadSVG("btn-group-call.svg");
		    self.loadSVG("btn-group-share.svg");
		    self.loadSVG("btn-unadd.svg");
		    self.loadSVG("btn-chat.svg");
		    self.loadSVG("btn-love.svg");
		    self.loadSVG("btn-settings.svg");
		    self.loadSVG("ic-dropdown_indicator.svg");
		    self.loadSVG("chrome-pointer.svg");
		    self.loadSVG("img-bulb.svg");
		    self.loadSVG("img-info.svg");
		    self.loadSVG("img-success.svg");
		    self.loadSVG("img-warning.svg");
		    self.loadSVG("img-error.svg");
		    self.loadTemplate("Main");
		    self.loadTemplate("BuddyList");
		    self.loadTemplate("WelcomeView");
		    self.loadTemplate("LoginView");
		    self.loadSound("bells1.wav");
		    self.loadSound("chat.wav");
		}
		else
		    self.loadTemplate(self.launchModuleName);

		self.signalWhenReady(true);		
	}

	this.InitializeProtoBufManager = function() {
		self.pendingLoads++;
		ProtobufManager.Initialize(function() {
			self.pendingLoads--;
		    
		    BuddyListManager.Initialize();
			
			self.signalWhenReady();
		});
	}

	this.svgDict = {};
	this.getSVG = function (url) {
		// console.log("getSVG: " + url);
		url = "img/" + url;
		var svgData = self.svgDict[url];
		return (svgData == undefined) ? "" : svgData;
	}
	this.loadSVG = function (url) {
		url = "img/" + url;
		self.pendingLoads++;
		$.ajax(url).then(self.loadSVGsuccess, self.loadSVGfailed);
	}
	this.loadSVGsuccess = function (data, textStatus, jqXHR) {
		self.pendingLoads--;
		self.svgDict[this.url] = jqXHR.responseText;
		self.signalWhenReady();
	}
	this.loadSVGfailed = function (jqXHR, textStatus, errorThrown) {
		self.pendingLoads--;
		console.log("couldn't load svg from " + this.url + ", error: " + errorThrown);
		self.signalWhenReady();
	}

	this.soundDict = {};
	this.loadSound = function (url) {
		url = "snd/" + url;
		self.pendingLoads++;
		//console.log("loadSound, useWebAudioAPI = " + self.useWebAudioAPI);
		if (self.useWebAudioAPI)
		{
			var request = new XMLHttpRequest();
			request.open('GET', url, true);
			request.responseType = 'arraybuffer';

			// Decode asynchronously
			request.onload = function() {
				if (!self.audioContext)
					self.audioContext = new webkitAudioContext();
				self.audioContext.decodeAudioData(request.response, function(buffer) {
						self.soundDict[url] = {buffer: buffer};
						self.pendingLoads--;
						self.signalWhenReady();
					}, 
					function(err) { 
						//console.log("audioContext decode failed: " + err); 
						self.pendingLoads--;
					});
			}
			request.send();
		}
		else
		{
			createjs.Sound.registerSound({src: url, id: url});
			self.pendingLoads--;
		}
	}
	this.playSound = function (url, shouldLoop) {
		if (Utils.isAwesomiumMac) {
			JSToNativeBridge.CallNativeFunction("PlaySound", url, shouldLoop===true);
			return;
		}
		self.stopSound(url);
		url = "snd/" + url;
		try {
			if (self.useWebAudioAPI)
			{
				var soundObject = self.soundDict[url];
				if (soundObject)
				{
					soundObject.source = self.audioContext.createBufferSource();
					soundObject.source.buffer = soundObject.buffer;
					soundObject.source.loop = shouldLoop;
					soundObject.source.connect(self.audioContext.destination);
					if (soundObject.source.start)
						soundObject.source.start(0);
					else 
						soundObject.source.noteOn(0);
				}
				else
					console.log("no audio source for " + url);
			}
			else
			{
				if (self.soundDict[url])
					self.soundDict[url].stop();
				self.soundDict[url] = createjs.Sound.play(url, {loop: shouldLoop ? -1 : 0});
			}
		}
		catch (e) {
			console.log("Exception in ResourceManager.playSound: " + e);
		}
	}
	this.stopSound = function (url) {
		if (Utils.isAwesomiumMac) {
			JSToNativeBridge.CallNativeFunction("StopSound", url);
			return;
		}
		url = "snd/" + url;
		try {
			if (self.useWebAudioAPI)
			{
				var soundObject = self.soundDict[url];
				if (soundObject && soundObject.source) {
						if (soundObject.source.stop)
							soundObject.source.stop(0);
						else 
							soundObject.source.noteOff(0);
				}
				else
					console.log("no audio source for " + url);
			}
			else
				if (self.soundDict[url])
					self.soundDict[url].stop();
		}
		catch (e) {
			console.log("Exception in ResourceManager.stopSound: " + e);
		}
	}

	this.loadTemplate = function(id) {
		self.pendingLoads++;
		$.ajax(id + "/" + id + ".htm").then(self.loadTemplateSuccess, self.loadTemplateFailed);
	}
	this.loadTemplateSuccess = function (data, textStatus, jqXHR) {
		//console.log("loaded template from " + this.url);
		var id = this.url.substring(this.url.lastIndexOf("/")+1).replace(".htm","");
		var obj = eval(id);
		obj.setTemplate(jqXHR.responseText);
		self.pendingLoads--;
		self.signalWhenReady();
	}
	this.loadTemplateFailed = function (jqXHR, textStatus, errorThrown) {
		//console.log("couldn't load template from " + this.url + ", error: " + errorThrown);
		self.pendingLoads--;
	}
	this.allPendingLoadsCompleted = function () {
		return self.pendingLoads == 0;
	}
	this.signalWhenReady = function(noMoreLoadsWillBeRequested) {
		if (noMoreLoadsWillBeRequested)
			self.noMoreLoadsWillBeRequested = true;

		if (self.noMoreLoadsWillBeRequested && self.allPendingLoadsCompleted())
		{
			if (!self.isMainModule()) {
				window.nativeObject = eval(self.launchModuleName);
				nativeObject.SignalReadyForLaunch();
			}
			else
			{
				try
				{
				    ChatWindowManager.Initialize();
					WindowManager.Initialize();
				    Main.Initialize();
				    WelcomeView.Initialize();
				    BuddyList.Initialize();
				    LoginView.Initialize();
				}	
				catch (err)
				{
					console.log("caught exception: " + err);
					console.log("stacktrace: " + err.stack);
				}

				JSToNativeBridge.SignalReadyForLaunch();		
			}
		}
	}
}