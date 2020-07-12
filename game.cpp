#include "game.h"

Game::Game():
    sceneWidth(600), sceneHeight(900), platNum(16)
{
    // create a scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    // visualize scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(sceneWidth, sceneHeight);

    // create the player inside scene
    player = new Player(sceneWidth/2-Player::width/2, sceneHeight-Player::height);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add player to scene
    scene->addItem(player);

    // add platform
    Platform* initPlat = platGenerator(sceneWidth/2-Platform::width/2, sceneHeight);
    platList.push_back(initPlat);
    entityList.push_back(initPlat);
    scene->addItem(initPlat);
    addPropToScene(initPlat);

    for (int i=0; i<platNum; i++) {
        int x = QRandomGenerator::global()->bounded(0, sceneWidth-Platform::width);
        int y = QRandomGenerator::global()->bounded(sceneHeight/2, sceneHeight);
        Platform* ptr = platGenerator(x, y);
        platList.push_back(ptr);
        entityList.push_back(ptr);
        scene->addItem(ptr);
        addPropToScene(ptr);
    }
    for (int i=platNum; i<platNum*2; i++) {
        int x = QRandomGenerator::global()->bounded(0, sceneWidth-Platform::width);
        int y = QRandomGenerator::global()->bounded(0, sceneHeight/2);
        Platform* ptr = platGenerator(x, y);
        platList.push_back(ptr);
        entityList.push_back(ptr);
        scene->addItem(ptr);
        addPropToScene(ptr);
    }

    // connect player
    connect(player, &Player::died, this, &Game::playerDied);
    connect(player, &Player::positChanged, this, &Game::checkSteppedPlat);
    connect(player, &Player::positChanged, this, &Game::checkSquashedMonster);
    connect(player, &Player::positChanged, this, &Game::checkSteppedProp);
    connect(player, &Player::moved, this, &Game::checkHazard);
    connect(player, &Player::killedMonster, this, &Game::removeThisItem);
    connect(player, &Player::crossUpperBound, this, &Game::scrollScene);
    connect(player, &Player::updateScene, this, &Game::generateScene);

    // connect platform
    for (int i=0; i<platList.size(); ++i) {
        connect(platList[i], &Platform::bounceValid, player, &Player::resetBounce);
        connect(platList[i], &Platform::breakPlat, this, &Game::deletePlat);
        connect(platList[i], &Platform::deleteGPlatform, this, &Game::removePropFromScene);
        connect(platList[i], &Entity::itemOffBounds, this, &Game::removeThisItem);
    }

    // start bouncing
    player->bounce();
}

void Game::playerDied()
{
    player->disconnect(player->timer, nullptr, player, nullptr);
    for (int i = 0; i < platList.size(); ++i) {
        delete platList[i];
        platList.remove(i);
    }
    for (int i = 0; i < hazList.size(); ++i) {
        delete hazList[i];
        hazList.remove(i);
    }
    int finalScore = player->score;
    delete player;
    player = nullptr;
    delete scene;
    scene = nullptr;
    this->close();
    emit gameOver(finalScore);
    return;
}

void Game::checkHazard()
{
    for (int i=0; i<hazList.size(); i++) {

        if (hazList[i]->collidesWithItem(player, Qt::IntersectsItemBoundingRect)
                && player->propStatus == player->Prop::none) {
//            qDebug() << "you died";
            playerDied();
            return;
        }
    }
}

void Game::checkSquashedMonster()
{
    for (int i=0; i<hazList.size(); i++) {
        if (hazList[i]->collidesWithItem(player, Qt::IntersectsItemBoundingRect)
                && typeid(*(hazList[i])) == typeid(Monster)) {
            player->resetBounce();
            removeThisItem(hazList[i]->listIdx, hazList[i]->entityIdx);
            break;
//            qDebug() << "monster squashed" << hazList[i]->entityIdx;
        }
    }
}

void Game::checkSteppedPlat()
{
    for (int i=0; i<platList.size(); i++) {
        if (platList[i]->collidesWithItem(player, Qt::IntersectsItemBoundingRect)
                && player->y()+player->height > platList[i]->y()
                && player->y()+player->height < platList[i]->y()+platList[i]->height) {
            platList[i]->onSteppedOn();
        }
    }
}

void Game::checkSteppedProp()
{
    for (int i=0; i<propList.size(); i++) {
        if (propList[i]->collidesWithItem(player, Qt::IntersectsItemBoundingRect)
                && typeid(*(propList[i])) == typeid(Spring)) {
            player->bounceSpring();
            removePropFromScene(propList[i]);
            break;
//            qDebug() << "monster squashed" << hazList[i]->entityIdx;
        }
        else if (propList[i]->collidesWithItem(player, Qt::IntersectsItemBoundingRect)
                 && typeid(*(propList[i])) == typeid(PogoShoes)) {
            player->wearPogoShoes();
            removePropFromScene(propList[i]);
            break;
        }
    }
}

void Game::deletePlat(const int& listIdx, const int& entityIdx)
{
    for (int i=0; i<platList.size(); i++) {
        if (platList[i]->listIdx == listIdx) {
            scene->removeItem(platList[i]);
            delete platList[i];
            platList.remove(i);
            break;
        }
    }
    for (int i=0; i<entityList.size(); i++) {
        if (entityList[i]->entityIdx == entityIdx) {
            entityList.remove(i);
            break;
        }
    }
}

void Game::scrollScene(const double& dy)
{
    for (int i=0; i<entityList.size(); i++) {
        entityList[i]->scrollDown(dy);
    }
}

void Game::removeThisItem(const int &listIdx, const int &entityIdx)
{
    for (int i=0; i<entityList.size(); i++) {
        if (entityList[i]->entityIdx == entityIdx) {
            QString classType = entityList[i]->getType();
            // remove object from [classList]
            if (classType == "Platform") {
                for (int j=0; j<platList.size(); j++) {
                    if (platList[j]->listIdx == listIdx) {
                        platList.remove(j);
                        break;
                    }
                }
            }
            else if (classType == "Hazard") {
                for (int j=0; j<hazList.size(); j++) {
                    if (hazList[j]->listIdx == listIdx) {
                        hazList.remove(j);
                        break;
                    }
                }
            }
            // remove object from [entityList]
            scene->removeItem(entityList[i]);
            delete entityList[i];
            entityList.remove(i);
            break;
        }
    }
}

void Game::generateScene()
{
    // generate platforms
    for (int i=0; i<platNum; i++) {
        int x = QRandomGenerator::global()->bounded(0, sceneWidth-Platform::width);
        int y;
        if (i < platNum/2) {
            y = QRandomGenerator::global()->bounded(int(player->y()-sceneHeight*1.5),
                                                        int(player->y()-sceneHeight));}
        else {
            y = QRandomGenerator::global()->bounded(int(player->y()-sceneHeight*2),
                                                        int(player->y()-sceneHeight*1.5));}
        Platform* ptr = platGenerator(x, y);
        platList.push_back(ptr);
        entityList.push_back(ptr);
        scene->addItem(ptr);
        addPropToScene(ptr);
        connect(ptr, &Platform::bounceValid, player, &Player::resetBounce);
        connect(ptr, &Platform::breakPlat, this, &Game::deletePlat);
        connect(ptr, &Platform::deleteGPlatform, this, &Game::removePropFromScene);
        connect(ptr, &Entity::itemOffBounds, this, &Game::removeThisItem);
    }

    // generate hazards
    int seed = QRandomGenerator::global()->bounded(0, 100);
    int x = QRandomGenerator::global()->bounded(0, sceneWidth-Hazard::width);
//    int y = QRandomGenerator::global()->bounded(0, 1);
    int y = QRandomGenerator::global()->bounded(int(player->y()-sceneHeight*2),
                                                int(player->y()-sceneHeight*2+1));
//    y = 0;
    if (seed > 80 && player->pageNum > 2) { // monster
        Monster* monster = new Monster(x, y);
        scene->addItem(monster);
        hazList.push_back(monster);
        entityList.push_back(monster);
        connect(monster, &Entity::itemOffBounds, this, &Game::removeThisItem);
    }
    else if (seed < 10 && player->pageNum > 2) { // blackhole
        Blackhole* blackhole = new Blackhole(x, y);
        scene->addItem(blackhole);
        hazList.push_back(blackhole);
        entityList.push_back(blackhole);
        connect(blackhole, &Entity::itemOffBounds, this, &Game::removeThisItem);
    }
}

void Game::addPropToScene(Platform* ptr)
{
    if (ptr->getProp() != nullptr) {
        Prop* prop = ptr->getProp();
        propList.push_back(prop);
        entityList.push_back(prop);
        scene->addItem(prop);
    }
}

void Game::removePropFromScene(Prop* prop)
{
    for (int i=0; i<propList.size(); i++) {
        if (propList[i] == prop) {
            propList.remove(i);
            break;
        }
    }
    for (int i=0; i<entityList.size(); i++) {
        if (entityList[i] == prop) {
            scene->removeItem(prop);
            entityList.remove(i);
            break;
        }
    }
}
