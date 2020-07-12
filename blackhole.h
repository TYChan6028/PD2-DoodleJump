#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "hazard.h"

class Blackhole: public Hazard
{
    friend class Game;
public:
    Blackhole(int x, int y);
    virtual ~Blackhole();
};

#endif // BLACKHOLE_H
