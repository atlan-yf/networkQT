import abc
import sys
import socket
import threading

import command_manager

#Commander类定义，继承自抽象类
class Commander(metaclass = abc.ABCMeta):

    #构造函数,需要传递一个更新命令函数
    def __init__(self, func_updateCommand):
        self.lock       = False
        self.shouldStop = False
        self.shutdown   = False

        self.func_updateCommand = func_updateCommand

        #默认代码b'\0'，默认函数列表[defaultDo]
        self.nextCommand = [command_manager.defaultDo]
        self.nextCode = b'\0'

        self.thread = threading.Thread(target = self._run)
        self.thread.start()

    #Commander内部循环，每次循环调用更新命令函数 内部函数
    def _run(self):
        while not self.shouldStop:
            self.func_updateCommand(self)
        self.shutdown = True

    #返回Commander是否失效
    def isAlive(self):
        return not self.shutdown

    #等待，后给nextCommand成员变量加锁
    def lockWhenUnlocked(self):
        while self.lock:
            pass
        self.lock = True

    #解锁
    def unlock(self):
        self.lock = False

    #获取指令
    #返回：元组（指令函数列表，指令代码）
    def getCommand(self):
        self.lockWhenUnlocked()
        temF = self.nextCommand
        temC = self.nextCode
        self.unlock()
        return (temF, temC)

    #抽象函数，接收Player发来的数据（只有NetCommander有接收数据的必要）
    @abc.abstractmethod
    def dataCommander(self, dataBytes):
        pass

    #抽象函数，停止Commander
    #重写时注意！！！请使用self.shouldStop = True来关闭
    @abc.abstractmethod
    def stop(self):
        pass

####NetCommander    ####################################################################

class NetCommander(Commander):
    #接受一个CommandManager作为构造函数的参数
    def __init__(self, mysocket, commandManager):
        self.mysocket = mysocket
        self.commandManager = commandManager

        Commander.__init__(self, self.updateCommand)

    def stop(self):
        try:
            self.mysocket.shutdown(2)
        except socket.error:
            pass
        self.mysocket.close()
        self.shouldStop = True

    #静态函数，更新命令，将作为参数传递给基类Commander
    @staticmethod
    def updateCommand(selfC):
        try:
            code = selfC.mysocket.recv(1)

            if code == b'\x7f':
                selfC.mysocket.send('connect test'.encode('ascii'))
            else:
                funcs = selfC.commandManager.getFuncs(code)
                if funcs:
                    selfC.lockWhenUnlocked()
                    selfC.nextCommand = funcs
                    selfC.nextCode = code
                    selfC.unlock()
        except socket.error:
            selfC.stop()

    def dataCommander(self, dataBytes):
        try:
            self.mysocket.send(dataBytes)
        except socket.error:
            self.stop()

####BotCommander    ####################################################################

class BotCommander(Commander):
    def __init__(self):
        Commander.__init__(self, self.updateCommand)
        pass

    @staticmethod
    def updateCommand(selfC):
        pass

    def dataCommander(self, dataBytes):
        pass

    def stop(self):
        self.shouldStop = True
        pass
