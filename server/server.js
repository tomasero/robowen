var express = require('express');
var app = express();
var port = process.env.PORT || 3000;

var bodyParser = require('body-parser');
app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: true  })); // support encoded bodies

app.get('/', function (req, res) {
      res.send('Hello World!');
});


app.post('/cmd', function(req, res) {
    console.log("cmd");
    var user_id = req.body.user_id;
    var token = req.body.token;
    var command = req.body.command;
    var timestamp = req.body.timestamp;
    if (command == 'popcorn') {
        activateRelay();
        res.send(command + ' activated.')
    } else {
        res.send('not a valid command');
    }
    //res.send(user_id + ' ' + token + ' ' + command);
});

app.listen(port, function () {
    console.log('Server started! At http://localhost:' + port);
});

var EventSource = require('eventsource');
var rest = require('restler');

var deviceID = "200039001747343338333633";
var accessToken = "320a9e527ec5863bf351c3302cef069a69a66c08";
var accessTokenURI = "/?access_token=" + accessToken;
var device = "https://api.particle.io/v1/devices/" + deviceID;
var eventsURI = device + "/events" + accessTokenURI;
var eventSrc = new EventSource(eventsURI);
var relayURI = device + "/relay" + accessTokenURI;
var relayState = 0;

eventSrc.addEventListener('status', function (e) {
    var data = JSON.parse(e.data);
    console.log(data);
});

eventSrc.addEventListener('logging', function (e) {
    var data = JSON.parse(e.data);
    console.log(data);
});

function activateRelay() {
    console.log("activateRelay");
    var command = (relayState ? "LOW" : "HIGH");
    relayState = (relayState + 1) % 2;
    rest.post(relayURI, {
        "data": {
            "params":"r4," + command
        }
    })
    .on('complete', function (data, response) {
        console.log(data);
    });
}
