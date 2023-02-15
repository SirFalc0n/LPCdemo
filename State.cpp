

#include "State.h"

State::State() {
}

State::~State() {
}

MainMenu::MainMenu(){
    background = IMG_LoadTexture(ren, "mainMenu.png");
    buttons[START].srect.x = 0;
    buttons[START].srect.y = 0;
    buttons[START].srect.w = 400;
    buttons[START].srect.h = 100;
    buttons[START].drect.w = 200;
    buttons[START].drect.h = 50;
    buttons[START].drect.x = (WIDTH/2)- 100;
    buttons[START].drect.y = 200;
    
    buttons[OPTIONS].srect.x = 0;
    buttons[OPTIONS].srect.y = 100*3;
    buttons[OPTIONS].srect.w = 400;
    buttons[OPTIONS].srect.h = 100;
    buttons[OPTIONS].drect.w = 200;
    buttons[OPTIONS].drect.h = 50;
    buttons[OPTIONS].drect.x = (WIDTH/2)- 100;
    buttons[OPTIONS].drect.y = 300; 
    
    buttons[EXIT].srect.x = 0;
    buttons[EXIT].srect.y = 100*7;
    buttons[EXIT].srect.w = 400;
    buttons[EXIT].srect.h = 100;
    buttons[EXIT].drect.w = 200;
    buttons[EXIT].drect.h = 50;
    buttons[EXIT].drect.x = (WIDTH/2)- 100;
    buttons[EXIT].drect.y = 400; 
    
}
void MainMenu::enter(){

    }
void MainMenu::update(){

    while(1){
        
        mouse.update();
        for (int i = 0; i < 3; i++){
            buttons[i].update(mouse);
        }
        
        SDL_Event e;
        while (SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);
                    
                      // Button actions
                case SDL_MOUSEBUTTONUP:
                    if (buttons[OPTIONS].isSelected){
                        current = options;
                        return;
                    }
                     if (buttons[START].isSelected){
                        current = level2;
                        return;
                    }
                    if (buttons[EXIT].isSelected){
                        running = false;
                        SDL_DestroyWindow(win);
                        SDL_Quit();
                        return;
                    }
            }// end switch
        }// end event loop
        
            
        
        // draw stuff
        SDL_SetRenderDrawColor(ren, 100,100,100,255);
        SDL_RenderClear(ren);
   
        SDL_RenderCopy(ren, background, NULL, NULL);
        for (int i = 0; i < 3; i++){
            buttons[i].draw();
        }
        mouse.draw();
        
        
         SDL_RenderPresent(ren);
    }
}


Options::Options(){
    background = IMG_LoadTexture(ren, "options.png");
    backButton.srect.y = 200;
    backButton.drect.x = 1100;
    backButton.drect.y = 10;
    

}
void Options::enter(){

}
void Options::update(){

 while(1){
        
        mouse.update();
        backButton.update(mouse);
        
        SDL_Event e;
        while (SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    SDL_Quit();
                    return;
                      // Button actions
                case SDL_MOUSEBUTTONUP:
                    if (backButton.isSelected){
                        current = mainMenu;
                        return;
                    }
              
            }// end switch
        }// end event loop
              
        // draw stuff
        SDL_SetRenderDrawColor(ren, 100,100,100,255);
        SDL_RenderClear(ren);
   
        SDL_RenderCopy(ren, background, NULL, NULL);
        backButton.draw();
        mouse.draw();
        
        
         SDL_RenderPresent(ren);
    }

}