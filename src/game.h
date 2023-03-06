#ifndef GAME
#define GAME


#include <SDL.h>
#include "map.h"
#include <memory>

class Game
{
public:
    Game(/* args */);
    ~Game();
private:
    void render();
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::shared_ptr<Map> m_map;
};


#endif