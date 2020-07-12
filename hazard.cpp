#include "hazard.h"

int Hazard::totalHazCreated = 0;
int Hazard::width = 120;
int Hazard::height = 120;

Hazard::Hazard()
{
    // set Hazard ID
    listIdx = totalHazCreated;
    totalHazCreated++;
}

Hazard::~Hazard()
{
//    qDebug() << "monster dtor";
}

const QString Hazard::getType()
{
    return metaObject()->className();
}
