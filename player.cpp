#include "player.h"
#include <QImage>
#include <QMovie>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QObject>
#include <QDebug>

Player::Player()
    : m_type(0), m_hp(0), m_attack(0), m_x(0), m_y(0), m_speed(0), m_movie(nullptr), lifespan(0)
{   //具体数值在对应玩家角色类中初始化
    coins = 0;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    keyRespondTimer = new QTimer(this);	//Create a timer object and connect signals and slots in the constructor
    connect(keyRespondTimer, &QTimer::timeout, this, &Player::slotTimeOut);
    keyRespondTimer->start(15);

    lifespantime = new QTimer(this);
    connect(lifespantime, &QTimer::timeout, this, &Player::updatePlayer);
    //lifespantime->start(1000);
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

bool Player::collidesWithItem(QGraphicsItem *other, Qt::ItemSelectionMode mode)
{
    Q_UNUSED(mode)
    return other->type() == DropItem::Type;
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

void Player::updatePlayer()
{
        qDebug() << "qu";
    lifespan++;
    attack();
}

void Player::takeDamage(int dam)
{
    m_hp -= dam;
}

void Player::attack()
{
    qDebug() << "qu";
    if(lifespan != 0 && lifespan % 3 == 0)//设置发射子弹时间间隔
    {
        Bullet* bull = new Bullet(m_type, m_x, m_y);
        scene()->addItem(bull);
    }
}









