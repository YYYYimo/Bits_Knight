#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QString>
#include "gamewindow.h"
#include "enemy.h"
#include "player.h"
#include "suject.h"
enum bullettype {angel, elf};
class Bullet : public QGraphicsItem, public subject
{
public:
    Bullet(int t, qreal x, qreal y);
    ~Bullet(){}
    
    QRectF boundingRect() const override;
    bool collidesWithItem(QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    void setPos(qreal x, qreal y);
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
