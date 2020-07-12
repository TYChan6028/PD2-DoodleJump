#include "platform_b.h"
#include <QDebug>
#include <QGraphicsScene>

B_Platform::B_Platform(int x, int y)
{
    setPos(x, y);
    QPixmap pic(":/pics/b_platform.png");
    setPixmap(pic.scaled(width, height));
}

B_Platform::~B_Platform()
{
    //    qDebug() << "Bplatform dtor";
}

void B_Platform::onSteppedOn()
{
    emit breakPlat(listIdx, entityIdx);
}
