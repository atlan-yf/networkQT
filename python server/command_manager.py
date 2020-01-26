import socket
import sys

import player

Speed = 100


#命令响应函数    ##############################################
#参数：_player,Player类型  deltaTime,数字类型
#功能：根据deltaTime时间差更新player状态


#默认函数，不可改动
def defaultDo(_player, deltaTime):
    pass

#自定义部分
def goUp(_player, deltaTime):
    _player.y -= Speed * deltaTime
def goDown(_player, deltaTime):
    _player.y += Speed * deltaTime
def goLeft(_player, deltaTime):
    _player.x -= Speed * deltaTime
def goRight(_player, deltaTime):
    _player.x += Speed * deltaTime

def gameOver(_player, deltaTime):
    _player.sendData('over'.encode('ascii'))
    _player.gameOver = True
#  End                  ######################################

#注册函数，由CommandManager内部调用，写在外边方便修改
def registerCommands(manager):
    manager.registerCommand(b'u',      goUp)
    manager.registerCommand(b's', defaultDo)
    manager.registerCommand(b'd',    goDown)
    manager.registerCommand(b'l',    goLeft)
    manager.registerCommand(b'r',   goRight)
    manager.registerCommand(b'q',  gameOver)

#CommandManager类
class CommandManager:
    #构造函数
    def __init__(self):
        self.socket = socket
        self.commands = {b'\0': [defaultDo]}
        self.register()

    #注册单个命令 内部函数
    def registerCommand(self, code, func):
        if code in self.commands.keys():
            self.commands.setdefault(code, []).append(func)
        else:
            self.commands[code] = [func]

    #注册所有命令 内部函数
    def register(self):
        global registerCommands
        registerCommands(self)

    #根据命令代码获取命令函数列表
    def getFuncs(self, code):
        if code in self.commands.keys():
            return self.commands[code]
        else:
            return []
