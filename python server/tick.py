import time
import sys
import player

SecPerTick = 1.0/25.0

class Tick:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2

    def tick(self, deltaTime):
        self.p1.update(deltaTime)
        self.p2.update(deltaTime)
        data1 = self.p1.getMyData()
        data2 = self.p2.getMyData()

        s = str('x' + str(data1[0]) + 'y' + str(data1[1]) + 'x' + str(data2[0]) + 'y' + str(data2[1]))

        self.p1.sendData(s.encode('ascii'))
        self.p2.sendData(s.encode('ascii'))

    def start(self):
        tOld = time.clock()
        deltaTime = 0
        while (self.p1.isConnected() and self.p2.isConnected()):
            tNew = time.clock()
            deltaTime += tNew - tOld
            tOld = tNew

            if (deltaTime >= SecPerTick):
                self.tick(deltaTime)
                deltaTime = 0
