var WindowManager = new function () {
    var self = this;

    this.WindowTypes = {
        ChatWindow: "ChatWindow",
        IncomingShareWindow: "IncomingShareWindow"
    };

    //jschild -> js
    this.ReceivePostedJSMessageFromChild = function (event) {
        if (event.data.windowType == self.WindowTypes.ChatWindow)
        {
            ChatWindowManager.ReceivePostedJSMessageFromChild(event);
        }
        else if (event.data.windowType == self.WindowTypes.IncomingShareWindow)
        {
            IncomingShareWindowManager.ReceivePostedJSMessageFromChild(event);
        }
    }
    //end of jschild ->js

    this.Initialize = function () {
        window.addEventListener("message", self.ReceivePostedJSMessageFromChild, false);
    }
}