#ifndef GAME_H
#define GAME_H
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include "player.h"
#include "platgenerator.h"
#include "prop.h"
#include "spring.h"
#include "hazard.h"
#include "monster.h"
#include "blackhole.h"
#include "bullet.h"


class Game: public QGraphicsView
{
    Q_OBJECT
    friend class MainWindow;
    friend class Bullet;
public:
    Game();
public slots:
    void playerDied();
    void checkHazard();
    void checkSquashedMonster();
    void checkSteppedPlat();
    void checkSteppedProp();
    void deletePlat(const int& listIdx, const int& entityIdx);
    void scrollScene(const double& dy);
    void removeThisItem(const int& listIdx, const int& entityIdx);
    void generateScene();
    void addPropToScene(Platform* ptr);
    void removePropFromScene(Prop* prop);
signals:
    void gameOver(int score);
private:
    QGraphicsScene *scene;
    Player* player;
    int sceneWidth;
    int sceneHeight;
    int platNum;
    QVector<Entity*> entityList;
    QVector<Platform*> platList;
    QVector<Prop*> propList;
    QVector<Hazard*> hazList;
};

#endif // GAME_H
