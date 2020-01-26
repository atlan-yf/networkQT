import time
import socket
import sys

import tick
import player
import commander
import command_manager
import controllor

#新建命令管理器对象，在这里注册所有命令
commandManager = command_manager.CommandManager()

#服务端socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
port = 9999
server.bind(('', port))
server.listen(2)

ct1 = controllor.PlayerControllor()
ct2 = controllor.PlayerControllor()

p1 = player.Player(ct1)
p2 = player.Player(ct2)

#隐式新建Tick类，并开始tick
tick.Tick(p1, p2, server, commandManager).start()

#退出
p1.stop()
p2.stop()
server.close()
print('disconnected')
