#include "entity.h"

Entity::Entity(int x, int y, int size, RGBA color) : x_(x), y_(y), size_(size), color_(color) {}


BoundingRectangle Entity::getBoundingRectangle()
{
    return BoundingRectangle(x_,y_,size_,size_);
}