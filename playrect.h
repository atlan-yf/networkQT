#ifndef PLAYRECT_H
#define PLAYRECT_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QRectF>

#include "settings.h"

class PlayRect : public QGraphicsRectItem
{
private:
    bool _player;                   //储存玩家号
    int  _state;                    //储存当前方块状态

public:
    //枚举方向常量
    enum Dir {
        Up, Down, Left, Right
    };
    //枚举状态常量
    enum State {
        GoingUp, GoingDown, GoingLeft, GoingRight, Stop
    };

public:
    void move(int direction);       //向指定移动【速度】个像素
    //重写绘制函数，改变方块颜色
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QRectF boundingRect() const;    //方块的碰撞框
    int  getState();
    void setState(int newState);

public:
    PlayRect(bool player);          //用玩家号来初始化方块，改变方块颜色
};

#endif // PLAYRECT_H
