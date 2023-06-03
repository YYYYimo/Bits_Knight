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

void Enemy::setType(int t)
{
    m_type = t;
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
    // 绘制血条
    int barWidth = 30;  // 血条宽度
    int barHeight = 5;  // 血条高度
    int barX = m_x + (width - barWidth) / 2;  // 血条的 x 坐标居中对齐
    int barY = m_y - barHeight - 5;  // 血条的 y 坐标位于怪物图像上方一定距离

    // 绘制血条的底色
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::gray);
    painter->drawRect(barX, barY, barWidth, barHeight);

    // 绘制实际血量的部分
    float healthPercentage = static_cast<float>(m_hp) / static_cast<float>(fullHp);
    int healthBarWidth = static_cast<int>(healthPercentage * barWidth);
    painter->setBrush(Qt::red);
    painter->drawRect(barX, barY, healthBarWidth, barHeight);

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

void Enemy::setdirect(int d)
{
    direct = d;
}

QPointF Enemy::getPlayerPos()
{
    QPointF point(play->m_x, play->m_y);
    return point;
}


void Enemy::rmenemy()
{
    updatetime->stop();
    lifespantime->stop();
    GameWindow::enemynum--;
    QSharedPointer<Enemy> ene = sharedFromThis();
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
    attack();
}

void Enemy::takeDamage(int dam)
{
    m_hp -= dam;
}

void Enemy::attack()
{
    if(collidesWithItem(play.data(), Qt::IntersectsItemBoundingRect))
    {
        play->takeDamage(m_attack);
    }
}

void Enemy::enemove()
{
    if (play)
    {
        if(m_type == demon)
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
        }
        else
        {
            qreal dx = 0;
            qreal dy = 0;
            if(direct == Right)
            {
                dx = m_speed;
                if(m_x + dx >= 1150)
                    direct = Left;
            }
            else if(direct == Down)
            {
                dy = m_speed;
                if(m_y + dy >= 1150)
                    direct = Up;
            }
            else if(direct == Left)
            {
                dx = -m_speed;
                if(m_x + dx <= 50)
                    direct = Right;
            }
            else
            {
                dy = -m_speed;
                if(m_y + dy <= 50)
                    direct = Down;
            }
            setPos(m_x + dx, m_y + dy);
        }
    }

}

void Enemy::slotTimeOut()
{
    if(this)
    {
        enemove();
        checkEnemystate();
    }
}

void Enemy::pauseAnimation()
{
    lifespantime->stop();
    updatetime->stop();
}

void Enemy::resumeAnimation()
{
    lifespantime->start();
    updatetime->start();
}









