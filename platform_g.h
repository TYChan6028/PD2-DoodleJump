#ifndef PLATFORM_G_H
#define PLATFORM_G_H

#include "platform.h"
#include "spring.h"
#include "pogoshoes.h"

class G_Platform: public Platform
{
    friend class Game;
public:
    G_Platform(int x, int y);
    virtual ~G_Platform();
public slots:
    virtual void onSteppedOn();
signals:
private:
};

#endif // PLATFORM_G_H
