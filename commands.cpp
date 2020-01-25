#include "commands.h"

void Commands::registerCommand(int key, char code)
{
    _commands.insert(key, code);
    if (!test(code))
        _codes.push_back(code);
}

QList<char> Commands::testKey(int key)
{
    if (_commands.find(key) != _commands.end()) {
        return _commands.values(key);
    } else {
        return QList<char>();
    }
}

bool Commands::test(char code)
{
    for (QList<char>::ConstIterator i = _codes.begin(); i != _codes.end(); ++i) {
        if (*i == code) {
            return true;
        }
    }
    return false;
}
