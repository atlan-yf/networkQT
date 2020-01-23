#include "netthread.h"

void NetThread::run()
{
    _socket = new QTcpSocket();
    while(!_stopped && !_connected) {
        _socket->connectToHost(IP_Address, Port);
        _connected = _socket->waitForConnected();
        if (_connected) {
            _socket->putChar(MyPlayer ? '1' : '2');
            _socket->flush();

            _socket->waitForReadyRead();
            QByteArray data = _socket->read(1024);
            if (!data.isEmpty()) {
                processData(data);
            }
            emit connectedSignal();
        }
    }

    while (!_stopped && _connected) {
        _socket->putChar(_command);
        _socket->flush();
        _command = CommandNothing;

        _socket->waitForReadyRead();
        QByteArray data = _socket->read(1024);
        if (!data.isEmpty()) {
            processData(data);
        }

        _connected = _socket->isOpen();
    }

    _socket->disconnectFromHost();
    delete _socket;
}

constexpr bool isNumber(int num)
{
    return (num >= '0' && num <= '9');
}

void NetThread::processData(QByteArray data)
{
    int coordXYs[4] = {0};//分别存play1 x y play2 x y
    int j = -1, minusFlag;
    for (int i = 0 ; data[i] != '\0' ; i++) {
        if (data[i] == 'x'||data[i] == 'y') {
            j++;
            if (j != 0)
                coordXYs[j - 1] *= minusFlag;
            minusFlag = 1;
        } else if (isNumber(data[i])) {
            coordXYs[j] *= 10;
            coordXYs[j] += (data[i]-'0');
        } else if (data[i] == '-'){
            minusFlag = -1;
        } else {
            return;
        }
    }
    emit coords(coordXYs[0], coordXYs[1], coordXYs[2], coordXYs[3]);
}

void NetThread::stop()
{
    _stopped = true;
}

void NetThread::setCommand(char command)
{
    if (command == CommandUp || command == CommandDown || command == CommandLeft || command == CommandRight) {
        _command = command;
    }
}

bool NetThread::isConnected()
{
    return _connected;
}

NetThread::NetThread()
{
    _stopped = false;
    _command = CommandNothing;
}
