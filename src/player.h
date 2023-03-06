#ifndef PLAYER
#define PLAYER


#include <SDL.h>

#include <SDL.h>

class Player {
public:
    Player(SDL_Renderer* renderer, int x, int y, int size);

    void render();

    void move(int dx, int dy);

private:
    SDL_Renderer* renderer;
    int x;
    int y;
    int size;
};


#endif
