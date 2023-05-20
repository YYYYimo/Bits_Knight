#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include "player.h"
#include "enemy.h"
#include "dropitem.h"

class GameWindow : public QWidget
{
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void addplayer(int type);
    void addenemy(int type);
    void removeItem(QGraphicsItem item);
    void updateGame();
    Player* play;

    QGraphicsView *view;
    QGraphicsScene *scene;
    QTimer *timer; //用于刷新游戏界面
    QTimer *gameTimer; //用于记录游戏开始时间
    QLabel *timerLable; //用于显示计时器时间
};

#endif // GAMEWINDOW_H
