#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPoint>
#include "player.h"
#include "gamewindow.h"

class Enemy : public QGraphicsItem
{
public:
    enemy();

    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    bool judge_dead();
    QPoint getPlayerPos(Player *p); //定位玩家位置
    void enemove(); //敌人移动逻辑
    void rmenemy(int type);

    void setMovie(const QString& path);
    void setSpeed(qreal speed);
    void setPos(qreal x, qreal y);
    void setHP(int hp);
    void setAttack(int attack);

    void advance();

    int m_type;
    int m_hp;
    int m_attack;
    int width;
    int height;
    qreal m_x;
    qreal m_y;
    qreal m_speed;
    QMovie* m_movie;


protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};




#endif // ENEMY_H
