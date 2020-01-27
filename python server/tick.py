import time
import sys
import socket

import player
import commander
import controllor
import command_manager

#每逻辑帧的时间
SecPerTick = 1.0/40.0

class Tick:
    #构造函数，需要传入两个玩家
    def __init__(self, p1, p2, server, commandManager):
        self.p1 = p1
        self.p2 = p2
        self.commandManager = commandManager
        self.server = server
        server.setblocking(False)

    #tick主函数
    def tick(self, deltaTime):
        self.p1.update(deltaTime)
        self.p2.update(deltaTime)
        data1 = self.p1.getMyData()
        data2 = self.p2.getMyData()

        s = str('x' + str(data1[0]) + 'y' + str(data1[1]) + 'x' + str(data2[0]) + 'y' + str(data2[1]))

        self.p1.sendData(s.encode('ascii'))
        self.p2.sendData(s.encode('ascii'))

    #开始tick（实际上是一个阻塞函数，每个循环询调用一次tick主函数）并且关注是否有新客户端连入
    def start(self):
        tOld = time.clock()
        deltaTime = 0

        while not (self.p1.isOver() or self.p2.isOver()):
            #获取deltaTime
            tNew = time.clock()
            deltaTime += tNew - tOld
            tOld = tNew

            #检测是否有新客户端接入
            if not self.p1.mycontrollor.connected or not self.p2.mycontrollor.connected:
                try:
                    c, a = self.server.accept() #如果没有客户端接入就会抛出BlockingIOError错误，被捕捉后pass掉
                    c.setblocking(True) #如果server socket为非阻塞模式，默认client也为非阻塞模式
                    n = c.recv(1)

                    if n == b'1':
                        self.p1.mycontrollor.newClient(c, self.commandManager)
                    elif n == b'2':
                        self.p2.mycontrollor.newClient(c, self.commandManager)
                except BlockingIOError:
                    pass

            #当deltaTime大于等于逻辑帧时间后，开始tick，并将deltaTime清零
            if (deltaTime >= SecPerTick):
                self.tick(deltaTime)
                deltaTime = 0
