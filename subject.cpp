#include "suject.h"
#include "bullet.h"
#include <algorithm>
 subject::subject()
 {
     play_p = nullptr;
 }

 void subject::addenemyPointer(Enemy *e)
 {
     enevec.push_back(e);
 }

 void subject::addplayerPointer(Player *p)
 {
     play_p = p;
 }

 void subject::removeenemyPointer(Enemy *e)
 {
     QVector<Enemy*>::Iterator it = std::find(enevec.begin(), enevec.end(), e);
     if(it != enevec.end())
     {
         enevec.erase(it);
     }
 }
