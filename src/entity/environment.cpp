#include "environment.h"
#include <iostream>
#include "../graphics/spritefactory.h"

Environment::Environment(int x, int y) : 
Entity(Rectangle(x,y,1,1), SpriteFactory::createRectangularSprite(
    SpriteFactory::SpriteType::RECTANGULAR, Rectangle(0,0,1,1), { 128, 128, 128, 255 })) {}


void Environment::printEntityType(){
    std::cout<<"Environment" << std::endl;
}