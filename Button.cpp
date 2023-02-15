/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Button.h"
#include <iostream>
using namespace std;

Button::Button() {
    srect.x=0;
    srect.w = 400;
    srect.h = 100;
    drect.w = 200;
    drect.h = 50;
    SDL_GetTextureColorMod(tex, &r,&g,&b);

}

Button::~Button() {
}

void Button::update(Mouse  &mouse){
    if (SDL_HasIntersection(&mouse.point, &drect)){
        isSelected = true; 
    }
    else {
        isSelected = false;
    }
}
void Button::draw(){
    if (isSelected){
        SDL_SetTextureColorMod(tex, 255,0,0);
    }
    else {
        SDL_SetTextureColorMod(tex, r, g, b);
    }
    SDL_RenderCopy(ren, tex, &srect, &drect);
    
}