import socket
import sys

import controllor
import commander
import command_manager

class Player:
    #需要一个commander作为参数，构造函数
    def __init__(self, mycontrollor):
        self.mycontrollor = mycontrollor
        self.x = 25
        self.y = 25

        #当前更新函数列表（状态）
        self.stateFuncs = [command_manager.defaultDo];
        self.state = b'\0'

        self.gameOver = False

    #停止player
    def stop(self):
        self.gameOver = True
        self.mycontrollor.stop()

    #返回游戏是否结束
    def isOver(self):
        return self.gameOver

    #更新玩家状态和下一个指令
    def update(self, deltaTime):
        for i, func in enumerate(self.stateFuncs):
            func(self, deltaTime)
        self.mycontrollor.update(self)

    #获取自身坐标和状态
    def getMyData(self):
        return [int(self.x), int(self.y), self.state]

    #向PlayerControllor/Commander发送数据（其实只有NetCommander有接收数据的必要）
    def sendData(self, dataBytes):
        self.mycontrollor.nowCommander.dataCommander(dataBytes)
