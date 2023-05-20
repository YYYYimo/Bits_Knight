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

    QRectF boundingRect() const override;
    int type() const override;
    void rmdropItem();

    int type;
    QString imgpath;
private:
    qreal m_x;
    qreal m_y;
    qreal wigth;
    qreal height;
};

#endif // DROPITEM_H
