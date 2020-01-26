import sys
import socket
import abc

import commander
import player

#继承自抽象类
class Controllor(metaclass = abc.ABCMeta):
    def __init__(self):
        pass

    #抽象函数，传入player，更改player状态
    #TODO: 在抽象出【物体】基类之后，把player改成【物体】，实现controllor对所有物体的控制
    @abc.abstractmethod
    def update(self, player):
        pass

class PlayerControllor(Controllor):
    #玩家控制器，用serversocket和commandManager作为参数，借此构造NetCommander
    def __init__(self):
        Controllor.__init__(self)

        self.botCommander = commander.BotCommander()
        self.nowCommander = self.botCommander

        self.connected = False

    def update(self, player):
        player.stateFuncs, player.state = self.nowCommander.getCommand()

        if self.connected:
            if self.netCommander.isAlive():
                self.nowCommander = self.netCommander
            else:
                self.nowCommander = self.botCommander
                self.connected = False
        else:
            self.nowCommander = self.botCommander

    def stop(self):
        self.botCommander.stop()
        if self.connected and self.netCommander.isAlive():
            self.nowCommander.stop()

    #等待连接，连接上后切换连接状态，并检测是否掉线
    def newClient(self, socket, commandManager):
        self.netCommander = commander.NetCommander(socket, commandManager)
        self.connected = True
