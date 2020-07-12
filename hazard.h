#ifndef HAZARD_H
#define HAZARD_H

#include <QBrush>
#include "entity.h"

class Hazard: public Entity
{
    Q_OBJECT
    friend class Game;
public:
    Hazard();
    virtual ~Hazard();
    virtual const QString getType();
protected:
    static int totalHazCreated;
    static int width, height;
};

#endif // HAZARD_H
