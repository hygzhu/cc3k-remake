#include "followmovement.h"

#include "../../geometry/point.h"
#include "../../utils/random.h"
#include "../player.h"

FollowMovement::FollowMovement(std::shared_ptr<Entity> entity, Point p,
                               bool collidable, std::shared_ptr<Entity> target, int range)
    : Movement(entity, p, collidable), m_target(target), m_range(range) {}

void FollowMovement::setMovement() {


  int base_acceleration = 80;

  if (m_movement_counter == 0) {
    if(m_target->getHitbox().getCenterCoordinate().distanceTo(m_entity->getHitbox().getCenterCoordinate()) <= m_range ){
      std::cout << "Follow" << std::endl;
      // follow target
      int dx = m_target->getHitbox().getCenterCoordinate().getX() - m_entity->getHitbox().getCenterCoordinate().getX();
      int dy = m_target->getHitbox().getCenterCoordinate().getY() - m_entity->getHitbox().getCenterCoordinate().getY();

      if(dx > 0){
        dx = 1;
      }
      if(dx< 0){
        dx = -1;
      }
      if(dy > 0){
        dy = 1;
      }
      if(dy< 0){
        dy = -1;
      }

      m_accelx = base_acceleration * dx;
      m_accely = base_acceleration * dy;

    }else{
      //randomly move
      // random direction
      int rand = Random::randomInt(0, 2);
      if (rand == 2) {
      rand = -1;
      }
      m_accelx = base_acceleration * rand;
      rand = Random::randomInt(0, 2);
      if (rand == 2) {
      rand = -1;
      }
      m_accely = base_acceleration * rand;
      }
  }
}

void FollowMovement::triggerCollisionSideEffect(std::shared_ptr<Entity> other) {

  std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(other);
  if (player != nullptr) {
    if (!other->getMovement()->isInvincible()) {
      other->getStatus().defendFrom(m_entity->getStatus());
      other->getMovement()->setInvincible(true);
    }
    if (!m_isInvincible) {
      m_entity->getStatus().defendFrom(other->getStatus());
      m_isInvincible = true;
    }
  }
}

void FollowMovement::tryToMove(
    double time, std::vector<std::shared_ptr<Entity>> otherEntities) {
  tick(time);
  m_movement_counter++;
  m_movement_counter = m_movement_counter % 50;

  if (m_movement_counter % 2 == 0) {
    int entityVelX = m_accelx * time;
    int entityVelY = m_accely * time;
    if (entityVelX != 0 || entityVelY != 0) {
      Point new_location =
          closestMovablePoint(Point(entityVelX, entityVelY), otherEntities);
      move(new_location.getX(), new_location.getY());
    }
  }
}