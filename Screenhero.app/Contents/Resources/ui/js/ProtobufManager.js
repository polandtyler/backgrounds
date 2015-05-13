var ProtobufManager = new function () {
	var self = this;

	this.Initialize = function(completion) {
        $.ajax("protobuf/ServerSide.proto").then(function (proto) {
            self.builder = dcodeIO.ProtoBuf.protoFromString(proto);
            completion();
		});
	}

	this.DecodeProtoBuf = function(pbType, pbData) {
        var pbUIR = self.builder.build(pbType); 
        pbUIR = pbUIR.decode64(pbData);
        return pbUIR;
	}

    this.SendProtoBuf = function(pbType, data, handler, failureHandler) {
        var pbUIR = self.builder.build("ServerSideProtocol." + pbType);
        pbUIR = new pbUIR();
        for (var key in data) {
            pbUIR[key] = data[key];
        }        
        $.ajax({
            url: Utils.apiServerURI + "/web-protobuf",
            type: "POST",
            data: {
                msgClass: pbType,
                requestBody: pbUIR.encode().toBase64()
            }
        }).then(handler, failureHandler);
    }
}
