#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "player.h"

class GameWindow : public QWidget
{
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void addplayer(int type);
    void updateGame();
    Player* play;


private slots:
private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QTimer *timer;
};

#endif // GAMEWINDOW_H
