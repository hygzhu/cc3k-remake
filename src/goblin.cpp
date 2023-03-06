#include "goblin.h"
#include <iostream>

Goblin::Goblin(int x, int y) : Entity(x, y, 1, { 0, 128, 0, 255 }) {}

void Goblin::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}


void Goblin::printEntityType(){
    //std::cout<<"Goblin" << std::endl;
}