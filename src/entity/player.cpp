
#include "player.h"
#include <iostream>


Player::Player(int size, RGBA color): Entity(0, 0, size, color) {}


void Player::move(int dx, int dy) {
    x_ = dx;
    y_ = dy;
}

void Player::printEntityType(){
    std::cout<<"Player" << std::endl;
}