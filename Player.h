

#ifndef PLAYER_H
#define PLAYER_H
#include "Animation.h"
#include "V2d.h"
#include "Mouse.h"
#include "Projectile.h"
#include "HudElements.h"
#include "Fx.h"
using namespace std;
class Player {
public:
    
    V2d pos, vel;
    SDL_Texture * tex;
    SDL_Rect rect;
    SDL_Rect collider[4];
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    vector<Animation*> animation;
    Animation * currentAnimation = nullptr;
    Animation * prevAnimation = nullptr;
    vector<WizardProjectile*> shots;
    vector<Heart> healthBar;
    int ps; // Player state
    enum PlayerStates{S_WALK, S_DIE};
    double speed = 400;
    double attackDelay = .20;
    double attackTimer = attackDelay; // counts down to allow next shot to be fired
    float hp;
    int maxhp;
    int damage = 2;   
    bool isAttacking = false;
    enum AnimationEnums{WALKUP, WALKDOWN, WALKRIGHT, DIE, ATTACKUP, ATTACKDOWN, ATTACKRIGHT};
    BloodFx bfx;
    Player();
     virtual ~Player();
     void update(Mouse&);
     void draw();
     friend class HudElements;
};

#endif /* PLAYER_H */

