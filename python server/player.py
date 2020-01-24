import socket
import sys
import threading

Stop  = 0
Up    = 1
Down  = 2
Left  = 3
Right = 4

Speed = 100

Commands = {b'w' : Up, b's' : Down, b'a' : Left, b'd' : Right, b'n' : Stop}

class Player:
    def __init__(self, socket):
        self.socket = socket
        self.x = 25
        self.y = 25
        self.state = Stop;

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
        if (self.state == Up):
            self.y -= Speed * deltaTime
        if (self.state == Down):
            self.y += Speed * deltaTime
        if (self.state == Left):
            self.x -= Speed * deltaTime
        if (self.state == Right):
            self.x += Speed * deltaTime

    def updateState(self):
        while (self.connected):
            try:
                data = self.socket.recv(1)
            except socket.error:
                self.connected = False
                break
            if (data and (data in Commands)):
                self.state = Commands[data]

    def getMyData(self):
        return [int(self.x), int(self.y), self.state]

    def sendData(self, dataByteArray):
        try:
            self.socket.send(dataByteArray)
        except socket.error:
            self.connected = False
