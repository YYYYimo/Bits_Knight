#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include <QDateTime>
#include <QString>
#include <QVector>
#include <QSharedDataPointer>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>
#include "player.h"
#include "enemy.h"
#include "dropitem.h"
#include "subject.h"
#include "customdialog.h"
class Player;
class Enemy;
class GameWindow : public QWidget, public subject
{
    Q_OBJECT
public:
    GameWindow(QWidget *parent = nullptr, int player_type = 0);
    ~GameWindow();
    void addplayer(int type);
    void addenemy(int type);
    void setgameTimerLabel();
    void checkPlayerstate();
    void pauseGame();
    //void nextlevel(); to do
    static int enemynum;
    int curtime;
    int lastenemytype;
    QSharedPointer<Player> play;
    int playerType;
    bool isGamepause;
    QDateTime startTime;
    QGraphicsView* view;
    QGraphicsScene* scene;
    
private slots:
    void updateGame(); //用于刷新游戏界面
    void updateTimerLabel(); //用于更新计时器数字显示
    void resumeGame();
    
private:
    QTimer* timer; //用于刷新游戏界面
    QTimer* gameTimer; //用于记录游戏开始时间
    QLabel* timerLabel; //用于显示计时器时间
    QLabel* coinLable;
    QLabel* showhp;
    QLabel* showexp;
    QGraphicsProxyWidget* dialogProxy;
    QGraphicsLinearLayout *layout;
};

#endif // GAMEWINDOW_H
