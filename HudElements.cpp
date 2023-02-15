
#include "HudElements.h"

HudElement::HudElement() {
}

HudElement::~HudElement() {
}

void HudElement::update() {

}

void HudElement::draw() {
    SDL_RenderCopy(ren, tex, &srect, &drect);
}

Heart::Heart() {
    static SDL_Texture * t = IMG_LoadTexture(ren, "hearts.png");
    tex = t;
    drect.h = drect.w = 32;
    srect.h = srect.w = 32;
    srect.x = 0;
    srect.y = 32*2;

}

Heart::~Heart() {
}

void Heart::update(int hs) {
    // enum HeartState{EMPTY, HALF, FULL};
    this->hs = hs;
    switch (hs) {
        case EMPTY:
            srect.y =32 ;
            break;
        case HALF:
            srect.y = 0;
            break;
        case FULL:
            srect.y = 32 * 2;
            break;
    }

}

