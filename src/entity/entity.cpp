#include "entity.h"

Entity::Entity(Rectangle rect, std::shared_ptr<Sprite> sprite)
    : m_hitbox(Hitbox(Rectangle(0, 0, rect.getWidth(), rect.getHeight()),
                      Point(rect.getX(), rect.getY()))),
      m_sprite(sprite), m_status(Status()) {}

Entity::Entity(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite,
               Status status)
    : m_hitbox(hitbox), m_sprite(sprite), m_status(status) {}

Hitbox &Entity::getHitbox() { return m_hitbox; }

std::shared_ptr<Sprite> Entity::getSprite() { return m_sprite; }

Status &Entity::getStatus() { return m_status; }

Point Entity::getPoint() { return m_movement->getPoint(); }

std::shared_ptr<Movement> Entity::getMovement() { return m_movement; }

void Entity::move(double x, double y) {
  m_movement->move(x, y);
  m_hitbox.setPoint(Point(x, y));
}