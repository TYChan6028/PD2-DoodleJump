#include "platgenerator.h"
#define GOOD_PLAT 0
#define BAD_PLAT 1
#include <QDebug>

Platform* platGenerator(int x, int y) {
    Platform* ptr = nullptr;
    int platformType = QRandomGenerator::global()->bounded(0, 100) > 80;
    switch (platformType) {
    case GOOD_PLAT:
        ptr = new G_Platform(x, y);
//        qDebug() << "good platform created";
        break;
    case BAD_PLAT:
        ptr = new B_Platform(x, y);
//        qDebug() << "bad platform created";
        break;
    }
    return ptr;
}
