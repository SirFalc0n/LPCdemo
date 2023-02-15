

#ifndef HUDELEMENTS_H
#define HUDELEMENTS_H
#include "globals.h"

class HudElement {
public:
    SDL_Texture * tex;
    SDL_Rect srect, drect;
    virtual void update();
    virtual void draw();
    HudElement();
    virtual ~HudElement();
};

class Heart: public HudElement {
public:
    enum HeartState {HALF, EMPTY, FULL};
    int hs = FULL;
    Heart();
    ~Heart();
    void update(int hs);
};


#endif /* HUDELEMENTS_H */

