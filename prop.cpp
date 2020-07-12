#include "prop.h"

int Prop::totalPropCreated = 0;

Prop::Prop()
{
    // set Prop ID
    listIdx = totalPropCreated;
    totalPropCreated++;
}

Prop::~Prop()
{
//    qDebug() << "prop dtor";
}

const QString Prop::getType()
{
    return metaObject()->className();
}
