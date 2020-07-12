#include "spring.h"

int Spring::width = 30;
int Spring::height = 30;

Spring::Spring(double x, double y)
{
    // set position
    setPos(x, y);
    QPixmap pic(":/pics/spring.png");
    setPixmap(pic.scaled(width, height));
    setZValue(45);
}

Spring::~Spring()
{
//    qDebug() << "spring dtor";
}
