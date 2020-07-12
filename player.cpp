#include "player.h"
#include <QDebug>

int Player::width = 80;
int Player::height = 80;

Player::Player(int x, int y):
    dt(0.01), // time increment
    y0(800), // initial y position
    v0(1000), // initial velocity
    g(1500), // gravity constant
    upperBound(300), // player bounce higher than this, scroll scene
    boostBounceHeight(1750), // jump height when using jumping props
    pogoShoesDuration(5)
{
    // set player attributes
    this->setPos(x, y);
    QPixmap pic(":/pics/doodle.png");
    setPixmap(pic.scaled(width, height));
    this->setZValue(100);
    connect(this, &Player::killedMonster, this, &Player::addKillBonus);

    // set move timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Player::add_t);
    connect(timer, &QTimer::timeout, this, &Player::bounce);
    connect(timer, &QTimer::timeout, this, &Player::moveTimerEvent);
    timer->start(int(dt*1000));
}

Player::~Player()
{
    delete timer;
}

void Player::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_A:
    case Qt::Key_Left:
        isMovingLeft = true;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        isMovingRight = true;
        break;
    case Qt::Key_W:
    case Qt::Key_Up:
        isSpawningBullet = true;
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_A:
    case Qt::Key_Left:
        isMovingLeft = false;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        isMovingRight = false;
        break;
    case Qt::Key_W:
    case Qt::Key_Up:
        isSpawningBullet = false;
        break;
    }
}

void Player::bounce()
{
    // update player position
    v = v0 - g*t;
    dy = v*dt;
    this->setY(y() - dy);

    // check under player for objects
    ascending = (v > 0) ? true : false;
    if (!ascending) {
        positChanged();
    };

    // check hazards nearby
    emit moved();

    // death condition here
    if (y() > 900) {
        disconnect(timer, nullptr, this, nullptr);
        emit died();
    }

    // load new scene
    totalDistTraveled += dy;
    if (totalDistTraveled > 900*pageNum) {
        score = pageNum;
        emit currentScore(score);
        pageNum++;
        emit updateScene();
    }
    // player bounced too high, have to scroll scene
    if (y() < upperBound) {
        setY(upperBound);
        emit crossUpperBound(dy);
    }
}

void Player::add_t()
{
    t += dt;
}

void Player::pausePlayer()
{
    if (gameStatus == running) {
        disconnect(timer, nullptr, this, nullptr);
        gameStatus = paused;
    }
    else if (gameStatus == paused) {
        connect(timer, &QTimer::timeout, this, &Player::add_t);
        connect(timer, &QTimer::timeout, this, &Player::bounce);
        connect(timer, &QTimer::timeout, this, &Player::moveTimerEvent);
        emit resumeGame();
        gameStatus = running;
    }
}

void Player::moveTimerEvent()
{
    if (isMovingLeft) {
        setX(x()-5);
        if (x() < -width) setX(600);
        moved();
    }
    else if (isMovingRight) {
        setX(x()+5);
        if (x() > 600) setX(0);
        moved();
    }
    else if (isSpawningBullet) {
        bullet = new Bullet(x()+width/2-Bullet::width/2, y()-Bullet::height);
        connect(bullet, &Bullet::hitMonster, this, &Player::killedMonster);
        scene()->addItem(bullet);
    }
}

void Player::resetBounce()
{
//    qDebug() << "reset bounce called";
    t = 0;
    v0 = 1000;
    if (propStatus == pogoShoes) wearPogoShoes();
    if (propStatus == spring) propStatus = none;
}

void Player::bounceSpring()
{
    t = 0;
    v0 = boostBounceHeight;
    propStatus = spring;
}

void Player::wearPogoShoes()
{
    if (pogoShoesUsage < pogoShoesDuration) {
        propStatus = pogoShoes;
        pogoShoesUsage++;
    }
    else {
        propStatus = none;
        pogoShoesUsage = 0;
        return;
    }
    t = 0;
    v0 = boostBounceHeight;
}

void Player::addKillBonus()
{
    score += 3;
}
