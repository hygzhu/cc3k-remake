
#include "player.h"
#include <iostream>


Player::Player(int size, RGBA color): Entity(0, 0, size, color) {}



void Player::printEntityType(){
    std::cout<<"Player " << getRectangle().toString() <<  std::endl;
}