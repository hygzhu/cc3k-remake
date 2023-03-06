#ifndef GAME
#define GAME


#include <SDL.h>
#include "map.h"

class Game
{
public:
    Game(/* args */);
    ~Game();
private:
    void render();
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    Map m_map;
};


#endif