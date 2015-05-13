// TODO

$(window).load(function(){
	// Block right click menu
	    document.body.addEventListener('contextmenu', function (evt) { if (Utils.shouldBlockRightClick) evt.preventDefault(); });

    ResourceManager.Initialize();
});

