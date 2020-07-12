#include "bullet.h"
#include <QBrush>
#include <QGraphicsScene>

Bullet::Bullet(const int& x, const int& y):
    X(x), Y(y), timer(nullptr)
{
    setRect(0, 0, width, height);
    setPos(x, y);
    setBrush(QBrush(Qt::green));

    // connect timer to bullet
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50);
}

Bullet::~Bullet()
{
//    qDebug() << "bullet dtor";
}

void Bullet::move()
{
    // check collision with enemy
    QList<QGraphicsItem*> collidedItems = collidingItems(Qt::IntersectsItemBoundingRect);
    for (int i=0; i<collidedItems.size(); ++i) {
        if (typeid(*(collidedItems[i])) == typeid(Monster)) {
            Monster* ptr = dynamic_cast<Monster*>(collidedItems[i]);
            // delete this and monster
            emit hitMonster(ptr->listIdx, ptr->entityIdx);
            scene()->removeItem(this);
            delete this;
//            qDebug() << "killed monster";
            return;
        }
    };

    // no collision, move forward
    setY(y()-50);
    if (y() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
