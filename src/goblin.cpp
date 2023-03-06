#include "goblin.h"

Goblin::Goblin(int x, int y)
    : x(x), y(y) {}

void Goblin::move(int dx, int dy) {
    x += dx;
    y += dy;
}

int Goblin::getX() const {
    return x;
}

int Goblin::getY() const {
    return y;
}
