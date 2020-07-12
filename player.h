#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include "bullet.h"


class Player: public QObject, public QGraphicsPixmapItem
{
    friend class Game;
    Q_OBJECT
public:
    Player(int x, int y);
    ~Player();
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void bounce();
    void add_t();
public slots:
    void pausePlayer();
    void moveTimerEvent();
    void resetBounce();
    void bounceSpring();
    void wearPogoShoes();
    void addKillBonus();
signals:
    void resumeGame();
    void died();
    void positChanged();
    void moved();
    void crossUpperBound(const double& dy);
    void killedMonster(const int& listIdx, const int& entityIdx);
    void updateScene();
    void currentScore(int score);
private:
    static int width, height;
    double t = 0;
    double dt;
    int ascending = true;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isSpawningBullet = false;
    int y0;
    double dy = 0;
    int v0;
    double v = 0;
    int g;
    double totalDistTraveled = 0;
    int pageNum = 0;
    int upperBound;
    QTimer* timer = nullptr;
    Bullet* bullet = nullptr;
    enum Status {paused=0, running};
    int gameStatus = running;
    enum Prop {none=0, spring, pogoShoes};
    Prop propStatus = none;
    int boostBounceHeight;
    int pogoShoesDuration;
    int pogoShoesUsage = 0;
    int score = 0;
};

#endif // PLAYER_H
