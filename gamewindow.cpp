#include "gamewindow.h"
#include "playerangle.h"
#include "player.h"

GameWindow::GameWindow(QWidget *parent):
        QWidget(parent)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1500,1200);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);//设置不适用索引

    view = new QGraphicsView(scene, this);
    view->resize(1502,1202);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/res/resource/img/map/Map001.png"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    addplayer(0);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    timer->start(10);

    view->show();
}

GameWindow::~GameWindow()
{
    delete view;
    delete scene;
}

void GameWindow::addplayer(int type)
{
    switch (type) {
    case 0:
    {
        play = new playerAngle();
        scene->addItem(play);
    }

        break;
    default:
        break;
    }
}

void GameWindow::updateGame()
{
    scene->update();
}

