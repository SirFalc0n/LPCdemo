

#ifndef ENEMY_H
#define ENEMY_H
#include "globals.h"
#include "V2d.h"
#include <vector>
#include "Animation.h"

#include "Player.h"
using namespace std;

class Enemy {
public:
    SDL_Texture * tex;
    SDL_Rect rect;
    SDL_RendererFlip flip;
    vector<Animation*> animation;
    Animation * currentAnimation = nullptr;
    V2d pos, vel;
    float speed = 200;
    Enemy();
    virtual ~Enemy();
    virtual void update();
    virtual void draw();
};

class WolfWarrior : public Enemy {
private:

    WolfWarrior() {
    }
public:
    V2d p1, p2, target; // patrol points
    int ws = 0;

    enum AnimationEnums {
        WALKUP, WALKDOWN, WALKRIGHT, DIE, ATTACKUP, ATTACKDOWN, ATTACKRIGHT, REST
    };
    double searchRadius; // follows the player if the player is this close (squared)
    double attackRadius; // attacks if the player is this close (squared)
    double attackTime; // sets the time in attack mode
    double attackTimer = attackTime; //a timer that counts down
    double restTime; // // time spent resting after an attack
    double restTimer = restTime; // count down timer
    WolfWarrior(V2d p1, V2d p2);
    ~WolfWarrior();
    void update(Player&);

};



#endif /* ENEMY_H */

