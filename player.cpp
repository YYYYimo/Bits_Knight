#include "player.h"
#include <QImage>
#include <QMovie>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QObject>

Player::Player()
    : m_type(0), m_hp(0), m_attack(0), m_x(0), m_y(0), m_speed(0), m_movie(nullptr), lifespan(0)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    keyRespondTimer = new QTimer;	//Create a timer object and connect signals and slots in the constructor
    connect(keyRespondTimer, &QTimer::timeout, this, &Player::slotTimeOut);
    keyRespondTimer->start(10);
}

QRectF Player::boundingRect() const
{
    return QRectF(m_x, m_y, width, height);
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image = m_movie->currentImage();
    painter->drawImage(QRectF(m_x, m_y, width, height), image);
    update();
}

bool Player::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
    // Check if the other item is a DropItem
        const DropItem* dropItem = dynamic_cast<const DropItem*>(other);
        if (dropItem)
        {
            // Get the bounding rectangles of the player and the drop item
            QRectF playerRect = boundingRect();
            QRectF dropItemRect = dropItem->boundingRect();

            // Check if the player's rectangle intersects with the drop item's rectangle
            bool collision = playerRect.intersects(dropItemRect);

            if (collision)
            {
                m_hp += 2;
                DropItem::rmdropItem(dropItem);
            }
            return collision;
        }

    return QGraphicsItem::collidesWithItem(other, mode);
}

int Player::type() const
{
    // 返回角色的类型
    return m_type;
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

void Player::setSpeed(qreal speed)
{
    // 设置角色的移动速度
    m_speed = speed;
}

void Player::setPos(qreal x, qreal y)
{
    // 设置角色的位置
    m_x = x;
    m_y = y;
}

void Player::setHP(int hp)
{
    // 设置角色的生命值
    m_hp = hp;
}

void Player::setAttack(int attack)
{
    // 设置角色的攻击力
    m_attack = attack;
}



void Player::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的按下,就将key值加入容器
        keys.append(event->key());
    if(!keyRespondTimer->isActive()) //如果定时器不在运行，就启动一下
        keyRespondTimer->start(10);
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的释放,就将key值从容器中删除
        keys.removeAll(event->key());
    if(keys.isEmpty()) //容器空了，关闭定时器
        keyRespondTimer->stop();
}

void Player::slotTimeOut()
{
    lifespan++;
    checkPlayerstate();
    qreal dx = 0;
    qreal dy = 0;
    foreach (int key, keys) {
        switch (key) {
            case Qt::Key_W:
                dy = -m_speed;  // 向上移动
                break;
            case Qt::Key_S:
                dy = m_speed;   // 向下移动
                break;
            case Qt::Key_A:
                dx = -m_speed;  // 向左移动
                break;
            case Qt::Key_D:
                dx = m_speed;   // 向右移动
                break;
            default:
                // 其他按键不做处理
                break;
        }

        // 更新角色的位置
        m_x += dx;
        m_y += dy;
        setPos(m_x, m_y);
    }
}

void Player::takeDamage(int dam)
{
    m_hp -= dam;
}









