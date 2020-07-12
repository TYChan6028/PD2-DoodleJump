#include "blackhole.h"

Blackhole::Blackhole(int x, int y)
{
    // set position
    setPos(x, y);
    QPixmap pic(":/pics/blackhole.png");
    setPixmap(pic.scaled(width, height));
    setZValue(40);
}

Blackhole::~Blackhole()
{
//    qDebug() << "blackhole dtor";
}
