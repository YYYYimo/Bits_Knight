#include "bullet.h"
#include <QPixmap>
Bullet::Bullet(int t, qreal x, qreal y):type(t),width(10),height(10),m_x(x),m_y(y)
{
    switch(t)
    {
    case angle:
        speed = 5;
        atk = 2;
        imgpath = "://resource/img/bulletForangle.png";
    case elf:
        speed = 5;
        atk = 2;
    case demon:
        speed = 5;
        atk = 2;
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
    QPixmap image(imgpath);
    image->setPixmap(image);
    image->setPos(m_x, m_y);
    // 将图片项添加到场景中
    GameWindow::scene->addItem(image);
    update();
}

bool Bullet::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{

    //tips: 直接从item类中读取伤害数值而不是直接设定数值
    switch(this->m_type)
    {
    case angle:
        damage = 1;
    case elf:
        damage = 2;
    case demon:
        damage = 2;
    }
    // 检测子弹与敌人的碰撞
    if (other->type() == Enemy::Type) 
    {
        const Enemy* enemy = qgraphicsitem_cast<const Enemy*>(other);
        if (enemy && collidesWithItem(enemy, mode)) 
        {
            // 子弹与敌人发生碰撞，敌人受伤扣血
            enemy->takeDamage(damage);
            GameWindow::scene->removeItem(this);
            delete this;
            return true;
        }
    }
    else
    {
        const Player* player = qgraphicsitem_cast<const Player*>(other);
        if(player && collidesWithItem(player, mode))
        {
            player->takeDamage(damage);
            GameWindow::scene->removeItem(this);
            delete this;
            return true;
        }
    }
    return false;
}

void Bullet::bullmove()
{
    //实现子弹追踪和移动逻辑
}


