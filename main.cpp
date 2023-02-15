
#include "Level2.h"


using namespace std;
SDL_Window * win = SDL_CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED,
        10, WIDTH, HEIGHT, NULL);
SDL_Renderer * ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

Mouse State::mouse;
SDL_Texture * Button::tex = IMG_LoadTexture(ren, "buttons.png");
State* State::mainMenu = new MainMenu();
State* State::options = new Options();
State* State::level2 = new Level2();
State* State::current = State::level2;

double delta = .0001;
double lastTime = SDL_GetTicks();
Camera cam;

bool running = true;
int main(int argc, char** argv) {
    while (running) {
        State::current->enter();
        State::current->update();

    }


    return 0;
}

