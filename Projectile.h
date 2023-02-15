

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "globals.h"
#include "V2d.h"
class Projectile {
public:
    SDL_Texture * tex;
    SDL_Rect rect;
    float angle;
    V2d pos, vel, acl;
    double speed;
    double spinSpeed = 0;
    bool isActive = false;
    double flightTime = 3;
    double flightTimer = flightTime;
    Projectile();
    virtual ~Projectile();
    
    void update();
    void draw();

};

class WizardProjectile: public Projectile{
public:
    WizardProjectile();
    virtual ~WizardProjectile();
    
};

class BloodDrop: public Projectile{
public:
    // colors: 192,20,29  237,28,36
    Uint8 r=192, g=20, b=29;
};
#endif /* PROJECTILE_H */

