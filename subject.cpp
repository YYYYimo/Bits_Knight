#include "subject.h"
#include "bullet.h"
#include <algorithm>

QSharedPointer<Player> subject::play_p = nullptr;
QVector<QSharedPointer<Enemy>> subject::enevec;
QVector<QSharedPointer<Bullet>> subject::bullvec;
QVector<QSharedPointer<DropItem>> subject::dropvec;
int subject::coins = 0;

 subject::subject()
 {
     play_p = nullptr;
 }

 void subject::addenemyPointer(QSharedPointer<Enemy> e)
 {
     enevec.push_back(e);
 }

 void subject::addplayerPointer(QSharedPointer<Player> p)
 {
     play_p = p;
 }

 void subject::removeenemyPointer(QSharedPointer<Enemy> e)
 {
     QVector<QSharedPointer<Enemy>>::Iterator it = std::find(enevec.begin(), enevec.end(), e);
     if(it != enevec.end())
     {
         enevec.erase(it);
     }
 }

 void subject::addbullPointer(QSharedPointer<Bullet> e)
 {
     bullvec.push_back(e);
 }

 void subject::removebullPointer(QSharedPointer<Bullet> e)
 {
    QVector<QSharedPointer<Bullet>>::Iterator it = std::find(bullvec.begin(), bullvec.end(), e);
    if(it != bullvec.end())
    {
        bullvec.erase(it);
    }
 }


void subject::removedropPointer(QSharedPointer<DropItem> e)
{
    QVector<QSharedPointer<DropItem>>::Iterator it = std::find(dropvec.begin(), dropvec.end(), e);
    if(it != dropvec.end())
    {
        dropvec.erase(it);
    }
}

void subject::adddropPointer(QSharedPointer<DropItem> e)
{
    dropvec.push_back(e);
}



