#ifndef FLOOR_H
#define FLOOR_H

#include "entity.h"

class Floor : public Entity {
public:
  Floor(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status stats);

  virtual bool collidable();
  virtual void printEntityType();

  virtual void move(int dx, int dy);
};

#endif