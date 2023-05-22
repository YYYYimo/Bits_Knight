#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPoint>
#include <QTimer>
#include <QObject>
#include "config.h"
#include "player.h"
#include "gamewindow.h"

class Player;
class Enemy : public QGraphicsItem, public QObject
{
    friend class Player;
public:
    Enemy();

    QRectF boundingRect() const override;
    bool collidesWithItem(QGraphicsItem* other, Qt::ItemSelectionMode mode) const;
    QPoint getPlayerPos(); //定位玩家位置
    void enemove(); //敌人移动逻辑
    void rmenemy(int type);
    void uplevel();  // todo: 怪物生成一段时间后自动升级为大怪物
    void takeDamage(int dam);
    void attack(int type);

    void setMovie(const QString& path);
    void setSpeed(qreal speed);
    void setPos(qreal x, qreal y);
    void setHP(int hp);
    void setAttack(int attack);
    void checkEnemystate();
    void advance();

protected:
    int m_type;
    int m_hp;
    int m_attack;
    int width;
    int height;
    int lifespan;
    qreal m_x;
    qreal m_y;
    qreal m_speed;
    QMovie* m_movie;
    QTimer* lifespantime;//生存时间
    QTimer* updatetime;//刷新时间
private slots:
    void updateEnemy();
    void slotTimeOut();
    //动画刷新界面； 与主场景的联动刷新
    //主场景中不需要实现刷新？只用在item中各自刷新。

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};




#endif // ENEMY_H
