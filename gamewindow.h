#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include <vector>
#include <QDateTime>
#include "player.h"
#include "enemy.h"
#include "dropitem.h"

enum Enemytype {_demon = 0,  _zombie = 1};
class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void addplayer(int type);
    void addenemy(int type);
    void setgameTimerLabel();
    void checkPlayerstate();//to do
    //void nextlevel(); to do
    Player* play;
    int enemynum;
    int curtime;
    QDateTime startTime;
    QGraphicsView *view;
    QGraphicsScene *scene;
    
private slots:
    void updateGame(); //用于刷新游戏界面
    void updateTimerLabel(); //用于更新计时器数字显示
    
private:
    QTimer *timer; //用于刷新游戏界面
    QTimer *gameTimer; //用于记录游戏开始时间
    QLabel *timerLabel; //用于显示计时器时间
};

#endif // GAMEWINDOW_H
