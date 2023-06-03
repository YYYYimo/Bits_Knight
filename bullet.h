#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QString>
#include <QTimer>
#include <QObject>
#include <QSharedPointer>
#include <QEnableSharedFromThis>
#include "gamewindow.h"
#include "enemy.h"
#include "player.h"
#include "subject.h"
enum bullettype {angel, elf, wizzard};
class Bullet : public QGraphicsItem, public subject, public QObject, public QEnableSharedFromThis<Bullet>
{
public:
    Bullet(int t, qreal x, qreal y, QSharedPointer<Player> pl);
    Bullet(Bullet*){} //
    ~Bullet(){}
    
    QRectF boundingRect() const override;
    void setPos(qreal x, qreal y);
    void advance();
    void attack();
    void bullmove();
    void rmbullet();

private:
    int m_type;
    int m_speed;
    int m_atk;
    int width;
    int height;
    QString imgpath;
    qreal m_x;
    qreal m_y;
    QSharedPointer<Enemy> target;
    QSharedPointer<Player> play;
    QTimer* updatetime;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
private slots:
    void slotTimeOut();
};

#endif // BULLET_H
