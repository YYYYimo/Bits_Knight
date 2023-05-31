#ifndef SUBJECT_H
#define SUBJECT_H
#include <QVector>
#include <QSharedPointer>
class Player;
class Enemy;
class Bullet;
class DropItem;
class subject
{
public:
    subject();
    static void addplayerPointer(QSharedPointer<Player> p);
    static void addenemyPointer(QSharedPointer<Enemy> e);
    static void removeenemyPointer(QSharedPointer<Enemy> e);
    static void addbullPointer(QSharedPointer<Bullet> e);
    static void removebullPointer(QSharedPointer<Bullet> e);
    static void adddropPointer(QSharedPointer<DropItem> e);
    static void removedropPointer(QSharedPointer<DropItem> e);


    static QSharedPointer<Player> play_p;//需要访问
    static QVector<QSharedPointer<Enemy>> enevec;
    static QVector<QSharedPointer<Bullet>> bullvec;
    static QVector<QSharedPointer<DropItem>> dropvec;
    static int coins;
};

#endif // SUJECTBULLET_H
