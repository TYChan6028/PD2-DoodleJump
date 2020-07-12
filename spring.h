#ifndef SPRING_H
#define SPRING_H

#include "prop.h"

class Spring: public Prop
{
    friend class Game;
public:
    Spring(double x, double y);
    virtual ~Spring();
    static int width, height;
};

#endif // SPRING_H
