var express = require('express');
var app = express();
var port = process.env.PORT || 3000;

var bodyParser = require('body-parser');
app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: true  })); // support encoded bodies

app.get('/', function (req, res) {
      res.send('Hello World!');
});


var commands = ['popcorn', 'door', 'light'];

app.post('/cmd', function(req, res) {
    console.log("cmd");
    var user_id = req.body.user_id;
    var token = req.body.token;
    var command = req.body.command;
    var timestamp = req.body.timestamp;
    if (commands.includes(command)) {
        if(command == 'door') {
            activateDoor();
        } else {
            activateRelay(command);
        }
        res.send(command + ' activated');
    } else {
        res.status(404).send('Command not found');
    }
    //res.send(user_id + ' ' + token + ' ' + command);
});

function activateDoor(command) {
    console.log("activateDoor");
    rest.post(sesameURI)
    .on('complete', function (data, response) {
        console.log(data);
    });
}

var states = commands.reduce(function(result, item) {
    result[item] = 0;
    return result;
}, {});

var relay = {
    'light': 'r3',
    'popcorn': 'r4'
}

function activateRelay(command) {
    console.log("activateRelay");
    var state = (states[command] ? "LOW" : "HIGH");
    states[command] = (states[command] + 1) % 2;
    rest.post(relayURI, {
        "data": {
            "params":relay[command]+ "," + state
        }
    })
    .on('complete', function (data, response) {
        console.log(data);
    });
}

app.listen(port, function () {
    console.log('Server started! At http://localhost:' + port);
});

var EventSource = require('eventsource');
var rest = require('restler');

var deviceIDSesame = "190033000347343337373737";
var deviceIDRelay = "200039001747343338333633";
var accessToken = "320a9e527ec5863bf351c3302cef069a69a66c08";
var accessTokenURI = "/?access_token=" + accessToken;
var deviceSesame = "https://api.particle.io/v1/devices/" + deviceIDSesame;
var deviceRelay = "https://api.particle.io/v1/devices/" + deviceIDRelay;
var eventsURISesame = deviceSesame + "/events" + accessTokenURI;
var eventsURIRelay = deviceRelay + "/events" + accessTokenURI;
var eventSrcSesame = new EventSource(eventsURISesame);
var eventSrcRelay = new EventSource(eventsURIRelay);
var sesameURI = deviceSesame + "/door" + accessTokenURI;
var relayURI = deviceRelay + "/relay" + accessTokenURI;

eventSrcSesame.addEventListener('status', function (e) {
    var data = JSON.parse(e.data);
    console.log("Device: Sesame");
    console.log(data);
});

eventSrcSesame.addEventListener('logging', function (e) {
    var data = JSON.parse(e.data);
    console.log("Device: Sesame");
    console.log(data);
});

eventSrcRelay.addEventListener('status', function (e) {
    var data = JSON.parse(e.data);
    console.log("Device: Relay");
    console.log(data);
});

eventSrcRelay.addEventListener('logging', function (e) {
    var data = JSON.parse(e.data);
    console.log("Device: Relay");
    console.log(data);
});
