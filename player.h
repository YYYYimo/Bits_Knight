#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QGraphicsItem>
#include "gamewindow.h"
#include "bullet.h"

class Player : public QGraphicsObject
{
    Q_OBJECT
    friend class GameWindow;
    friend class Bullet;
public:
    Player();

    QRectF boundingRect() const override;
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
    int type() const override;

    void setMovie(const QString& path);
    void setSpeed(qreal speed);
    void setPos(qreal x, qreal y);
    void setHP(int hp);
    void setAttack(int attack);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);
    void takeDamage(int dam);
    void attack();

    void advance(); //to do: 设计人物在每一帧刷新后的逻辑

    QList<int> keys;
private:
    int m_type;
    int m_hp;
    int m_attack;
    int width;
    int height;
    int lifespan;
    qreal m_x;
    qreal m_y;
    qreal m_speed;
    QMovie* m_movie;
    QTimer* keyRespondTimer;
private slots:
    void slotTimeOut();
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};


#endif // PLAYER_H
