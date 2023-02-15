#pragma once
#include <vector>
#include "globals.h"
using namespace std;

class Animation
{
public:
        char name[32];
	vector<double> frameTime; // should between 0.01 and .1 for most animations - lower is faster
	double frameTimer; // keeps track of how long a frame has been displayed
	int numberOfFrames; // total number of frames in the animation
        int x,y; // starting x and y values for an animation
	SDL_Rect rect; // the rectangle on the sprite sheet
	SDL_Texture *tex; // the png image
	int frameCounter; // keeps track of which frame the animation is on
        bool isComplete = false; // a flag to know when the last frame is played

	Animation();
	Animation(SDL_Texture *, SDL_Rect startingRect, int numberOfFrames, double frameTime, char*name="unNamed");
	~Animation();
        
        // plays the animations
	void animate();
        
        // resets an animation to the first frame
        void reset();
};
