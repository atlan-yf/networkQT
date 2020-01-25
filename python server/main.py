import time
import socket
import sys

import tick
import player
import command_manager

commandManager = command_manager.CommandManager()

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
port = 9999
server.bind(('', port))
server.listen(2)

c1, a1 = server.accept()
c2, a2 = server.accept()

p1 = player.Player(c1, commandManager)
p2 = player.Player(c2, commandManager)

tick.Tick(p1, p2).start()

p1.stop()
p2.stop()
server.close()
print('disconnected')
