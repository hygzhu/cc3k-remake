#ifndef SPRITE_H
#define SPRITE_H

#include "../geometry/point.h"
#include "../renderer.h"

class Sprite {
    
public:

    virtual void render(Renderer renderer, Point p, float xtrans, float ytrans, Point baseviewp, Point relativeviewp, Rectangle viewbox) = 0;
};

#endif