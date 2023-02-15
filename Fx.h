

#ifndef FX_H
#define FX_H
#include "Projectile.h"
#include <vector>

class Fx {
public:
      
    double fxTimer;
    double fxTime;
    Fx();
    virtual ~Fx();
    virtual void update();
    virtual void draw();
};

class BloodFx: public Fx{
public:
    vector<BloodDrop*> particles;  
    BloodFx();
    ~BloodFx();
    void update();
    void draw();
    void createBloodFx(V2d& pos);
    
};
#endif /* FX_H */

