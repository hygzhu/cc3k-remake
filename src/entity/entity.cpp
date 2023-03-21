#include "entity.h"

Entity::Entity(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite,
               Status status)
    : m_point(std::make_shared<Point>(p)), m_hitbox(hitbox), m_sprite(sprite), m_status(status) {
  
  // Make hitbox use the same point
  m_hitbox.setPoint(m_point);
}

Hitbox Entity::getHitbox() { return m_hitbox; }

std::shared_ptr<Sprite> Entity::getSprite() { return m_sprite; }

Status &Entity::getStatus() { return m_status; }

Point Entity::getPoint() { return Point(m_point->getX(), m_point->getY()); }


void Entity::setPoint(Point p) { 
  m_point->setX(p.getX()); 
  m_point->setY(p.getY());
}

std::shared_ptr<Movement> Entity::getMovement() { return m_movement; }

void Entity::setMovement(std::shared_ptr<Movement> movement) {
  m_movement = movement;
  m_movement->setPoint(m_point);
}

void Entity::move(double x, double y) {
  m_movement->move(x, y);
}