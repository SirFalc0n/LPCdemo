
#include "Level2.h"

Level2::Level2() {
    // load sprites?
    for (int i = 0; i < 10; i++) {
        Bush *b = new Bush();

        b->pos.x = 400;
        b->pos.y = 200 +i* 128;
        b->rect.x = b->pos.x - b->rect.w / 2;
        b->rect.y = b->pos.y + b->rect.h / 2;

        tiles.push_back(b);

    }
    for (int i = 0; i < 10; i++) {
        Bush *b = new Bush();

        b->pos.x = 656 + 128 * i;
        b->pos.y = 400 + 128 *i;
 
        tiles.push_back(b);

    }
    wolf = new WolfWarrior(V2d{100,100}, V2d{1000,100});
}

Level2::~Level2() {
}

void Level2::enter() {

    player.pos.x = 500;
    player.pos.y = 400;

    // setup hero
    // setup enemies
    // set other things?
    // start music


}

void Level2::update() {


    while (1) {
        delta = (SDL_GetTicks() - lastTime) / 1000;
        lastTime = SDL_GetTicks();

        mouse.update();
        player.update(mouse);
        wolf->update(player);
        checkCollision();
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);

                    // Button actions
                    // case SDL_MOUSEBUTTONUP:

            }// end switch
        }// end event loop



        // draw stuff
        SDL_SetRenderDrawColor(ren, 47, 129, 54, 255);
        SDL_RenderClear(ren);
        for (int i = 0; i < tiles.size(); i++) {
            auto n = tiles[i];
            n->rect.x = (n->pos.x - cam.x) - n->rect.w * .5;
            n->rect.y = (n->pos.y - cam.y) - n->rect.h * .5;
            n->draw();

        }
        wolf->draw();
        player.draw();
        mouse.draw();

     
        SDL_RenderPresent(ren);
    }




}

void Level2::checkCollision() {
    //checking tile collisions. The sides need a separate loop from checking top and bottom
    // sides
    for (int i = 0; i < tiles.size(); i++) {
        // check for blocked north
        if (SDL_HasIntersection(&player.collider[0], &tiles[i]->rect)) {
            player.vel.y = 0;
            player.pos.y++;
           
            break;
        }

        if (SDL_HasIntersection(&player.collider[2], &tiles[i]->rect)) {
            player.vel.y = 0;
            player.pos.y--;
          
            break;
        }
    }
    // top and bottom
    for (int i = 0; i < tiles.size(); i++) {
        if (SDL_HasIntersection(&player.collider[1], &tiles[i]->rect)) {
            player.vel.x = 0;
            player.pos.x--;
           
            break;
        }
        if (SDL_HasIntersection(&player.collider[3], &tiles[i]->rect)) {
            player.vel.x = 0;
            player.pos.x++;
          
            break;
        }
    }
}