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
#define PI 3.1415926
Bullet::Bullet(int t, qreal x, qreal y):m_type(t), m_x(x), m_y(y)
{
    //子弹发射时选定一个离玩家最近的敌人，并持续追踪
    qreal mindis = std::numeric_limits<qreal>::max();
    target = nullptr;
    QVector<Enemy*>::Iterator it = enevec.begin();
    for(it = enevec.begin(); it != enevec.end(); ++it)
    {
        Enemy* e = *it;
        QPointF point1(m_x, m_y);
        QPointF point2(e->m_x, e->m_y);
        QLineF line(point1, point2);
        qreal dis = line.length();
        if(dis < mindis)
        {
            mindis = dis;
            target = e;
        }
    }
    if(target == nullptr)
        qDebug() << "null";
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
        break;
    }
    }
}

QRectF Bullet::boundingRect() const
{
    return QRectF(m_x, m_y, width, height);
}

void Bullet::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image(imgpath);
    painter->drawImage(QRectF(m_x, m_y, width, height), image);
    update();
}

bool Bullet::collidesWithItem(QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    int damage;
    //tips: 直接从item类中读取伤害数值而不是直接设定数值
    switch(this->m_type)
    {
    case angel:
        damage = 1;
    case elf:
        damage = 2;
    }
    // 检测子弹与敌人的碰撞
    if (other->type() == Enemy::Type) 
    {
        Enemy* enemy = qgraphicsitem_cast<Enemy*>(other);
        if (enemy && collidesWithItem(enemy, mode)) 
        {
            // 子弹与敌人发生碰撞，敌人受伤扣血
            enemy->takeDamage(damage);
            scene()->removeItem(const_cast<Bullet*>(this));
            delete this;
            return true;
        }
    }
    else
    {
        Player* player = qgraphicsitem_cast<Player*>(other);
        if(player && collidesWithItem(player, mode))
        {
            player->takeDamage(damage);
            scene()->removeItem(const_cast<Bullet*>(this));
            delete this;
            return true;
        }
    }
    return false;
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
            if(dx >= 20 && dy >= 20)
            {
                m_x += m_speed;
                m_y += m_speed;
            }
            else if(dx <= 20 && dy >= 20)
                m_y += m_speed;
            else
                m_x += m_speed;
        }
        else if(dx <= 0 && dy >= 0)
        {
            if(dx <= -20 && dy >= 20)
            {
                m_x -= m_speed;
                m_y += m_speed;
            }
            else if(dx >= -20 && dy <= 20)
                m_y -= m_speed;
            else
                m_x += m_speed;
        }
        else if(dx >= 0 && dy <= 0)
        {
            if(dx >= 20 && dy <= -20)
            {
                m_x += m_speed;
                m_y -= m_speed;
            }
            else if(dx <= 20 && dy >= -20)
                m_y += m_speed;
            else
                m_x -= m_speed;
        }
        else
        {
            if(dx <= -20 && dy <= -20)
            {
                m_x -= m_speed;
                m_y -= m_speed;
            }
            else if(dx >= -20 && dy >= -20)
                m_y -= m_speed;
            else
                m_x -= m_speed;
        }
        setPos(m_x, m_y);
    }
}

void Bullet::advance()
{
    bullmove();
    QPointF newPos(m_x, m_y);
    //判断子弹是否超出场景范围
    if(!scene()->sceneRect().contains(newPos))
    {
        scene()->removeItem(this);
        delete this;
        return;
    }
}


