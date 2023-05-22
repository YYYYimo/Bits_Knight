#ifndef DROPITEM_H
#define DROPITEM_H
#include <QGraphicsItem>
#include <QString>
#include <QMovie>
enum dropItem_type {red = 0, yellow = 1, blue = 2, green = 3, coin = 4};
class DropItem: public QGraphicsItem
{
public:
    DropItem(int t, qreal x, qreal y);
    ~DropItem();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    void rmdropItem(DropItem* item);

    int type;
    QMovie *coin_movie;
    QString imgpath;

private:
    qreal m_x;
    qreal m_y;
    qreal width;
    qreal height;
};

#endif // DROPITEM_H
