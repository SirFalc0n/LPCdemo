
#include "Projectile.h"

Projectile::Projectile() {
    speed = 3000;
    rect.w = rect.h = 16;
}

Projectile::~Projectile() {
}
using namespace std;

void Projectile::update() {
  

    pos.x += vel.x * delta;
    pos.y += vel.y * delta;
    rect.x = (pos.x - cam.x) - rect.w / 2;
    rect.y = (pos.y - cam.y) - rect.h / 2;
    angle += spinSpeed;
    flightTimer -= delta;
    if (flightTimer < 0) {
        isActive = false;
        flightTimer = flightTime;
    }
}

void Projectile::draw() {

    SDL_RenderCopyEx(ren, tex, NULL, &rect, angle, NULL, SDL_FLIP_NONE);

}

WizardProjectile::WizardProjectile() {
    speed = 800;
    spinSpeed = 1;
    static SDL_Texture * t = IMG_LoadTexture(ren, "projectile1.png");
    tex = t;
    rect.w = 32;
    rect.h = 32;
}

WizardProjectile::~WizardProjectile() {
}