#include "entity.h"

int Entity::totalEntitiesCreated = 0;

Entity::Entity()
{
    // set Entity ID
    entityIdx = totalEntitiesCreated;
    totalEntitiesCreated++;
}

Entity::~Entity()
{
//    qDebug() << "entity dtor";
}

void Entity::scrollDown(const double& dy)
{
    setY(y()+ dy);
    if (y() > 900) emit itemOffBounds(listIdx, entityIdx);
}
