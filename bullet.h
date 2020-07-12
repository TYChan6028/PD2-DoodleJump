#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QList>
#include "monster.h"


class Bullet: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Bullet(const int& x, const int& y);
    ~Bullet();
    const static int width = 5, height = 10;
public slots:
    void move();
signals:
    void hitMonster(const int& listIdx, const int& entityIdx);
private:
    int X, Y;
    QTimer* timer;
};

#endif // BULLET_H
