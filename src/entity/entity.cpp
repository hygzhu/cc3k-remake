#include "entity.h"

Entity::Entity(int x, int y, int size, RGBA color) : x_(x), y_(y), size_(size), color_(color), m_accelx(0), m_accely(0) {}


BoundingRectangle Entity::getBoundingRectangle()
{
    return BoundingRectangle(x_,y_,size_,size_);
}

void Entity::setMovement(){
    //Do nothing if not overidden
}