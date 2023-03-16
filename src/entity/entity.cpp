#include "entity.h"

Entity::Entity(int x, int y, int size, RGBA color) : m_x(x), 
m_y(y), m_width(size), m_height(size), m_color(color), m_accelx(0), m_accely(0) {}


Entity::Entity(Rectangle rect, RGBA color): m_x(rect.getX()), 
m_y(rect.getY()), m_width(rect.getWidth()), m_height(rect.getHeight()), m_color(color), m_accelx(0), m_accely(0){
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
int Entity::getX() const{ return m_x;};
int Entity::getY() const{return m_y;};
void Entity::setX(int x) { m_x = x; }
void Entity::setY(int y) { m_y =y;}
int & Entity::getAccelX(){ return m_accelx;}
int & Entity::getAccelY(){return m_accely;}