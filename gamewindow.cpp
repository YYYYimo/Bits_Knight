#include "gamewindow.h"
#include "playerangle.h"
#include "player.h"

GameWindow::GameWindow(QWidget *parent):
        QWidget(parent), curtime(0)
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

    setgameTimerLabel();

    view->show();
}

GameWindow::~GameWindow()
{
    delete view;
    delete scene;
}

void GameWindow::setgameTimerLabel()
{
    gameTimer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));
    timer->start(1000);
    timerLable = new QLabel(this);
    QFont font("Arial", 24, QFont::Bold);
    timerLabel->setFont(font);
    timerLabel->setGeometry(10, 10, 50, 30);
    timerLabel->setText("00:00");
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

void GameWindow::addenemy(int type)
{
    switch (type) {
    case demon:
        
        break;
    default:
        break;
    }
}

void GameWindow::removeItem(QGraphicsItem item)
{
    scene->removeItem(item);
    delete item;
}

void GameWindow::updateGame()
{
    scene->advance();
}

void GameWindow::updateTimerLabel()
{
    curtime++;
    QDateTime currentTime = QDateTime::currentDateTime();
    // 计算时间差（毫秒）
    qint64 elapsedTime = startTime.msecsTo(currentTime);
    // 转换为分钟和秒钟
    int minutes = static_cast<int>(elapsedTime / 60000);
    int seconds = static_cast<int>((elapsedTime % 60000) / 1000);
    // 格式化时间字符串
    QString timeStr = QString("%1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));

    // 更新计时器标签的文本
    timerLabel->setText(timeStr);
}

