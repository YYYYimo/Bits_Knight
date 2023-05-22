#include "dropitem.h"
#include "gamewindow.h"
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPainter>

DropItem::DropItem(int t, qreal x, qreal y):type(t),m_x(x),m_y(y)
{
    width = 30;
    height = 30;
    if(t == coin)
    {
        coin_movie = new QMovie("://resource/gif/coin.gif");
        coin_movie->start();
    }
    else
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
        default:
            break;
        }

        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem();
        QPixmap pixmap(imgpath);
        pixmapItem->setPixmap(pixmap);
        pixmapItem->setPos(m_x, m_y);
        // 将图片项添加到场景中
        scene()->addItem(pixmapItem);
    }
}

void DropItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image = coin_movie->currentImage();
    painter->drawImage(QRectF(m_x, m_y, width, height), image);
    update();
}

QRectF DropItem::boundingRect() const
{
    return QRectF(m_x, m_y, width, height);
}

bool DropItem::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    return QGraphicsItem::collidesWithItem(other, mode);
}

void DropItem::rmdropItem(DropItem* item)
{
    scene()->removeItem(item);
    delete this;
}



