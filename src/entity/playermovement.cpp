#include "playermovement.h"
#include "../geometry/point.h"
#include "enemy.h"
#include "entity.h"

PlayerMovement::PlayerMovement(std::shared_ptr<Entity> entity, Point p,
                               bool collidable)
    : Movement(entity, p, collidable) {}

void PlayerMovement::triggerCollisionSideEffect(std::shared_ptr<Entity> other) {

  std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(other);
  if (enemy != nullptr) {
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