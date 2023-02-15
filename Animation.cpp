#include "Animation.h"

Animation::Animation() {

}


Animation::Animation(SDL_Texture * texture, SDL_Rect startingRect, int numberOfFrames, double frameTime, char*name ) {
    this->tex = texture; // the sprite sheet for the animation	
    this->numberOfFrames = numberOfFrames; // the number of frames to play in the animation	
    this->rect = startingRect; // the source rectangle that moves along the sprite sheet
    x = rect.x;// the starting x value for the source rectangle (for resetting)
    y = rect.y; // the starting y value for the source rectangle
    // frameTime is used to set the amount of time one frame stays on the screen
    for(int i = 0; i < numberOfFrames; i++){
        this->frameTime.push_back(frameTime);
    } 
    strcpy(this->name, name);
    frameTimer = 0;
    frameCounter = 0;
    
    

}

Animation::~Animation() {
}

void Animation::animate() {

    frameTimer += delta;
    if (frameTimer >= frameTime[frameCounter]) {
        frameTimer = 0;
        frameCounter += 1;
        if (frameCounter == numberOfFrames) { // reset the animation if we have reached the last frame.
            reset();  
            return;
          }
       rect.x += rect.w;
    }
}

void Animation::reset(){
    frameTimer = 0;
    frameCounter = 0;
    rect.x =x;
    rect.y =y;
    isComplete = true;
    
}