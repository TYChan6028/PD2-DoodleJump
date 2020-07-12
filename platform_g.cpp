#include "platform_g.h"
#include <QRandomGenerator>

G_Platform::G_Platform(int X, int Y)
{
    setPos(X, Y);
    QPixmap pic(":/pics/g_platform.png");
    setPixmap(pic.scaled(width, height));

    // random generate props
    int seed = QRandomGenerator::global()->bounded(0, 100);
    if (seed < 10) {
        prop = new Spring(x()+width/2-Spring::width/2, y()-Spring::height);
    }
    else if (seed > 97) {
        prop = new PogoShoes(x()+width/2-PogoShoes::width/2, y()-PogoShoes::height);
    }
}

G_Platform::~G_Platform()
{
    emit deleteGPlatform(prop);
    delete prop;
//    qDebug() << "Gplatform dtor";
}

void G_Platform::onSteppedOn()
{
    emit bounceValid();
}
