#ifndef PLATFORM_B_H
#define PLATFORM_B_H

#include "platform.h"

class B_Platform: public Platform
{
    friend class Game;
public:
    B_Platform(int x, int y);
    virtual ~B_Platform();
public slots:
    virtual void onSteppedOn();
};

#endif // PLATFORM_B_H
