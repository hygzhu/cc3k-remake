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
  int menu(); 
  int gameplay(); 
  void renderMenu();
  void renderGame();
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  std::shared_ptr<Map> m_map;
// std::shared_ptr<Menu> m_menu;
};

#endif