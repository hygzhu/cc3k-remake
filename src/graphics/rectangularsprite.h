#ifndef RECTANGULARSPRITE_H
#define RECTANGULARSPRITE_H

#include "../geometry/rectangle.h"
#include "rgba.h"
#include "sprite.h"

class RectangularSprite : public Sprite {
public:
  RectangularSprite(Rectangle rect, RGBA rgba);

  void render(Renderer renderer, Point p) override;

private:
  Rectangle m_rect;
  RGBA m_color;
};

#endif