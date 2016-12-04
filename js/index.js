var five = require("johnny-five");
var board = new five.Board();

var encode = function(string) {
    var bytes = new Buffer(string + "\0", "utf8");
    var data = [];
    for (var i = 0, length = bytes.length; i < length; i++) {
        data.push(bytes[i] & 0x7F);
        data.push((bytes[i] >> 7) & 0x7F);
    }

    return data;
}

var sendSysex = function(command, _data) {
    data = [command].concat(encode(_data));
    board.sysexCommand(data);
}

board.on("string", function(s) {
    console.log("Arduino Debug: " + s);
});

board.on("ready", function() {
    // Create a standard `led` component instance
    var led = new five.Led(13);


    var button = new five.Button({
        pin: 2,
        isPullup: true
    });

    this.repl.inject({
        led: led,
        button: button
    });


    button.on("down", function(value) {
        led.blink(500);
        console.log("Button down");
    });

    button.on("up", function() {
        console.log("Button up");
        led.stop();
        led.off();
    });

    board.sysexResponse(0x01, function(data) {
        var string = new Buffer(data).toString("utf8").replace(/\0/g, "");
        console.log("Sysex received: " + string);
    });

    sendSysex(0x01, "Ahoj svete")
});
