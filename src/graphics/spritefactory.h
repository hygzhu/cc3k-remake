#ifndef SPRITEFACTORY_H
#define SPRITEFACTORY_H

#include "rgba.h"
#include "sprite.h"
#include <memory>
#include "../geometry/rectangle.h"

class SpriteFactory {

public:
  enum SpriteType { RECTANGULAR = 1 };

  static std::shared_ptr<Sprite>
  createRectangularSprite(SpriteType type, Rectangle rect, RGBA rgba);
};

#endif