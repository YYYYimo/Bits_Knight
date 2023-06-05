#include "bullet.h"
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QtMath>
#include <QPointF>
#include <QLineF>
#include <QList>
#include <QVector>
#include <limits>
Bullet::Bullet(int t, qreal x, qreal y, QSharedPointer<Player> pl):m_type(t), m_x(x), m_y(y)
{
    //子弹发射时选定一个离玩家最近的敌人，并持续追踪
    direct = 0;
    qreal mindis = std::numeric_limits<qreal>::max();
    target = nullptr;
    QVector<QSharedPointer<Enemy>>::Iterator it = enevec.begin();
    for(it = enevec.begin(); it != enevec.end(); ++it)
    {
        QSharedPointer<Enemy> e = *it;
        QPointF point1(m_x, m_y);
        QPointF point2(e->m_x, e->m_y);
        QLineF line(point1, point2);
        qreal dis = line.length();
        if(dis < mindis)
        {
            mindis = dis;
            target = e;
        }
        play = pl;
    }
    switch(t)
    {
    case angel:
    {
        m_speed = 5;
        m_atk = 2;
        imgpath = "://resource/img/bulletForangle.png";
        break;
    }
    case elf:
    {
        m_speed = 5;
        m_atk = 2;
        imgpath = "://resource/img/bulletForElf.png";
        break;
    }
    case wizzard:
        m_speed = 5;
        m_atk = 2;
        imgpath = "://resource/img/bulletForWizzard.png";
    }
    updatetime = new QTimer(this);
    connect(updatetime, &QTimer::timeout, this, &Bullet::slotTimeOut);
    updatetime->start(15);
}

Bullet::Bullet(int t, qreal x, qreal y, int direction, QSharedPointer<Player> pl): m_type(t), m_x(x), m_y(y), direct(direction)
{
    target = nullptr;
    play = pl;
    m_speed = 5;
    m_atk = 1;
    imgpath = "://resource/img/bulletForZombie.png";
    updatetime = new QTimer(this);
    connect(updatetime, &QTimer::timeout, this, &Bullet::slotTimeOut);
    updatetime->start(15);
}

QRectF Bullet::boundingRect() const
{
    return QRectF(m_x, m_y, 50, 50);
}

void Bullet::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image(imgpath);
    painter->drawImage(QRectF(m_x, m_y, 50, 50), image);
    update();
}

void Bullet::setPos(qreal x, qreal y)
{
    m_x = x;
    m_y = y;
}

void Bullet::bullmove()
{
    if(target)
    {
        qreal dx = target->m_x - m_x;
        qreal dy = target->m_y - m_y;
        if(dx >= 0 && dy >= 0)
        {
            if(dx >= 10 && dy >= 10)
            {
                m_x += m_speed;
                m_y += m_speed;
            }
            else if(dx < 10 && dy >= 10)
                m_y += m_speed;
            else
                m_x += m_speed;
        }
        else if(dx < 0 && dy >= 0)
        {
            if(dx < -10 && dy >= 10)
            {
                m_x -= m_speed;
                m_y += m_speed;
            }
            else if(dx >= -10 && dy < 10)
                m_y -= m_speed;
            else
                m_x += m_speed;
        }
        else if(dx >= 0 && dy < 0)
        {
            if(dx >= 10 && dy <= -10)
            {
                m_x += m_speed;
                m_y -= m_speed;
            }
            else if(dx < 10 && dy >= -10)
                m_y += m_speed;
            else
                m_x -= m_speed;
        }
        else
        {
            if(dx < -10 && dy < -10)
            {
                m_x -= m_speed;
                m_y -= m_speed;
            }
            else if(dx >= -10 && dy >= -10)
                m_y -= m_speed;
            else
                m_x -= m_speed;
        }
        setPos(m_x, m_y);
    }
    else if(target == nullptr && m_type != _zombie)
    {
        rmbullet();
    }
    else
    {
        qreal dx = 0;
        qreal dy = 0;
        if(direct == _Right)
        {
            dx = m_speed;
        }
        else if(direct == _Down)
        {
            dy = m_speed;
        }
        else if(direct == _Left)
        {
            dx = -m_speed;
        }
        else
        {
            dy = -m_speed;
        }
        setPos(m_x + dx, m_y + dy);
    }
}

void Bullet::advance()
{
    bullmove();
    QPointF newPos(m_x, m_y);
    //判断子弹是否超出场景范围
    if(!scene()->sceneRect().contains(newPos))
    {
        rmbullet();
    }
}

void Bullet::rmbullet()
{
    updatetime->stop();
    QSharedPointer<Bullet> bull = sharedFromThis();
    removebullPointer(bull);
    scene()->removeItem(bull.data());
}

void Bullet::attackEne()
{
    int damage = play->m_attack;
    if(collidesWithItem(target.data(), Qt::IntersectsItemBoundingRect))
    {
        target->takeDamage(damage);
        rmbullet();
    }
}

void Bullet::attackPla()
{
    if(collidesWithItem(play.data(), Qt::IntersectsItemBoundingRect))
    {
        play->takeDamage(m_atk);
        rmbullet();
    }
}


void Bullet::slotTimeOut()
{
    bullmove();
    if(m_type != _zombie)
        attackEne();
    else
        attackPla();
}


