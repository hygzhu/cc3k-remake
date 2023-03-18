
#include "player.h"
#include <iostream>


Player::Player(int size, RGBA color): Entity(Rectangle(0,0,size,size),  
SpriteFactory::createRectangularSprite(
    SpriteFactory::SpriteType::RECTANGULAR, Rectangle(0,0,size,size), color)
    ) {}



void Player::printEntityType(){
    std::cout<<"Player " << getHitbox().toString() <<  std::endl;
}