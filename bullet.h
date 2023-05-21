#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QString>
#include "player.h"
#include "enemy.h"
#include "gamewindow.h"
enum bullettype {angel, elf, demon};
class Bullet : public QGraphicsItem
{
public:
    Bullet(int t, qreal x, qreal y);
    ~Bullet();
    
    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    void setPos();
    void advance();
    void bullmove();

private:
    int m_type;
    int m_speed;
    int m_atk;
    int width;
    int height;
    QString imgpath;
    qreal m_x;
    qreal m_y;
    Enemy* target;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // BULLET_H
