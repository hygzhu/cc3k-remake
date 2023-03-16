#include "entity.h"

Entity::Entity(int x, int y, int size, RGBA color) : m_x(x), 
m_y(y), m_width(size), m_height(size),
 m_color(color), m_accelx(0), m_accely(0), m_hitbox(Hitbox(Rectangle(0,0,size,size), Point(x,y))) {}


Entity::Entity(Rectangle rect, RGBA color): m_x(rect.getX()), 
m_y(rect.getY()), m_width(rect.getWidth()),
 m_height(rect.getHeight()), m_color(color),
  m_accelx(0), m_accely(0), m_hitbox(Hitbox(Rectangle(0,0,rect.getWidth(), rect.getHeight()), Point(rect.getX(), rect.getY()))){
}

Rectangle Entity::getRectangle()
{
    return Rectangle(m_x,m_y,m_width,m_height);
}

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