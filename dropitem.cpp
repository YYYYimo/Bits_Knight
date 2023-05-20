#include "dropitem.h"
#include <QGraphicsPixmapItem>

DropItem::DropItem(int t, qreal x, qreal y):type(t),m_x(x),m_y(y)
{
    switch(t)
    {
    case red:
       imgpath = "://resource/img/flask_big_red.png"; break;
    case blue:
        imgpath = "://resource/img/flask_big_blue.png"; break;
    case yellow:
        imgpath = "://resource/img/flask_big_yellow.png"; break;
    case green:
        imgpath = "://resource/img/flask_big_green.png"; break;
    }

    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem();
    QPixmap pixmap(imgpath);
    pixmapItem->setPixmap(pixmap);
    pixmapItem->setPos(m_x, m_y);
    // 将图片项添加到场景中
    scene->addItem(pixmapItem);
}

QRectF DropItem::boundingRect() const
{
    return QRectF(m_x, m_y, width, height);
}




