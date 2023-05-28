#include "enemy.h"
#include "dropitem.h"
#include "gamewindow.h"
#include <QPixmap>
#include <QMovie>
#include <QtMath>
#include <QDebug>
#include <QList>
#define PI 3.1415926
Enemy::Enemy()
 : m_type(0), m_hp(0), m_attack(0), m_x(0), m_y(0), m_speed(0), m_movie(nullptr)
{
    QString imgpath = "://resource/gif/small_demon_run.gif";
    m_movie = new QMovie(imgpath);
    m_movie->start();

    lifespan = 0;
    lifespantime = new QTimer(this);
    connect(lifespantime, &QTimer::timeout, this, &Enemy::updateEnemy);
    lifespantime->start(1000);

    updatetime = new QTimer(this);
    connect(updatetime, &QTimer::timeout, this, &Enemy::slotTimeOut);
    updatetime->start(15);

}

Enemy::~Enemy()
{

}

QRectF Enemy::boundingRect() const
{
    return QRectF(m_x, m_y, width, height);
}

void Enemy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image = m_movie->currentImage();
    painter->drawImage(QRectF(m_x, m_y, width, height), image);
    update();
}

QPainterPath Enemy::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}


void Enemy::setMovie(const QString& path)
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

QPointF Enemy::getPlayerPos()
{
    QPointF point(play->m_x, play->m_y);
    return point;
}

void Enemy::enemove()
{
    if (play)
    {
        qreal dx = play->m_x - m_x;
        qreal dy = play->m_y - m_y;
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

void Enemy::rmenemy()
{
    lifespantime->stop();
    QSharedPointer<Enemy> ene = QSharedPointer<Enemy>::create(this);
    qreal lsp = lifespan;
    qreal x = m_x, y = m_y;
    int type = m_type;
    if(lsp < 120)
    {
        QSharedPointer<DropItem> dropcoin = QSharedPointer<DropItem>(new DropItem(coin, x, y, play));
        adddropPointer(dropcoin);
        scene()->addItem(dropcoin.data());
    }
    else
    {
        QSharedPointer<DropItem> dropcoin = QSharedPointer<DropItem>(new DropItem(coin, x, y, play));
        QSharedPointer<DropItem> dropitem = QSharedPointer<DropItem>(new DropItem(type, x + 5, y + 5, play));
        scene()->addItem(dropcoin.data());
        scene()->addItem(dropitem.data());
    }
    removeenemyPointer(ene);
    scene()->removeItem(this);
}

void Enemy::uplevel()
{
    //to do
}

void Enemy::checkEnemystate()
{
    if(m_hp <= 0)
        rmenemy();
    else
    {
        if(lifespan >= 60)
            uplevel();
    }
}

void Enemy::updateEnemy()
{
    lifespan++;
    checkEnemystate();
    attack();
}

void Enemy::takeDamage(int dam)
{
    m_hp -= dam;
}

void Enemy::attack()
{
    //QList<QGraphicsItem*> collisions = collidingItems();
    if(collidesWithItem(play.data(), Qt::IntersectsItemBoundingRect))
    {
        play->takeDamage(m_attack);
    }
}

void Enemy::slotTimeOut()
{
    if(this)
        enemove();
}







