import socket
import sys

import player

Speed = 100

def defaultDo(_player, deltaTime):
    pass

def goUp(_player, deltaTime):
    _player.y -= Speed * deltaTime
def goDown(_player, deltaTime):
    _player.y += Speed * deltaTime
def goLeft(_player, deltaTime):
    _player.x -= Speed * deltaTime
def goRight(_player, deltaTime):
    _player.x += Speed * deltaTime

def registerCommands(manager):
    manager.registerCommand(b'u',      goUp)
    manager.registerCommand(b's', defaultDo)
    manager.registerCommand(b'd',    goDown)
    manager.registerCommand(b'l',    goLeft)
    manager.registerCommand(b'r',   goRight)


class CommandManager:
    def __init__(self):
        self.socket = socket
        self.commands = {b'\0': [defaultDo]}
        self.register()

    def registerCommand(self, code, func):
        if code in self.commands.keys():
            self.commands.setdefault(code, []).append(func)
        else:
            self.commands[code] = [func]

    def register(self):
        global registerCommands
        registerCommands(self)

    def getFuncs(self, code):
        if code in self.commands.keys():
            return self.commands[code]
        else:
            return []
