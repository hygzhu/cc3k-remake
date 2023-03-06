
#include "player.h"
#include <iostream>


Player::Player(int x, int y, int size): x(x), y(y), size(size) {}


void Player::move(int dx, int dy) {
    x += dx;
    y += dy;
}


int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}
int Player::getSize() const {
    return size;
}