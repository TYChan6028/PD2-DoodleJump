#include "pogoshoes.h"

int PogoShoes::width = 50;
int PogoShoes::height = 50;

PogoShoes::PogoShoes(double X, double Y)
{
    // set position
    setPos(X, Y);
    QPixmap pic(":/pics/astroboots.png");
    setPixmap(pic.scaled(width, height));
    setZValue(45);
}

PogoShoes::~PogoShoes()
{
//    qDebug() << "pogoshoes dtor";
}
