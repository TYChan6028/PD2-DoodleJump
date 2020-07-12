#include "platform.h"

int Platform::totalPlatCreated = 0;
int Platform::width = 100;
int Platform::height = 20;

Platform::Platform()
{
    // set Platform ID
    listIdx = totalPlatCreated;
    totalPlatCreated++;
    setZValue(50);
}

Platform::~Platform()
{
//    qDebug() << "platform dtor";
}

const QString Platform::getType()
{
    return metaObject()->className();
}

Prop *Platform::getProp()
{
    return prop;
}
