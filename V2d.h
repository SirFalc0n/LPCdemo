

#ifndef V2D_H
#define V2D_H
#include "globals.h"

struct V2d{
    float x, y;
    V2d(float x = 0, float y = 0):x{x},y{y}{}
    
    void operator +=(V2d v){
        x += v.x;
        y += v.y;
    }
   bool operator ==(V2d& v){
        if (x == v.x && y == v.y)
            return true;
        else return false;
    }

};



#endif /* V2D_H */

