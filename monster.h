#ifndef MONSTER_H
#define MONSTER_H

#include "hazard.h"

class Monster: public Hazard
{
    friend class Game;
public:
    Monster(int x, int y);
    virtual ~Monster();
};

#endif // MONSTER_H
