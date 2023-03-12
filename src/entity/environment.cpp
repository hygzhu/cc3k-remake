#include "environment.h"
#include <iostream>

Environment::Environment(int x, int y) : Entity(x, y, 1, { 128, 128, 128, 255 }) {}

void Environment::move(int dx, int dy) {
    // Environments don't move, so do nothing
}

void Environment::printEntityType(){
    //std::cout<<"Environment" << std::endl;
}