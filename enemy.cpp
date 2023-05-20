#include "enemy.h"
#include "dropitem.h"
#include "gamewindow.h"
#include <QPixmap>

Enemy::enemy()
 : m_type(0), m_hp(0), m_attack(0), m_x(0), m_y(0), m_speed(0), m_movie(nullptr)
{

}

QRect Enemy::boundingRect() const
{
    return QRectF(m_x, m_y, width, height);
}

void Enemy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    enemove();
    QImage image = m_movie->currentImage();
    painter->drawImage(QRectF(m_x, m_y, width, height), image);
    update();
}

bool Enemy::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    return QGraphicsItem::collidesWithItem(other, mode);
}


void Player::setMovie(const QString& path)
{
    // 设置角色的动画
    if (m_movie)
    {
        m_movie->stop();
        delete m_movie;
        m_movie = nullptr;
    }

    m_movie = new QMovie(path);
    m_movie->setCacheMode(QMovie::CacheAll);
    m_movie->start();
}

void Enemy::setSpeed(qreal speed)
{
    // 设置角色的移动速度
    m_speed = speed;
}

void Enemy::setPos(qreal x, qreal y)
{
    // 设置角色的位置
    m_x = x;
    m_y = y;
}

void Enemy::setHP(int hp)
{
    // 设置角色的生命值
    m_hp = hp;
}

void Enemy::setAttack(int attack)
{
    // 设置角色的攻击力
    m_attack = attack;
}

bool Enemy::judge_dead()
{
    if (m_hp <= 0)
        return true;
}

QPoint Enemy::getPlayerPos(Player *p)
{
    QPointF playerpos;
    playerpos.rx() = p->m_x;
    playerpos.ry() = p->m_y;
    QPoint point(playerpos.x(), playerpos.y());
    return point;
}

void Enemy::enemove()
{
    QPointF playerpos = getPlayerPos(GameWindow.play);
    qreal x = playerpos.x();
    qreal y = playerpos.y();
    qreal dx = 0, dy = 0;
    qreal dis_x = abs(x - m_x), dis_y = abs(y - m_y);
    //通过计算x，y移动后敌人和玩家之间缩短的距离来得出最佳移动方案
    if(((dis_x - m_speed) * (dis_x - m_speed) + dis_y * dis_y) >=
            (dis_x * dis_x + (dis_y - m_speed) * (dis_y - m_speed)))
    {
        //水平方向移动，判断左移还是右移
        if((x - m_x) >= 0) //右
            dx = m_speed;
        else
            dx = -m_speed;
    }
    else
    {
        //竖直方向移动，判断上下
        if((y - m_y) >= 0) //下
            dy = m_speed;
        else
            dy = -m_speed;
    }
    // 更新角色的位置
    m_x += dx;
    m_y += dy;
    setPos(m_x, m_y);
}

void Enemy::rmenemy(int type)
{
    delete this->m_movie;
    DropItem dropItem(type);
    GameWindow::scene->addItem(dropItem);
}









