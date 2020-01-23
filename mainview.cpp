#include "mainview.h"

void MainView::keyReleaseEvent(QKeyEvent *event)
{
    if (_thread->isConnected()) {
        switch (event->key()) {
        case Qt::Key_Up:
            nowPlayer()->move(PlayRect::Dir::Up);
            _thread->setCommand(CommandUp);
            break;
        case Qt::Key_Down:
            nowPlayer()->move(PlayRect::Dir::Down);
            _thread->setCommand(CommandDown);
            break;
        case Qt::Key_Right:
            nowPlayer()->move(PlayRect::Dir::Right);
            _thread->setCommand(CommandRight);
            break;
        case Qt::Key_Left:
            nowPlayer()->move(PlayRect::Dir::Left);
            _thread->setCommand(CommandLeft);
            break;
        default:
            break;
        }
    }
}

void MainView::updatePositions(int x1, int y1, int x2, int y2)
{
    _r1->setPos(x1, y1);
    _r2->setPos(x2, y2);
}

void MainView::connected()
{
    _scene->removeItem(_msgWaiting);
    delete  _msgWaiting;
    _scene->addItem(_r1);
    _scene->addItem(_r2);
    _scene->addItem(_edges);
}

MainView::MainView()
{
    _scene = new QGraphicsScene();
    _scene->setSceneRect(0, 0, WindowWidth, WindowHeight);

    _edges = new QGraphicsItemGroup;

    QGraphicsLineItem *l1, *l2, *l3, *l4;
    l1 = new QGraphicsLineItem(EdgeWidth, EdgeWidth, EdgeWidth, WindowHeight - EdgeWidth);
    l2 = new QGraphicsLineItem(EdgeWidth, EdgeWidth, WindowWidth - EdgeWidth,  EdgeWidth);
    l3 = new QGraphicsLineItem(WindowWidth - EdgeWidth, EdgeWidth, WindowWidth - EdgeWidth, WindowHeight - EdgeWidth);
    l4 = new QGraphicsLineItem(EdgeWidth, WindowHeight - EdgeWidth, WindowWidth - EdgeWidth, WindowHeight - EdgeWidth);
    _edges->addToGroup(l1);
    _edges->addToGroup(l2);
    _edges->addToGroup(l3);
    _edges->addToGroup(l4);

    _r1 = new PlayRect(Player1);
    _r2 = new PlayRect(Player2);

    _msgWaiting = new QGraphicsTextItem("Waiting for connect...");
    _msgWaiting->setDefaultTextColor(Qt::blue);
    QFont font = _msgWaiting->font();
    font.setPixelSize(TextFontSize);
    _msgWaiting->setFont(font);
    _msgWaiting->setPos(TextPositionX, TextPositionY);

    _scene->addItem(_msgWaiting);

    this->setScene(_scene);
    this->setFixedSize(WindowWidth, WindowHeight);

    _thread = new NetThread();
    connect(_thread, SIGNAL(connectedSignal()), this, SLOT(connected()));
    connect(_thread, SIGNAL(coords(int, int, int, int)), this, SLOT(updatePositions(int, int, int, int)));
    _thread->start();
}

MainView::~MainView()
{
    _thread->stop();
    _thread->wait();
    delete _thread;
    delete _scene;
}
