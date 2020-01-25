#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QKeyEvent>
#include <QTcpSocket>
#include <QList>

#include "settings.h"
#include "playrect.h"
#include "netthread.h"

class MainView : public QGraphicsView
{
    Q_OBJECT

protected:
    void keyReleaseEvent(QKeyEvent *event); //按键释放以后出发该事件

private:
    NetThread          *_thread;        //网络线程，包括socket和多线程相关
    PlayRect           *_r1, *_r2;      //玩家控制的方块，r1是玩家1，颜色为红色，玩家2位蓝色
    QGraphicsScene     *_scene;         //游戏场景
    QGraphicsItemGroup *_edges;         //碰撞边缘，由4条线组成一个item group
    QGraphicsTextItem  *_msgWaiting;    //文字item，显示等待信息

private:
    inline PlayRect *nowPlayer()        //为了方便起见，写一个根据设置，获取当前玩家方块指针的函数
    {return MyPlayer ? _r1 : _r2;}

public slots:
    void updatePositions(int x1, int y1, int x2, int y2);   //接收到信号后，更新方块位置
    void connected();                                       //接收到信号后，移除文字item

public:
    MainView();
    ~MainView();
};
#endif // MAINVIEW_H
