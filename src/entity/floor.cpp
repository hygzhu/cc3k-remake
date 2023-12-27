#include "floor.h"
#include "../graphics/spritefactory.h"
#include <iostream>


Floor::Floor(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status stats): Entity(p, hitbox, sprite, stats){}

void Floor::move(int dx, int dy) {
  // Floors don't move, so do nothing
}

void Floor::printEntityType() {
  // std::cout << "Floor " << getHitbox().toString() << std::endl;
}

bool Floor::collidable() { return true; }