
#ifndef MOUSE_H
#define MOUSE_H
#include "globals.h"

class Mouse {
public:
    SDL_Texture *tex;
    SDL_Rect rect;
    SDL_Rect point;
    Uint32 mouseState =0;
    void update();
    void draw();
    
    Mouse();

    virtual ~Mouse();
private:

};

#endif /* MOUSE_H */

