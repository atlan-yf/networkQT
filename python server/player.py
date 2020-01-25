import socket
import sys
import threading

import command_manager

class Player:
    def __init__(self, socket, commandManager):
        self.socket = socket
        self.commandManager = commandManager
        self.x = 25
        self.y = 25
        self.stateFuncs = [command_manager.defaultDo];
        self.state = b'\0'

        self.connected = True

        try:
            self.socket.recv(1)
            self.socket.send('x25y25x25y25'.encode('ascii'))
        except socket.error:
            self.connected = False
            return

        self.t = threading.Thread(target = self.updateState)
        self.t.start()

    def stop(self):
        try:
            self.socket.shutdown(2)
        except socket.error:
            pass
        self.socket.close()

    def isConnected(self):
        return self.connected

    def update(self, deltaTime):
        for i, func in enumerate(self.stateFuncs):
            func(self, deltaTime)

    def updateState(self):
        while (self.connected):
            try:
                code = self.socket.recv(1)
            except socket.error:
                self.connected = False
                break
            funcs = self.commandManager.getFuncs(code)
            if funcs:
                self.stateFuncs = funcs
                self.state = code

    def getMyData(self):
        return [int(self.x), int(self.y), self.state]

    def sendData(self, dataByteArray):
        try:
            self.socket.send(dataByteArray)
        except socket.error:
            self.connected = False
