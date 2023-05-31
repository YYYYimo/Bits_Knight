#ifndef ENEMYZOMBIE_H
#define ENEMYZOMBIE_H
#include "enemy.h"
class enemyzombie : public Enemy
{
public:
    enemyzombie(QSharedPointer<Player> pl);
    ~enemyzombie(){}
};

#endif // ENEMYZOMBIE_H
