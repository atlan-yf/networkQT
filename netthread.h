#ifndef NETTHREAD_H
#define NETTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include <queue>

#include "settings.h"

class NetThread : public QThread
{
    Q_OBJECT

protected:
    void run();     //主循环

private:
    volatile bool    _stopped;              //是否已停止的标志
    QTcpSocket       *_socket;              //连接服务端的socket
    bool             _connected;            //是否已连接到服务端并且成功“握手”的标志
    volatile bool    _queueLock;            //多线程锁，防止队列被同时修改
    std::queue<char> _commands;             //指令队列

private:
    inline char _popCommand()
    {
        while (_queueLock);
        _queueLock = true;
        char c = _commands.back();
        _commands.pop();
        _queueLock = false;
        return c;
    }

public:
    Commands commandManager;
public:
    void processData(QByteArray data);  //处理坐标协议的函数，由此发送coords(int, int, int, int)信号
    void stop();                        //通过改变_stopped标志，使进程安全停止
    void addCommand(char command);      //向队列添加指令
    bool isConnected();                 //提供检测是否连接的接口

signals:
    void coords(int x1, int y1, int x2, int y2);    //收到并成功解析坐标协议的信号
    void connectedSignal();                         //已经连接并“握手”的信号

public:
    NetThread();
};

#endif // NETTHREAD_H
