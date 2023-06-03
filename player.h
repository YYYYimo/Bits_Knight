#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QGraphicsItem>
#include <QSharedPointer>
#include <QEnableSharedFromThis>
#include <QJsonObject>
#include "gamewindow.h"
#include "bullet.h"
#include "subject.h"
class Player : public QGraphicsObject, public subject, public QEnableSharedFromThis<Player>
{
    Q_OBJECT
    friend class GameWindow;
    friend class Bullet;
public:
    Player();
    QRectF boundingRect() const override;
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
    void pickupItem();
    void pauseAnimation();
    void resumeAnimation();
    void read(const QJsonObject &json);
    void write(QJsonObject &json);

    qreal m_x;
    qreal m_y;
    int m_hp;
    int exp;
    int m_attack;
protected:
    QList<int> keys;

    qreal m_speed;
    int m_type;
    int width;
    int height;
    int lifespan;
    QTimer* keyRespondTimer;
    QTimer* lifespantime;
    QMovie* m_movie;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
private slots:
    void slotTimeOut();
    void updatePlayer();

signals:
    void keyPressed(QKeyEvent *event);

};


#endif // PLAYER_H
