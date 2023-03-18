#include "entity.h"

Entity::Entity(Rectangle rect, std::shared_ptr<Sprite> sprite): 
 m_x(rect.getX()), 
 m_y(rect.getY()), 
  m_accelx(0), m_accely(0), 
  m_hitbox(Hitbox(Rectangle(0,0,rect.getWidth(), rect.getHeight()), Point(rect.getX(), rect.getY()))),
  m_sprite(sprite){
}


Entity::Entity(Point p, Hitbox hitbox, std::shared_ptr<Sprite> sprite):
    m_x(p.getX()), 
    m_y(p.getY()), 
    m_accelx(0), m_accely(0), 
    m_hitbox(hitbox),
    m_sprite(sprite){}

void Entity::setMovement(){
    //Do nothing if not overidden
}

bool Entity::collidable(){
    return false;
}

int & Entity::getAccelX(){ return m_accelx;}
int & Entity::getAccelY(){return m_accely;}

Hitbox Entity::getHitbox()
{
    return m_hitbox;
}


void Entity::move(int dx, int dy) {
    m_x = dx;
    m_y = dy;
    m_hitbox.setPoint(Point(dx, dy));
}

std::shared_ptr<Sprite> Entity::getSprite(){
    return m_sprite;
}

Point Entity::getPoint(){
    return Point(m_x, m_y);
}