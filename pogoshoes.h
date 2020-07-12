#ifndef POGOSHOES_H
#define POGOSHOES_H

#include "prop.h"

class PogoShoes: public Prop
{
    friend class Game;
public:
    PogoShoes(double X, double Y);
    virtual ~PogoShoes();
    static int width, height;
};

#endif // POGOSHOES_H
