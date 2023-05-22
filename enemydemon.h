#ifndef ENEMYDEMON_H
#define ENEMYDEMON_H
#include "enemy.h"
#include "player.h"
#include <QMovie>

class enemydemon : public Enemy
{
public:
    enemydemon(Player* pl);
    ~enemydemon(){}
};

#endif // ENEMYDEMON_H
