var socket = io();
var button = document.getElementById('button');
socket.emit('role', 'admin');
document.addEventListener('click', function () {
    socket.emit('start');
});
// socket.on('new message', function () {

// });
console.log(button);
