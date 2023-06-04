#ifndef PET_H
#define PET_H
#include <QGraphicsItem>
#include <QMovie>
#include <QSharedPointer>
#include "player.h"
#include "subject.h"
class Pet : public QGraphicsItem,  public subject
{
public:
    Pet(qreal x, qreal y, QSharedPointer<Player> pl);
    ~Pet() {}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const override;
    void move();
private:
    QMovie* petmovie;
    qreal x;
    qreal y;
    qreal width;
    qreal height;
    QSharedPointer<Player> play;
};

#endif // PET_H
