#include "game.h"
#include "entity/entityfactory.h"
// Using SDL, SDL_image, standard IO, and strings
#include "renderer.h"
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <utility>

// Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Set up the timer and frame rate
Uint32 lastFrameTime = SDL_GetTicks();
const Uint32 frameInterval = 16; // 60 fps

Game::Game(/* args */) {

  SDL_Init(SDL_INIT_VIDEO);
  m_window =
      SDL_CreateWindow("CC3K", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}

int Game::start() {

  
  bool quit = false;
  
  // if(!menu()){
  //   return 0;
  // }

  return gameplay();

}

void Game::renderGame() {

  const int RENDER_WIDTH = 1280;
  const int RENDER_HEIGHT = 720;
  const int RENDER_X = (SCREEN_WIDTH / 2) - (RENDER_WIDTH / 2);
  const int RENDER_Y = (SCREEN_HEIGHT / 2) - (RENDER_HEIGHT / 2);

  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);

  Rectangle viewbox = m_map->getViewBox();
  const int realx = viewbox.getX();
  const int realy = viewbox.getY();

  Renderer game_window_renderer(
      m_renderer, Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
      Rectangle(RENDER_X, RENDER_Y, RENDER_WIDTH, RENDER_HEIGHT), viewbox);

  // Render all entities in viewbox
  for (const auto &entity : m_map->getViewboxStaticEntities()) {
    entity->getSprite()->render(game_window_renderer, entity->getPoint());
  }
  for (const auto &entity : m_map->getViewboxMovingEntities()) {
    entity->getSprite()->render(game_window_renderer, entity->getPoint());
  }
  // Render GUI
  auto status = m_map->getPlayer()->getStatus();
  SDL_Rect hpBar = {20, 20, static_cast<int>(2 * status.getCurrHp()), 20};
  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(m_renderer, &hpBar);
  SDL_Rect mpBar = {20, 50, static_cast<int>(2 * status.getCurrMp()), 20};
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(m_renderer, &mpBar);

  SDL_RenderPresent(m_renderer);
}


void Game::renderMenu() {

  const int RENDER_WIDTH = 1280;
  const int RENDER_HEIGHT = 720;
  const int RENDER_X = (SCREEN_WIDTH / 2) - (RENDER_WIDTH / 2);
  const int RENDER_Y = (SCREEN_HEIGHT / 2) - (RENDER_HEIGHT / 2);

  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);

  Rectangle viewbox = Rectangle(0,0,RENDER_WIDTH,RENDER_HEIGHT);

  Renderer game_window_renderer(
      m_renderer, Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
      Rectangle(RENDER_X, RENDER_Y, RENDER_WIDTH, RENDER_HEIGHT), viewbox);


  SDL_RenderPresent(m_renderer);
}

Game::~Game() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}


int Game::menu(){
  

  // m_map = std::make_shared<Menu>();

  std::cout << "menu start" << std::endl;
  SDL_Event event;
  const int fps = 60;
  const int frameDelay = 1000 / fps;
  Uint32 frameStart;
  int frameTime;
  int ticks = 0;

  bool downKeys[SDL_NUM_SCANCODES] = {false};
  bool quit = false;
  // core menu loop
    while (!quit) {
    frameStart = SDL_GetTicks();

    const int speed = 160;
    std::pair<int, int> new_location;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        return 0;
      case SDL_KEYDOWN:
        downKeys[event.key.keysym.scancode] = true;
        break;
      case SDL_KEYUP:
        downKeys[event.key.keysym.scancode] = false;
        break;
      }
    }
    if (downKeys[SDL_SCANCODE_R]) {
      return true;
    }
    if (downKeys[SDL_SCANCODE_A]) {
    }
    if (downKeys[SDL_SCANCODE_D]) {
    }
    if ((!downKeys[SDL_SCANCODE_D] && !downKeys[SDL_SCANCODE_A]) ||
        downKeys[SDL_SCANCODE_D] && downKeys[SDL_SCANCODE_A]) {
    }
    if (downKeys[SDL_SCANCODE_W]) {
    }
    if (downKeys[SDL_SCANCODE_S]) {
    }
    if ((!downKeys[SDL_SCANCODE_W] && !downKeys[SDL_SCANCODE_S]) ||
        downKeys[SDL_SCANCODE_W] && downKeys[SDL_SCANCODE_S]) {
    }

    renderMenu();

    // Control game loop timing
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      ticks++;
      SDL_Delay(frameDelay - frameTime);
    }
    if (ticks == fps) {
      ticks = 0;
    }
  }
  return 0;
}

int Game::gameplay(){
  

  std::cout << "Game start" << std::endl;
  int max_rooms = 20;
  SDL_Event event;
  const int fps = 60;
  const int frameDelay = 1000 / fps;
  Uint32 frameStart;
  int frameTime;
  int ticks = 0;
  auto player = EntityFactory::createPlayer();
  m_map = std::make_shared<Map>(player, max_rooms, 40, 35);
  bool downKeys[SDL_NUM_SCANCODES] = {false};
  bool quit = false;
  // core game loop
    while (!quit) {

    if (!player->getStatus().isAlive()) {
      // player died
      return 1;
    }

    frameStart = SDL_GetTicks();

    const int speed = 160;
    std::pair<int, int> new_location;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        return 0;
      case SDL_KEYDOWN:
        downKeys[event.key.keysym.scancode] = true;
        break;
      case SDL_KEYUP:
        downKeys[event.key.keysym.scancode] = false;
        break;
      }
    }
    if (downKeys[SDL_SCANCODE_R]) {
      return true;
    }
    if (downKeys[SDL_SCANCODE_A]) {
      player->getMovement()->getAccelX() = -speed;
    }
    if (downKeys[SDL_SCANCODE_D]) {
      player->getMovement()->getAccelX() = speed;
    }
    if ((!downKeys[SDL_SCANCODE_D] && !downKeys[SDL_SCANCODE_A]) ||
        downKeys[SDL_SCANCODE_D] && downKeys[SDL_SCANCODE_A]) {
      player->getMovement()->getAccelX() = 0;
    }
    if (downKeys[SDL_SCANCODE_W]) {
      player->getMovement()->getAccelY() = -speed;
    }
    if (downKeys[SDL_SCANCODE_S]) {
      // Move player down
      player->getMovement()->getAccelY() = speed;
    }
    if ((!downKeys[SDL_SCANCODE_W] && !downKeys[SDL_SCANCODE_S]) ||
        downKeys[SDL_SCANCODE_W] && downKeys[SDL_SCANCODE_S]) {
      player->getMovement()->getAccelY() = 0;
    }

    // Update all movable entity location
    double frame_delay = static_cast<double>(frameDelay) / 1000;
    m_map->updateAllMovableEntityLocations(frame_delay);

    renderGame();

    // Control game loop timing
    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime) {
      ticks++;
      SDL_Delay(frameDelay - frameTime);
    }

    if (ticks == fps) {
      ticks = 0;
      std::cout << "Map entities " << m_map->getAllEntities().size()
                << std::endl;
    }
  }
  return 0;
}