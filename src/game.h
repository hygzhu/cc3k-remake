#ifndef GAME
#define GAME

#include "map.h"
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