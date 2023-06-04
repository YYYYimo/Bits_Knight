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
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
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
    enum SaveFormat {Json};
    GameWindow(int player_type, int isRenew);
    ~GameWindow();
    void addplayer(int type);
    void addenemy(int type);
    void addpet();
    void setgameTimerLabel();
    void checkPlayerstate();
    void pauseGame();
    void endGame(int situ);
    void keyPressEvent(QKeyEvent* event);
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
    void resumeGame();//重启游戏
    void saveGame();//保存游戏
    void loadGame();//加载游戏
    
private:
    int ishavepet; //玩家是否拥有宠物
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
