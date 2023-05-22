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

    addplayer(0);//根据角色选择界面选择加载的角色

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    timer->start(10);
    startTime = QDateTime::currentDateTime();
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
    int index = curtime % 7;
    qreal x, y;
    switch (index) { //根据时间得出怪物出现的位置
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
        x = 1490;
        y = 50;
    case 5:
        x = 1490;
        y = 420;
    case 6:
        x = 1490;
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
            Enemy* ene1 = new Enemy;
            ene1->setMovie("://resource/gif/small_demon_run.gif");
            ene1->setSpeed(5);
            ene1->setPos(x, y);
            ene1->setHP(10);
            ene1->setAttack(2);
            scene->addItem(ene1);
            enemynum++;
            break;
        }
        case 1:
        {
            Enemy* ene2 = new Enemy;
            ene2->setMovie("://resource/gif/small_zombie_run.gif");
            ene2->setSpeed(5);
            ene2->setPos(x, y);
            ene2->setHP(10);
            ene2->setAttack(2);
            scene->addItem(ene2);
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
    checkPlayerstate();
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

void GameWindow::checkPlayerstate()
{
    if(play->m_hp <= 0)
    {
        timer->stop();
        gameTimer->stop();
        //加载失败界面
    }
    if(curtime == 120)
    {
        timer->stop();
        gameTimer->stop();
        //nextlevel();
    }
}

