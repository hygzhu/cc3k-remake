#ifndef FOLLOWMOVEMENT_H
#define FOLLOWMOVEMENT_H


#include "movement.h"

class FollowMovement : public Movement {

public:
  FollowMovement(std::shared_ptr<Entity> entity, Point p, bool collidable, std::shared_ptr<Entity> player, int range);

  void setMovement() override;
  void tryToMove(double time,
                 std::vector<std::shared_ptr<Entity>> otherEntities) override;
  void triggerCollisionSideEffect(std::shared_ptr<Entity> other) override;

private:
  int m_movement_counter = 0;
  int m_range;
  std::shared_ptr<Entity> m_target;
};

#endif