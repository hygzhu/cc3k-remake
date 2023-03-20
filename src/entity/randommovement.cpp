#include "randommovement.h"

#include "../geometry/point.h"
#include "../utils/random.h"
#include "player.h"

RandomMovement::RandomMovement(std::shared_ptr<Entity> entity, Point p,
                               bool collidable)
    : Movement(entity, p, collidable) {}

void RandomMovement::setMovement() {

  // std::cout << m_movement_counter << std::endl;

  if (m_movement_counter == 0) {
    int base_acceleration = 80;
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

void RandomMovement::triggerCollisionSideEffect(std::shared_ptr<Entity> other) {

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

void RandomMovement::tryToMove(
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