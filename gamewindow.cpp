#include "gamewindow.h"
#include "playerangle.h"
#include "enemydemon.h"
#include "player.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent):
        QWidget(parent), curtime(0)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1500,1200);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);//设置不适用索引

    view = new QGraphicsView(scene, this);
    view->resize(1502,1202);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap("://resource/img/map/Map001.png"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    addplayer(0);//根据角色选择界面选择加载的角色 todo
    lastenemytype = 0;
    enemynum = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    timer->start(15);
    startTime = QDateTime::currentDateTime();//记录游戏开始的时间
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
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));
    gameTimer->start(1000);
    timerLabel = new QLabel(this);
    QFont font("Arial", 14, QFont::Bold);
    timerLabel->setFont(font);
    timerLabel->setGeometry(10, 10, 80, 30);
    timerLabel->setText("00:00");

    QMovie* movie = new QMovie("://resource/gif/coin.gif");
    movie->setScaledSize(QSize(20, 20));
    movie->start();
    QLabel* label = new QLabel(this);
    label->setMovie(movie);
    label->setGeometry(120, 1, 50, 50); // 设置位置和大小
    label->show();

    QLabel* heart = new QLabel(this);
    QPixmap pixmap("://resource/img/ui_heart_full.png");
    QPixmap scaledPixmap = pixmap.scaled(30, 30, Qt::KeepAspectRatio);
    heart->setPixmap(scaledPixmap);
    heart->setGeometry(200, 3, 50, 50);

    showhp = new QLabel(this);
    showhp->setFont(font);
    showhp->setGeometry(230, 10, 80, 30);
    QString hp = QString("%1").arg(play->m_hp);
    showhp->setText(hp);


    coinLable = new QLabel(this);
    coinLable->setFont(font);
    coinLable->setGeometry(155, 10, 80, 30);
    coinLable->setText("0");
}

void GameWindow::addplayer(int type)
{
    switch (type) {
    case 0:
    {
        play = QSharedPointer<playerAngle>(new playerAngle());
        scene->addItem(play.data());
        play->setPos(750, 600);
        addplayerPointer(play);
        qDebug() << "play: " << play.data();

        
    }

        break;
    default:
        break;
    }
}

void GameWindow::addenemy(int type)
{
    int index = curtime % 7;
    qreal x, y;
    switch (index) { //根据时间得出怪物出现的位置，to do
    case 0:
        x = 10;
        y = 10;
        break;
    case 1:
        x = 390;
        y = 10;
        break;
    case 2:
        x = 770;
        y = 10;
        break;
    case 3:
        x = 1150;
        y = 10;
    case 4:
        x = 1150;
        y = 50;
    case 5:
        x = 1150;
        y = 420;
    case 6:
        x = 1150;
        y = 800;
    default:
        break;
    }
    if(enemynum <= 7)
    {
        switch (type)
        { //选择加载的怪物类型
        //todo：对于不同的怪物类型有不同的设定
        case 0:
        {
            QSharedPointer<enemydemon> ene1 = QSharedPointer<enemydemon>(new enemydemon(play));
            scene->addItem(ene1.data());
            ene1->setPos(x, y);
            addenemyPointer(ene1);
            enemynum++;
            break;
        }
        case 1:
        {
            break;
        }
        default:
            break;
        }
    }
}


void GameWindow::updateGame()
{
    checkPlayerstate();
    scene->advance();
}

void GameWindow::updateTimerLabel()
{
    curtime++;
    addenemy(lastenemytype);
     //顺便产生新的敌人
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
    //更新血量标签
    QString hp = QString("%1").arg(play->m_hp);
    showhp->setText(hp);

    //更新金币标签
    QString coin = QString("%1").arg(play->coins);
    coinLable->setText(coin);

}

void GameWindow::checkPlayerstate()
{
    if(play->m_hp <= 0)
    {
        timer->stop();
        gameTimer->stop();
        //加载失败界面 to do
    }
    if(curtime == 120)
    {
        timer->stop();
        gameTimer->stop();
        //nextlevel(); to do
    }
}



