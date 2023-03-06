
#include "player.h"
#include <iostream>


Player::Player(SDL_Renderer* renderer, int x, int y, int size) 
        : renderer(renderer), x(x), y(y), size(size) {}

void Player::render() {
    SDL_Rect rect = { x, y, size, size };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Player::move(int dx, int dy) {
    x += dx;
    y += dy;
}