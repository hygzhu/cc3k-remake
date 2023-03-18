#ifndef RECTANGULARSPRITE_H
#define RECTANGULARSPRITE_H

#include "sprite.h"
#include "../geometry/rectangle.h"
#include "rgba.h"

class RectangularSprite : public Sprite {
public:
    RectangularSprite(Rectangle rect, RGBA rgba);
    
    void render(Renderer renderer, Point p,float xtrans, float ytrans, Point baseviewp, Point relativeviewp, Rectangle viewbox) override;
private:
    Rectangle m_rect;
    RGBA m_color;

};

#endif