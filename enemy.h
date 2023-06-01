#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPoint>
#include <QTimer>
#include <QObject>
#include <QPainterPath>
#include <QSharedPointer>
#include "player.h"
#include "gamewindow.h"
#include "subject.h"
enum Enemytype {demon = -1, zombie = 1};
enum direct {Right = 0, Down = 1, Left = 2, Up = 3};
class Player;
class Enemy : public QGraphicsItem, public QObject, public subject
{
    friend class Player;
public:
    Enemy();
    Enemy(Enemy*) {}//
    ~Enemy();
    QRectF boundingRect() const override;
    QPainterPath shape() const;
    QPointF getPlayerPos(); //定位玩家位置
    void enemove();//敌人移动逻辑
    void rmenemy();
    void uplevel();  // todo: 怪物生成一段时间后自动升级为大怪物
    void takeDamage(int dam);
    void attack();

    void setMovie(const QString& path);
    void setSpeed(qreal speed);
    void setPos(qreal x, qreal y);
    void setHP(int hp);
    void setType(int t);
    void setAttack(int attack);
    void checkEnemystate();
    void advance();
    void setdirect(int d);
    void pauseAnimation();//使动画停止
    void resumeAnimation();//使动画继续进行下去
    qreal m_x;
    qreal m_y;

protected:
    int m_type;
    int m_hp;
    int m_attack;
    int width;
    int height;
    int lifespan;
    int direct;
    qreal m_speed;
    QSharedPointer<Player> play;
    QMovie* m_movie;
    QTimer* lifespantime;//生存时间
    QTimer* updatetime;//刷新时间
private slots:
    void updateEnemy();
    void slotTimeOut();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};




#endif // ENEMY_H
