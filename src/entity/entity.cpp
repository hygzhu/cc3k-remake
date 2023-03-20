#include "entity.h"

Entity::Entity(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite,
               Status status)
    : m_hitbox(hitbox), m_sprite(sprite), m_status(status) {}

Hitbox Entity::getHitbox() { return m_hitbox; }

std::shared_ptr<Sprite> Entity::getSprite() { return m_sprite; }

Status &Entity::getStatus() { return m_status; }

Point Entity::getPoint() { return m_movement->getPoint(); }


void Entity::setPoint(Point p) { 
  m_hitbox.setPoint(p);
}

std::shared_ptr<Movement> Entity::getMovement() { return m_movement; }

void Entity::move(double x, double y) {
  m_movement->move(x, y);
  m_hitbox.setPoint(Point(x, y));
}