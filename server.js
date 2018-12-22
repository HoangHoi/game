require('dotenv').config();
var express = require('express');
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io')(server);
var colors = require('colors');
var port = process.env.PORT || 3000;

var userWin = null;

server.listen(port, function () {
    console.log('Server listening at port %d', port);
});

app.use(express.static(__dirname + '/public'));

function clearUserWin() {
    userWin = null;
    var clients = io.sockets.clients().sockets;
    var clientsKey = Object.keys(clients);
    for (var i = 0; i < clientsKey.length; i++) {
        clients[clientsKey[i]].isTriggered = false;
    }
    io.emit('clear', {status: 1});
}

function handleUserTrigg(socket) {
    if (!socket.isTriggered) {
        if (userWin == null) {
            userWin = socket;
            socket.emit('win', {status: 1});

            setTimeout(clearUserWin, 5000);
        }
        socket.isTriggered = true;
    }
}

io.on('connection', function (socket) {
    console.log('New client connect'.gray);

    socket.on('trigg', function () {
        handleUserTrigg(socket);
    });

    socket.on('disconnect', function () {
        console.log('Client disconnect'.gray);
    });
});
