

#ifndef LEVEL2_H
#define LEVEL2_H
#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "Tile.h"

class Level2 : public State{
public:
    vector<Tile*> tiles;
    Player player;

    WolfWarrior * wolf;
    Level2();
    virtual ~Level2();
    void enter();
    void update();
    void checkCollision();
    friend class Enemy;
};

#endif /* LEVEL2_H */

