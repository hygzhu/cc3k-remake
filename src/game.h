#ifndef GAME
#define GAME

#include "map.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <memory>

class Game {
public:
  Game(/* args */);
  int start();
  ~Game();

private:
  void render();
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  std::shared_ptr<Map> m_map;
};

#endif