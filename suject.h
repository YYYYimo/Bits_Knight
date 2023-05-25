#ifndef SUJECT_H
#define SUJECT_H
#include <QVector>
class Player;
class Enemy;
class subject
{
public:
    subject();
    void addplayerPointer(Player* p);
    void addenemyPointer(Enemy* e);
    void removeenemyPointer(Enemy* e);

    Player* play_p;
    QVector<Enemy*> enevec;
};

#endif // SUJECTBULLET_H
