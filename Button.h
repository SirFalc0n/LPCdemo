

#ifndef BUTTON_H
#define BUTTON_H
#include "globals.h"
#include "Mouse.h"

class Button {
public:
    static SDL_Texture * tex ;
    SDL_Rect srect;
    SDL_Rect drect;
    bool isSelected = false;
    Uint8 r, g, b; // to store original color;
    
    Button();
    void update(Mouse&);
    void draw();
    virtual ~Button();
private:

};

#endif /* BUTTON_H */

