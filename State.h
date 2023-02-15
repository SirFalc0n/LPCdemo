
#ifndef STATE_H
#define STATE_H
#include "Mouse.h"
#include "Button.h"

class State {
public:
    static State * current, *previous, *mainMenu,  *options, *credits, *winScreen,*loseScreen, *level1, *level2; 
    static Mouse mouse;
    SDL_Texture * background = nullptr;
    State();

    virtual ~State();
    
    virtual void enter() = 0;
    virtual void update() = 0;

};

class MainMenu: public State{
public:       
    MainMenu();
    enum buttonNames{START, OPTIONS, EXIT, CREDITS};
    Button buttons[3];
    void enter();
    void update();
    
};

class Options: public State{
public:
    Options();
    Button backButton;
    void enter();
    void update();
    
};

#endif /* STATES_H */

