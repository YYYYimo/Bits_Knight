#include "gamewindow.h"
#include "playerangle.h"
#include "playerelf.h"
#include "playerwizzard.h"
#include "enemydemon.h"
#include "enemyzombie.h"
#include "player.h"
#include <QDebug>
#include <QMessageBox>
int GameWindow::enemynum = 0;
GameWindow::GameWindow(QWidget *parent, int player_type):
        QWidget(parent), curtime(0), playerType(player_type)
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

    addplayer(player_type);//根据角色选择界面选择加载的角色 todo
    lastenemytype = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    timer->start(15);
    startTime = QDateTime::currentDateTime();//记录游戏开始的时间
    setgameTimerLabel();

    lastenemytype = 1;

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
    QPixmap pixmapheart("://resource/img/ui_heart_full.png");
    QPixmap scaledPixmapheart = pixmapheart.scaled(30, 30, Qt::KeepAspectRatio);
    heart->setPixmap(scaledPixmapheart);
    heart->setGeometry(200, 3, 50, 50);

    QLabel* expbox = new QLabel(this);
    QPixmap pixmapexp("://resource/img/expbox.png");
    QPixmap scaledPixmapexp = pixmapexp.scaled(30, 30, Qt::KeepAspectRatio);
    expbox->setPixmap(scaledPixmapexp);
    expbox->setGeometry(280, 3, 50, 50);

    showhp = new QLabel(this);
    showhp->setFont(font);
    showhp->setGeometry(230, 10, 80, 30);
    QString hp = QString("%1").arg(play->m_hp);
    showhp->setText(hp);


    coinLable = new QLabel(this);
    coinLable->setFont(font);
    coinLable->setGeometry(155, 10, 80, 30);
    coinLable->setText("0");

    showexp = new QLabel(this);
    showexp->setFont(font);
    showexp->setGeometry(320, 10, 80, 30);
    QString Exp = QString("%1").arg(play->exp);
    showexp->setText(Exp);
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
        break;
    }
    case 1:
    {
        play = QSharedPointer<playerelf>(new playerelf());
        scene->addItem(play.data());
        play->setPos(750, 600);
        addplayerPointer(play);
        break;
    }
    case 2:
    {
        play = QSharedPointer<playerwizzard>(new playerwizzard());
        scene->addItem(play.data());
        play->setPos(750, 600);
        addplayerPointer(play);
        break;
    }
    default:
        break;
    }
}

void GameWindow::addenemy(int type)
{
    lastenemytype = -lastenemytype;
    int index = curtime % 8;
    qreal x, y;
    int direction;
    switch (index) { //根据时间得出怪物出现的位置，to do
    case 0:
        x = 400;
        y = 10;
        direction = 1;
        break;
    case 1:
        x = 800;
        y = 10;
        direction = 1;
        break;
    case 2:
        x = 1150;
        y = 400;
        direction = 2;
        break;
    case 3:
        x = 1150;
        y = 800;
        direction = 2;
        break;
    case 4:
        x = 800;
        y = 1150;
        direction = 3;
        break;
    case 5:
        x = 400;
        y = 1150;
        direction = 3;
        break;
    case 6:
        x = 10;
        y = 800;
        direction = 0;
        break;
    case 7:
        x = 10;
        y = 400;
        direction = 0;
        break;
    default:
        break;
    }
    if(enemynum <= 8)
    {
        switch (type)
        {
        case -1:
        {
            QSharedPointer<enemydemon> ene1 = QSharedPointer<enemydemon>(new enemydemon(play));
            scene->addItem(ene1.data());
            ene1->setPos(x, y);
            ene1->setType(type);
            ene1->setdirect(direction);
            addenemyPointer(ene1);
            enemynum++;
            break;
        }
        case 1:
        {
            QSharedPointer<enemyzombie> ene2 = QSharedPointer<enemyzombie>(new enemyzombie(play));
            scene->addItem(ene2.data());
            ene2->setPos(x, y);
            ene2->setType(type);
            ene2->setdirect(direction);
            addenemyPointer(ene2);
            enemynum++;
            break;
        }
        default:
            break;
        }
    }
}


void GameWindow::updateGame()
{
    if(isGamepause == false)
    {
        checkPlayerstate();
        scene->advance();
    }
}

void GameWindow::updateTimerLabel()
{
    curtime++;
    if(play->exp % 20 == 0)
        pauseGame();
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
    QString coin = QString("%1").arg(coins);
    coinLable->setText(coin);

    //更新经验值标签
    QString Exp = QString("%1").arg(play->exp);
    showexp->setText(Exp);
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

void GameWindow::pauseGame()
{
    QList<QGraphicsItem *> items = scene->items();
    foreach (QGraphicsItem *item, items) {
        if (Player* t1 = dynamic_cast<Player*>(item)) {
            t1->pauseAnimation();
        } else if (Enemy* t2 = dynamic_cast<Enemy*>(item)) {
            t2->pauseAnimation();
        }
    }
    // 停止计时器
    isGamepause = true;
    gameTimer->stop();
    timer->stop();
    CustomDialog* dialog = new CustomDialog(play, 0);
    connect(dialog, SIGNAL(finished(int)),
            this, SLOT(resumeGame()));
    dialog->setGeometry(800, 600, 500, 200);
    dialog->open();
}

void GameWindow::resumeGame()
{
    isGamepause = false;
    QList<QGraphicsItem *> items = scene->items();
    foreach (QGraphicsItem *item, items) {
        if (Player* t1 = dynamic_cast<Player*>(item)) {
            t1->resumeAnimation();
        } else if (Enemy* t2 = dynamic_cast<Enemy*>(item)) {
            t2->resumeAnimation();
        }
    }
    gameTimer->start();
    timer->start();
}




