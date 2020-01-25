#ifndef COMMANDS_H
#define COMMANDS_H

#include <QMultiMap>
#include <QList>

class Commands
{
private:
    QMultiMap<int, char> _commands;
    QList<char>              _codes;

public:
    void static registerCommands(Commands *commands)
    {
        commands->registerCommand((int)Qt::Key_Up,    'u');
        commands->registerCommand((int)Qt::Key_Down,  'd');
        commands->registerCommand((int)Qt::Key_Left,  'l');
        commands->registerCommand((int)Qt::Key_Right, 'r');
        commands->registerCommand((int)Qt::Key_Space, 's');
    }

public:
    void registerCommand(int key, char code);
    QList<char>  testKey(int key);
    bool test(char code);
};

#endif // COMMANDS_H
