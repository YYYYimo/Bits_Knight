#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPoint>
#include <QTimer>
#include "player.h"
#include "gamewindow.h"

class Enemy : public QGraphicsItem
{
public:
    enemy();

    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    QPoint getPlayerPos(Player *p); //定位玩家位置
    void enemove(); //敌人移动逻辑
    void rmenemy(int type);
    //void uplevel();   todo: 怪物生成一段时间后自动升级为大怪物

    void setMovie(const QString& path);
    void setSpeed(qreal speed);
    void setPos(qreal x, qreal y);
    void setHP(int hp);
    void setAttack(int attack);
    void checkEnemystate();
    void advance();

private:
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
    QTimer* lifespantime;
private slots:
    void updateEnemy();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};




#endif // ENEMY_H
