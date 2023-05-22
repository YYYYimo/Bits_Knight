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
    bool collidesWithItem(QGraphicsItem *other, Qt::ItemSelectionMode mode);

    void setMovie(const QString& path);
    void setSpeed(qreal speed);
    void setPos(qreal x, qreal y);
    void setHP(int hp);
    void setAttack(int attack);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);
    void checkPlayerState();
    void takeDamage(int dam);
    void attack();


    qreal m_x;
    qreal m_y;
        int m_hp;
protected:
    QList<int> keys;
    int m_type;

    int m_attack;
    int width;
    int height;
    int lifespan;
    int coins;

    qreal m_speed;
    QTimer* keyRespondTimer;
    QTimer* lifespantime;
    QMovie* m_movie;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
private slots:
    void slotTimeOut();
    void updatePlayer();

};


#endif // PLAYER_H
