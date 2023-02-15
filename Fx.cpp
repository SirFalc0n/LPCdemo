

#include "Fx.h"

Fx::Fx() {
}

Fx::~Fx() {
}

void Fx::update() {
}

void Fx::draw() {
}

BloodFx::BloodFx() {
    for (int i = 0; i < 20; i++) {
        BloodDrop *b = new BloodDrop();
        if (i % 2 == 0) {
            // colors: 192,20,29 or 237,28,36
            b->r = 237;
            b->g = 20;
            b->b = 29;
            b->rect.h = b->rect.w = 2;
            
        }else{
        b->rect.h = b->rect.w = 4;
        }
        b->acl.x = 0;
        b->acl.y = 1000;
        b->vel.x = rand() % (200 - -200+1)+ -200;
        b->vel.y = rand() % (-100 - -400+1)+ -400;
        b->pos.x = b->pos.y = 0;
        particles.push_back(b);
        fxTimer = fxTime = .4f;
    }

}

BloodFx::~BloodFx() {

}

void BloodFx::update() {
    fxTimer -= delta;
    if (fxTimer > 0){
      
        for(int i=0; i < particles.size();i++){
            auto p =particles[i];
            p->vel.y += p->acl.y * delta;
            p->pos.x += p->vel.x *delta;
            p->pos.y += p->vel.y *delta;
            p->rect.x = p->pos.x - p->rect.w*.5;
            p->rect.y = p->pos.y - p->rect.h*.5;
            
        }
    }
    
}
void BloodFx::createBloodFx(V2d& pos){
    for(int i = 0; i < particles.size();i++){
        particles[i]->pos = pos;
        particles[i]->vel.x = rand() % (200 - -200+1)+ -200;
        particles[i]->vel.y = rand() % (-10 - -100+1)+ -100;
    }
    fxTimer = fxTime;
    
}

void BloodFx::draw() {
    for (auto& n:particles){
        n->rect.x -= cam.x;
        n->rect.y -= cam.y;
        SDL_SetRenderDrawColor(ren,n->r,n->g, n->b,255);
        SDL_RenderFillRect(ren, &n->rect);
    }

}