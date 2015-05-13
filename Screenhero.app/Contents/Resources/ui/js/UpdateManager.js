var UpdateManager = (function () {
    // This is currently Windows-only

    var updateTime = 10 * 60 * 1000; // 10 mins
    var idleTime = 10 * 60 * 1000; // 10 mins
    var lastEventTime = new Date().getTime();
    var updateInterval;
    var dialogWasShown = false;
    var isMainWindowActive = true;
    var hasUpdateButNotYetIdleCount = 0;

    var SilentCheckForUpdates = function() {
        JSToNativeBridge.CallNativeFunction("SilentCheckForUpdates");
    };

    var IsIdle = function() {
        var now = new Date().getTime();
        console.log("now: " + now + ", lastEventTime:" + lastEventTime + ", isInShare: " + BuddyListManager.IsInShare() + ", numChatWindows: " + ChatWindowManager.NumberOfOpenChatWindows() + ", isMainWindowActive: " + isMainWindowActive);
        if (now - lastEventTime < idleTime || BuddyListManager.IsInShare() || ChatWindowManager.NumberOfOpenChatWindows() > 0 || isMainWindowActive)
            return false;
        else
            return true;
    };

    var public = {};

    public.Initialize = function() {
        updateInterval = setInterval(SilentCheckForUpdates, updateTime);
    };

    public.EventOccurred = function () {
        lastEventTime = new Date().getTime();
    };

    public.UpdateAvailable = function (isMajor) {
        if (IsIdle())
            JSToNativeBridge.CallNativeFunction("DoSilentUpdate");
        else if (isMajor) {
            if (hasUpdateButNotYetIdleCount < 5)
                hasUpdateButNotYetIdleCount++;
            else {
                //show major popup
                if (!dialogWasShown) {
                    dialogWasShown = true;
                    var dialog = {};
                    dialog.title = "Update ready to install!";
                    dialog.body = "Relaunch Screenhero to start using this version!  You'll love it, we promise :)";
                    dialog.labelArray = ["Relaunch", "Dismiss"];
                    dialog.shouldhideArray = [1, 1];
                    dialog.source = "jsRequest";
                    dialog.uuid = "UpdateManager.UpdateDialogResponse";
                    dialog.tag = "1";
                    dialog.defaultIndex = 0;
                    BuddyList.ShowDialog(dialog);
                }
            }
        }
    };

    public.UpdateDialogResponse = function (tag, index) {
        console.log("UpdateDialogResponse: " + index);
        if (index == 0) //relaunch
        {
            JSToNativeBridge.CallNativeFunction("DoSilentUpdate");
        }
        else if (index == 1) //dismiss
        {
            //do nothing?
        }
        else if (index == 2) //learn more
        {
            JSToNativeBridge.CallNativeFunction("LaunchUrlInBrowser", "https://screenhero.com");
        }
    };

    public.MainWindowActivated = function (isActive) {
        isMainWindowActive = isActive;
        public.EventOccurred();
    }

    return public;
})();