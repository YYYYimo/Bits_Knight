#include "Pet.h"
#include <QImage>

Pet::Pet(qreal x, qreal y, QSharedPointer<Player> pl) : x(x), y(y), play(pl)
{
    width = 50;
    height = 50;
    petmovie = new QMovie("://resource/gif/skelet_run.gif");
    petmovie->start();
}

void Pet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    move();
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image = petmovie->currentImage();
    painter->drawImage(QRectF(x, y, width, height), image);
    update();
}

QRectF Pet::boundingRect() const
{
    return QRectF(x, y, width, height);
}

void Pet::move()
{
    x = play->m_x - 50;
    y = play->m_y - 50;
}
