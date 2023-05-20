#ifndef DROPITEM_H
#define DROPITEM_H
#include <QGraphicsItem>
#include <QString>
enum dropItem_type {red = 0, yellow = 1, blue = 2, green = 3};
class DropItem: public QGraphicsItem
{
public:
    DropItem(int t);
    ~DropItem();
    void setPos(qreal x, qreal y);

    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    int type() const override;

    int type;
    QString imgpath;
private:
    qreal m_x;
    qreal m_y;

};

#endif // DROPITEM_H
