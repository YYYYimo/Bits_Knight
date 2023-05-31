#ifndef DROPITEM_H
#define DROPITEM_H
#include <QGraphicsItem>
#include <QString>
#include <QMovie>
#include <QSharedPointer>
#include <QEnableSharedFromThis>
#include "subject.h"
enum dropItem_type {red = 0, yellow = 1, blue = 2, green = 3, coin = 4};
class DropItem: public QGraphicsItem, public subject, public QEnableSharedFromThis<DropItem>
{
public:
    DropItem(int t, qreal x, qreal y, QSharedPointer<Player> p);
    DropItem(DropItem*) {}
    ~DropItem() {}
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect() const override;
    void rmdropItem(QSharedPointer<DropItem> item);
    void pickup();
    int type;
    QMovie* coin_movie;
    QString imgpath;
    QSharedPointer<Player> play;

private:
    qreal m_x;
    qreal m_y;
    qreal width;
    qreal height;
};

#endif // DROPITEM_H
