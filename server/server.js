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
    var user_id = req.body.id;
    var token = req.body.token;
    var cmd = req.body.cmd;
    res.send(user_id + ' ' + token + ' ' + cmd);
});

app.listen(port, function () {
    console.log('Server started! At http://localhost:' + port);
});
