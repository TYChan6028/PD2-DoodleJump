#include "monster.h"

Monster::Monster(int x, int y)
{
    // set position
    setPos(x, y);
    QPixmap pic(":/pics/winny_the_poo.png");
    setPixmap(pic.scaled(width, height));
    setZValue(60);
}

Monster::~Monster()
{
//    qDebug() << "monster dtor";
}
