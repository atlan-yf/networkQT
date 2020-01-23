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

public:
    //枚举方向常亮
    enum Dir {
        Up, Down, Left, Right
    };

public:
    void move(int direction);       //向指定移动【速度】个像素
    //重写绘制函数，改变方块颜色
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QRectF boundingRect() const;    //方块的碰撞框
    PlayRect(bool player);          //用玩家号来初始化方块，改变方块颜色
};

#endif // PLAYRECT_H
