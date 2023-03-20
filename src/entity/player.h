#ifndef PLAYER
#define PLAYER

#include "../graphics/spritefactory.h"
#include "entity.h"

class Player : public Entity {
public:
  Player(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite, Status stats);
  virtual void printEntityType() override;
  // void triggerCollisionSideEffect(std::shared_ptr<Entity> other) override;
};

#endif
