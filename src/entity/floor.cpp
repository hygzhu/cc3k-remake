#include "floor.h"
#include <iostream>
#include "../graphics/spritefactory.h"

Floor::Floor(Rectangle rect) : Entity(rect, SpriteFactory::createRectangularSprite(
    SpriteFactory::SpriteType::RECTANGULAR, Rectangle(0,0,rect.getWidth(), rect.getHeight()), { 128, 128, 128, 255 })) {}

void Floor::move(int dx, int dy) {
    // Floors don't move, so do nothing
}

void Floor::printEntityType(){
    std::cout<<"Floor " <<  getHitbox().toString() <<std::endl;
}

bool Floor::collidable(){
    return true;
}