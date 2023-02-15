

#include "Player.h"
#include "HudElements.h"

Player::Player() {
    //  enum AnimationEnums{WALKUP, WALKDOWN, WALKRIGHT, DIE, ATTACKUP, ATTACKDOWN, ATTACKRIGHT};
    tex = IMG_LoadTexture(ren, "Wizard.png");
    if (!tex) {
        cout << "Error loading wizard texture: \n" << SDL_GetError() << endl;
    }
    animation.push_back(new Animation(tex, SDL_Rect{0, 8 * 64, 64, 64}, 9, .1, "wizWalkUp"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 10 * 64, 64, 64}, 9, .1, "wizWalkDown"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 11 * 64, 64, 64}, 9, .1, "wizWalkRight"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 20 * 64, 64, 64}, 6, .1, "wizDie"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 4 * 64, 64, 64}, 8, .016, "wizAtkUp"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 6 * 64, 64, 64}, 8, .016, "wizAtkDown"));
    animation.push_back(new Animation(tex, SDL_Rect{0, 7 * 64, 64, 64}, 8, .016, "wizAtkRight"));
    currentAnimation = animation[WALKDOWN];
    prevAnimation = currentAnimation;
    pos.x = WIDTH / 2;
    pos.y = HEIGHT / 2;
    rect.w = 128;
    rect.h = 128;
    rect.x = pos.x - rect.w / 2;
    rect.y = pos.y - rect.h / 2;

    for (int i = 0; i < 20; i++) {
        shots.push_back(new WizardProjectile());
    }

    // set colliders

    collider[0].h = collider[2].h = 4;
    collider[0].w = collider[2].w = 16;
    collider[1].h = collider[3].h = rect.h / 3;
    collider[1].w = collider[3].w = 4;
    // starting top and going clockwise
    collider[0].x = pos.x;
    collider[0].y = pos.y - rect.h / 4;
    //right
    collider[1].x = pos.x + 16;
    collider[1].y = pos.y;
    //bottom
    collider[2].x = pos.x;
    collider[2].y = pos.y + rect.h / 2;
    //left
    collider[3].x = pos.x - 16;
    collider[3].y = pos.y;

    // health
    hp = 6.5;
    maxhp = 10;
    for (int i = 0; i < maxhp; i++) {
        Heart h;
        h.drect.x = WIDTH - (h.drect.w * i) - 64;
        h.drect.y = 5;
        healthBar.push_back(h);
    }
    // starting state
    ps = S_WALK;
}

Player::~Player() {
    // clean up dynamically allocated memory
    for (int i = 0; i < animation.size(); i++) {
        delete animation[i];
    }
    SDL_DestroyTexture(tex);
}

void Player::update(Mouse& mouse) {
    //check keyboard state
    auto key = SDL_GetKeyboardState(NULL);
    switch (ps) {
        case S_WALK:
        {
            attackTimer -= delta;
            if (!isAttacking) {
                vel.x = 0;
                vel.y = 0;
                //respond to keyboard input
                if (key[SDL_SCANCODE_W]) {
                    currentAnimation = animation[WALKUP];
                    vel.y = -speed;
                    currentAnimation->isComplete = false;
                }
                if (key[SDL_SCANCODE_S]) {
                    currentAnimation = animation[WALKDOWN];
                    vel.y = speed;
                    currentAnimation->isComplete = false;
                }
                if (key[SDL_SCANCODE_D]) {
                    currentAnimation = animation[WALKRIGHT];
                    vel.x = speed;
                    flip = SDL_FLIP_NONE;
                    currentAnimation->isComplete = false;
                }
                if (key[SDL_SCANCODE_A]) {
                    currentAnimation = animation[WALKRIGHT];
                    flip = SDL_FLIP_HORIZONTAL;
                    vel.x = -speed;
                    currentAnimation->isComplete = false;
                }
            }
            // begin right click (attack)
            if (mouse.mouseState == SDL_BUTTON(1) && attackTimer < 0) {
                attackTimer = attackDelay;
                auto angle = atan2((rect.y + rect.h / 2) - mouse.point.y, mouse.point.x - (rect.x + rect.w / 2));
                for (int i = 0; i < shots.size(); i++) {
                    if (!shots[i]->isActive) {
                        shots[i]->isActive = true;
                        shots[i]->vel.x = cos(angle) * shots[i]->speed;
                        shots[i]->vel.y = -sin(angle) * shots[i]->speed;
                        shots[i]->pos.x = pos.x;
                        shots[i]->pos.y = pos.y;
                        isAttacking = true;
                        prevAnimation = currentAnimation; // set previous animation so we can return to walking after the shot is fired.
                        if (angle > -60 * PI / 180 && angle < 60 * PI / 180) {
                            currentAnimation = animation[ATTACKRIGHT];
                            flip = SDL_FLIP_NONE;
                        } else if (angle > 4 * PI / 6 || angle < -4 * PI / 6) {
                            currentAnimation = animation[ATTACKRIGHT];
                            flip = SDL_FLIP_HORIZONTAL;
                        } else if (angle >= 2 * PI / 6 && angle <= 4 * PI / 6) {
                            currentAnimation = animation[ATTACKUP];
                        } else if (angle <= -2 * PI / 6 && angle >= -4 * PI / 6)
                            currentAnimation = animation[ATTACKDOWN];
                        currentAnimation->isComplete = false;
                        break;
                    }
                }
            } // end if right click
            if (isAttacking && currentAnimation->isComplete) {
                isAttacking = false;
            }

            // state changes
            if (hp < .5) {
                ps = S_DIE;
            }
            break;
        }// end walk case
        case DIE:
            currentAnimation = animation[DIE];
            break;
    }// END STATE SWITCH?
    if (!currentAnimation->isComplete) {
        currentAnimation->animate();
    }
    pos.x += vel.x*delta;
    pos.y += vel.y*delta;

    cam.x = pos.x - WIDTH / 2;
    cam.y = pos.y - HEIGHT / 2;

    for (int i = 0; i < shots.size(); i++) {
        if (shots[i]->isActive) {
            shots[i]->update();
        }
    }
    // update collider positions
    collider[0].x = rect.x + rect.w / 2 - collider[0].w / 2;
    collider[0].y = rect.y + rect.h / 2;
    collider[1].x = rect.x + rect.w - 48 - 4;
    collider[1].y = rect.y + rect.h / 2 + 8;
    collider[2].x = rect.x + rect.w / 2 - collider[0].w / 2;
    collider[2].y = rect.y + rect.h - 8;
    collider[3].x = rect.x + 48;
    collider[3].y = rect.y + rect.h / 2 + 8;

    // update health
    for (int i = maxhp; i > 0; i--) {
        if (hp == i - .5) {
            healthBar[i - 1].update(Heart::HALF);
        } else if (hp >= i) {
            healthBar[i - 1].update(Heart::FULL);
        } else {
            healthBar[i - 1].update(Heart::EMPTY);
        }
    }
    // update FX
    bfx.update();
}

void Player::draw() {

    for (int i = 0; i < shots.size(); i++) {
        if (shots[i]->isActive) {
            shots[i]->draw();

        }
    }
    for (int i = 0; i < maxhp; i++) {
        SDL_RenderCopy(ren, healthBar[i].tex, &healthBar[i].srect, &healthBar[i].drect);
    }
    SDL_RenderCopyEx(ren, tex, &currentAnimation->rect, &rect, 0, NULL, flip);
    
    //draw FX
    bfx.draw();
    
    //  debugging draw colliders
    //        SDL_SetRenderDrawColor(ren, 250, 0, 0, 255);
    //        for (int i = 0; i < 4; i++) {
    //    
    //            SDL_RenderDrawRect(ren, &collider[i]);
    //        }


}