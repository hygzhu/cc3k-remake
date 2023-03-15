#include "floor.h"
#include <iostream>

Floor::Floor(Rectangle rect) : Entity(rect, { 128, 128, 128, 255 }) {}

void Floor::move(int dx, int dy) {
    // Floors don't move, so do nothing
}

void Floor::printEntityType(){
    std::cout<<"Floor " << getRectangle().toString() <<std::endl;
}

bool Floor::collidable(){
    return true;
}