var ChatHistoryManager = new function () {
    var self = this;

    this.Initialize = function() {
        self.ra = new Ractive({
            data: {
                unreadMessageCountHash: {}
            }
        });
    }

    this._chatHistoryDict = {}; // dict of bareJid -> array of ChatMessage objects
    this.GetChatHistoryForBuddy = function (bareJid) {
        var chatHistory = self._chatHistoryDict[bareJid];
        if (!chatHistory)
        {
            chatHistory = [];
            self._chatHistoryDict[bareJid] = chatHistory;
        }
        return chatHistory;
    }

    this.HandleChatMessage = function(bareJid, chatMessage) {
        var chatHistory = self.GetChatHistoryForBuddy(bareJid);
        chatHistory.push(chatMessage);
    }

    this.ChatMessageModel = function (msg, timestamp, fromMe) {
        this.msg = msg;
        this.timestamp = timestamp;
        this.fromMe = fromMe;
    }

    this.IncrementUnreadMessageCountForBuddy = function(bareJid) {        
        var count = self.ra.get("unreadMessageCountHash." + bareJid.split("@")[0]);
        if (count)
            count = count + 1;
        else
            count = 1;
        self.ra.set("unreadMessageCountHash." + bareJid.split("@")[0], count);
    }

    this.ResetUnreadMessageCount = function(bareJid) {
        self.ra.set("unreadMessageCountHash." + bareJid.split("@")[0], 0);
    }
}
