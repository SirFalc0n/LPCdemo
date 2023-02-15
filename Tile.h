

#ifndef TILE_H
#define TILE_H
#include "globals.h"
#include "V2d.h"
class Tile {
public:
    SDL_Texture * tex = nullptr;
    SDL_Rect rect;
    V2d pos;
    bool isWall = false;
    Tile();
    virtual ~Tile();

    virtual void draw() {

        SDL_SetRenderDrawColor(ren, 200, 150, 0, 255);
        SDL_RenderFillRect(ren, &rect);
        SDL_SetRenderDrawColor(ren, 0, 10, 0, 255);
        SDL_RenderDrawRect(ren, &rect);
    }


};

class Bush : public Tile {
public:

    Bush() {
        static SDL_Texture * t = IMG_LoadTexture(ren, "bush.png");
        tex = t;
        rect.w = rect.h = 128;
    }
    void draw(){
//        SDL_SetRenderDrawColor(ren,200, 0,0,254);
//        SDL_RenderDrawRect(ren, &rect);
        SDL_RenderCopy(ren, tex, NULL, &rect);
    }
};
#endif /* TILE_H */

