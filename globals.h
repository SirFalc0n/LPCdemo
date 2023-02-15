
#ifndef GLOBALS_H
#define GLOBALS_H
#include <sdl.h>
#include <sdl_image.h>
#include <iostream>
#include <cmath>
#include "Camera.h"
#define WIDTH  1280
#define HEIGHT  720
#define PI 3.14159
extern SDL_Renderer * ren;
extern SDL_Window * win;
extern double delta;
extern double lastTime;
extern Camera cam;
static int init = SDL_Init(SDL_INIT_EVERYTHING);
extern bool running; 
using namespace std;
#endif /* GLOBALS_H */

