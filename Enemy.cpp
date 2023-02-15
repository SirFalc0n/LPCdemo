
#include "Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::update() {
}

void Enemy::draw() {
    //    cout << "enemey rect: " << rect.x << "  " << rect.y << endl;

    SDL_RenderCopyEx(ren, tex, &currentAnimation->rect, &rect, NULL, 0, flip);
}

WolfWarrior::WolfWarrior(V2d p1, V2d p2) : p1{p1}, p2{p2}
{
    searchRadius = 125000; //squared
    attackRadius = 25000; // also squared
    attackTime = .7; // sets the time in attack mode
    attackTimer = attackTime; //a timer that counts down
    restTime = 1.0;
    restTimer = restTime;
    pos.x = p1.x;
    pos.y = p1.y;
    target = p1; // set first patrol point
    static SDL_Texture * t = IMG_LoadTexture(ren, "wolfWarrior.png");
    tex = t;
    rect.h = rect.w = 128;
    animation.push_back(new Animation(tex, SDL_Rect{0, 8 * 64, 64, 64}, 9, .1, "WolfWalkUp"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 10 * 64, 64, 64}, 9, .1, "WolfWalkDown"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 11 * 64, 64, 64}, 9, .1, "WolfWalkRight"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 20 * 64, 64, 64}, 6, .1, "WolfDie"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 1344, 192, 192}, 6, .064, "WolfAtkUp"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 1344 + 192 * 2, 192, 192}, 6, .064, "WolfAtkDown"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 1344 + 192 * 3, 192, 192}, 6, .064, "WolfAtkRight"));
    //place a hold on the first(ish) and last frame of the attacks
    for (int i = ATTACKUP; i <= ATTACKRIGHT; i++) {
        animation[i]->frameTime[2] = .3;
        animation[i]->frameTime[5] = .3;
    }
    animation.push_back(new Animation(tex, SDL_Rect{0, 20 * 64, 64, 64}, 3, .016, "WolfRest"));
    animation[REST]->frameTime[2] = restTime; // set the last frame to hold longer
    currentAnimation = animation[WALKDOWN];
}

WolfWarrior::~WolfWarrior() {
}

void WolfWarrior::update(Player& player) {

    enum WolfStates {
        SEEK, ATTACK, DIE, PATROL
    };
    switch (ws) {
        case SEEK:
        {
            double deltax = (player.pos.x - pos.x)*(player.pos.x - pos.x);
            double deltay = (player.pos.y - pos.y)*(player.pos.y - pos.y);
            double d = deltax + deltay; //distance from player squared
            float angle = atan2(pos.y - player.pos.y, player.pos.x - pos.x);
            if (d < attackRadius) {
                ws = ATTACK;
                currentAnimation->reset();
                break;
            } else if (d < searchRadius) {
                vel.x = cos(angle) * speed * 1.5;
                vel.y = -sin(angle) * speed * 1.5;
            } else {
                ws = PATROL;
                currentAnimation->reset();
                break;
            }
            if (angle < PI / 4 && angle > -PI / 4) {
                currentAnimation = animation[WALKRIGHT];
                flip = SDL_FLIP_NONE;
            } else if (angle > 3 * PI / 4 || angle < -3 * PI / 4) {
                currentAnimation = animation[WALKRIGHT];
                flip = SDL_FLIP_HORIZONTAL;
            } else if (angle <= 3 * PI / 4 && angle >= PI / 4) {
                currentAnimation = animation[WALKUP];
            } else {
                currentAnimation = animation[WALKDOWN];
            }
            break;
        }
        case ATTACK:
        { //initialize the attack

            if (attackTimer == attackTime) {
                target = player.pos;
                float angle = atan2(pos.y - player.pos.y, player.pos.x - pos.x);
                vel.x = vel.y = 0;


                if (angle < PI / 4 && angle > -PI / 4) {
                    currentAnimation = animation[ATTACKRIGHT];
                    flip = SDL_FLIP_NONE;
                } else if (angle > 3 * PI / 4 || angle < -3 * PI / 4) {
                    currentAnimation = animation[ATTACKRIGHT];
                    flip = SDL_FLIP_HORIZONTAL;
                } else if (angle <= 3 * PI / 4 && angle >= PI / 4) {
                    currentAnimation = animation[ATTACKUP];

                } else {
                    currentAnimation = animation[ATTACKDOWN];
                }
                rect.h = rect.w = 128 * 3;

            } else if (attackTimer < 0) { // end the attack
                attackTimer = attackTime;
                currentAnimation->reset();
                ws = REST;
                target = p1;
                rect.w = rect.h = 128;
                vel.x = vel.y = 0;
                currentAnimation = animation[REST];
                player.hp--;
                player.bfx.createBloodFx(player.pos);

                break;
            } else if (currentAnimation->frameCounter == 3) {
                float angle = atan2(pos.y - player.pos.y, player.pos.x - pos.x);
                vel.x = cos(angle) * speed * 5;
                vel.y = -sin(angle) * speed * 5;



            }

            attackTimer -= delta;
            break;
        }
            //        case DIE:
            //            break;
        case REST:
        {
            restTimer -= delta;

            if (restTimer < 0) {
                ws = PATROL;
                currentAnimation->reset();
                restTimer = restTime;

            }
            break;
        }
        case PATROL:
        {
            // Manhattan

            double targetDistance = (pos.x - target.x) + (pos.y - target.y);

            if (abs(targetDistance) < 10) {
                target = target == p1 ? p2 : p1; // switch target to other patrol point
            }
            float angle = atan2(pos.y - target.y, target.x - pos.x);
            vel.x = cos(angle) * speed;
            vel.y = -sin(angle) * speed;
            // change states if...
            double deltax = (player.pos.x - pos.x)*(player.pos.x - pos.x);
            double deltay = (player.pos.y - pos.y)*(player.pos.y - pos.y);
            double d = deltax + deltay; //distance from player squared

            if (d < searchRadius * .75) {

                ws = SEEK;
                currentAnimation->reset();
                break;
            }
            // set animation
            if (angle < PI / 4 && angle > -PI / 4) {
                currentAnimation = animation[WALKRIGHT];
                flip = SDL_FLIP_NONE;
            } else if (angle > 3 * PI / 4 || angle < -3 * PI / 4) {
                currentAnimation = animation[WALKRIGHT];
                flip = SDL_FLIP_HORIZONTAL;
            } else if (angle <= 3 * PI / 4 && angle >= PI / 4) {
                currentAnimation = animation[WALKUP];
            } else {
                currentAnimation = animation[WALKDOWN];
            }

            break;
        }
    }// end switch
    //physics updates:
    pos.x += vel.x * delta;
    pos.y += vel.y * delta;
    rect.x = (pos.x - cam.x) - rect.w * .5;
    rect.y = (pos.y - cam.y) - rect.w * .5;

    currentAnimation->animate();

}
