import player
import time
import socket
import sys
import tick

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
port = 9999
server.bind(('', port))
server.listen(2)

c1, a1 = server.accept()
c2, a2 = server.accept()

p1 = player.Player(c1)
p2 = player.Player(c2)

tick.Tick(p1, p2).start()

p1.stop()
p2.stop()
server.close()
print('disconnected')
