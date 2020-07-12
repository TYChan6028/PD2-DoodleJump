#ifndef PLATFORM_H
#define PLATFORM_H

#include "entity.h"
#include "prop.h"

class Platform: public Entity
{
    Q_OBJECT
    friend class Game;
public:
    Platform();
    virtual ~Platform();
    virtual const QString getType();
    virtual Prop* getProp();
public slots:
    virtual void onSteppedOn() = 0;
signals:
    void sendPropPtr(Prop* ptr);
    void bounceValid();
    void breakPlat(const int& listIdx, const int& entityIdx);
    void deleteGPlatform(Prop* prop);
protected:
    static int totalPlatCreated;
    static int width, height;
    Prop* prop = nullptr;
};

#endif // PLATFORM_H
