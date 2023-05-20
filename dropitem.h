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

    int type;
    QString imgpath;


};

#endif // DROPITEM_H
