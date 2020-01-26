#include "netthread.h"

void NetThread::run()
{
    _socket = new QTcpSocket();
    _socket->connectToHost(IP_Address, Port);
    if (!_stopped)
        _connected = _socket->waitForConnected();
    if (_connected) {
        _socket->putChar(MyPlayer ? '1' : '2');
        _socket->flush();

        emit connectedSignal();
    }

    while (!_stopped && _connected) {
        if (!_commands.empty()) {
            char c = _popCommand();
            _socket->putChar(c);
            _socket->flush();
        }

        _socket->waitForReadyRead();
        QByteArray data = _socket->read(16);
        if (!data.isEmpty()) {
            processData(data);
        }
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
    if (data == "over") {
        _connected = false;
        _stopped = true;
        return;
    }

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

void NetThread::addCommand(char command)
{
    if (!commandManager.test(command)) {
        return;
    }
    while (_queueLock);
    _queueLock = true;
    _commands.push(command);
    _queueLock = false;
}

bool NetThread::isConnected()
{
    return _connected;
}

NetThread::NetThread()
{
    _connected = false;
    _stopped = false;
    _queueLock = false;

    Commands::registerCommands(&this->commandManager);
}
