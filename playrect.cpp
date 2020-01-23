#include "playrect.h"

PlayRect::PlayRect(bool player)
    :_player(player), _state(State::Stop)
{
    setPos(EdgeWidth + 2, EdgeWidth + 2);
}

void PlayRect::move(int direction)
{
    //WindowWidth = 800
    //WindowHeight = 600
    //EdgeWidth = 5
    //delta是差值

    int deltaX = 0, deltaY = 0;
    switch(direction) {
    case Dir::Up:
        deltaY = -Speed;
        break;
    case Dir::Down:
        deltaY = Speed;
        break;
    case Dir::Left:
        deltaX = -Speed;
        break;
    case Dir::Right:
        deltaX = Speed;
        break;
    default:
        break;
    }

    //越界检测
    //在这里做了一个处理：越界的移动按照刚好贴上边界，重新计算delta
    if (this->x() + deltaX < EdgeWidth) {
        deltaX = EdgeWidth - this->x();
    }
    if (this->x() + deltaX + 50 > WindowWidth - EdgeWidth) {
        deltaX = WindowWidth - EdgeWidth - this->x() - 50;
    }
    if (this->y() + deltaY < EdgeWidth) {
        deltaY = EdgeWidth - this->y();
    }
    if (this->y() + deltaY + 50 > WindowHeight - EdgeWidth) {
        deltaY = WindowHeight - EdgeWidth - this->y() - 50;
    }
    this->setX(this->x() + deltaX);
    this->setY(this->y() + deltaY);
}

void PlayRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
Q_UNUSED(option);
Q_UNUSED(widget);

    painter->setBrush(_player ? Qt::red : Qt::blue);
    painter->drawRect(0, 0, RectangleWight, RectangleHeight);
}

QRectF PlayRect::boundingRect() const
{
    return QRectF(0, 0, RectangleWight, RectangleHeight);
}

int PlayRect::getState()
{
    return _state;
}

void PlayRect::setState(int newState)
{
    if (    newState == State::Stop      ||
            newState == State::GoingUp   ||
            newState == State::GoingDown ||
            newState == State::GoingLeft ||
            newState == State::GoingRight) {
        _state = newState;
    }
}
