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
    var led = new five.Led(25);


    var bSW3 = new five.Button({
        pin: 30,
        isPullup: true,
    });

    var bSW4 = new five.Button({
        pin: 31,
        isPullup: true,
    });

    this.repl.inject({
        led: led,
        bSW3: bSW3,
        bSW4: bSW4
    });

    bSW3.on("down", function() {
        led.blink(500);
        console.log("Button SW3 down");
        sendSysex(0x02, "SW3 button");
    });

    bSW3.on("up", function() {
        console.log("Button SW3 up");
    });

    bSW4.on("down", function() {
        led.stop();
        led.off();
        console.log("Button SW4 down");
        sendSysex(0x02, "SW4 button");
    });

    bSW4.on("up", function() {
        console.log("Button SW4 up");
    });


    board.sysexResponse(0x01, function(data) {
        var string = new Buffer(data).toString("utf8").replace(/\0/g, "");
        console.log("Sysex received: " + string);
    });

    sendSysex(0x01, "Hello World")
});
