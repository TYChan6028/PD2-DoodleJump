#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>
#include <QDebug>

class Entity: public QObject, public /*QGraphicsRectItem,*/ QGraphicsPixmapItem
{
    Q_OBJECT
    friend class Game;
    friend class Bullet;
public:
    Entity();
    virtual ~Entity();
    virtual const QString getType() = 0;
public slots:
    virtual void scrollDown(const double& dy);
signals:
    void itemOffBounds(const int& listIdx, const int& entityIdx);
protected:
    static int totalEntitiesCreated;
    int entityIdx;
    int listIdx;
};

#endif // ENTITY_H
