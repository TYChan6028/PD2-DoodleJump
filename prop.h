#ifndef PROP_H
#define PROP_H

#include "entity.h"

class Prop: public Entity
{
    Q_OBJECT
    friend class Game;
public:
    Prop();
    virtual ~Prop();
    virtual const QString getType();
protected:
    static int totalPropCreated;
};

#endif // PROP_H
