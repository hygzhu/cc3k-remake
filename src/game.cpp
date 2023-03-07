#include "game.h"
#include "player.h"
//Using SDL, SDL_image, standard IO, and strings
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <utility>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Set up the timer and frame rate
Uint32 lastFrameTime = SDL_GetTicks();
const Uint32 frameInterval = 16; // 60 fps


Game::Game(/* args */)
{
 
    SDL_Init(SDL_INIT_VIDEO);
    m_window = SDL_CreateWindow("CC3K", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}


int Game::start()
{
    RGBA playerColor = { 255, 0, 0, 255 };
    std::shared_ptr<Player> player = std::make_shared<Player>(10, playerColor);
    m_map = std::make_shared<Map>(player);
    bool quit = false;
    SDL_Event event;

    while (!quit) {

        // Calculate the time since the last frame
        Uint32 currentFrameTime = SDL_GetTicks();
        Uint32 timeSinceLastFrame = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        const int speed = 15;
        std::pair<int,int> new_location;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    new_location = m_map->movableLocationCloseTo(0,-speed,player);
                    player->move(new_location.first, new_location.second);
                    break;
                case SDLK_DOWN:
                    new_location = m_map->movableLocationCloseTo(0,speed,player);
                    player->move(new_location.first, new_location.second);
                    break;
                case SDLK_LEFT:
                    new_location = m_map->movableLocationCloseTo(-speed,0,player);
                    player->move(new_location.first, new_location.second);
                    break;
                case SDLK_RIGHT:
                    new_location = m_map->movableLocationCloseTo(speed,0,player);
                    player->move(new_location.first, new_location.second);
                    break;
                case SDLK_r:
                    return 1;
                    break;
                }
                break;
            }
        }

        render();

        // Delay until the next frame
        Uint32 elapsedTime = SDL_GetTicks() - currentFrameTime;
        if (elapsedTime < frameInterval)
        {
            SDL_Delay(frameInterval - elapsedTime);
        }

    }
    return 0;
}

void Game::render()
{

    const int RENDER_WIDTH = 700;
    const int RENDER_HEIGHT = 700;
    const int RENDER_X = (SCREEN_WIDTH/2)- (RENDER_WIDTH/2);
    const int RENDER_Y = (SCREEN_HEIGHT/2)- (RENDER_HEIGHT/2);
    const float BLOCK_WIDTH = RENDER_WIDTH/ m_map->getWidth();
    const float BLOCK_HEIGHT = RENDER_HEIGHT/ m_map->getHeight();

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    BoundingRectangle viewbox = m_map->getViewBox();
    const int realx = viewbox.getX();
    const int realy = viewbox.getY();

    // Render all entities in viewbox
    for (const auto& entity : m_map->getViewboxEntities()) {
        SDL_Rect rect = { 
        static_cast<int>((entity->getX()-realx)*BLOCK_WIDTH) + RENDER_X, 
        static_cast<int>((entity->getY()-realy)*BLOCK_HEIGHT) + RENDER_Y,
        static_cast<int>(entity->getSize()*BLOCK_WIDTH), 
        static_cast<int>(entity->getSize()*BLOCK_HEIGHT)};
        RGBA entityColor = entity->getColor();
        SDL_SetRenderDrawColor(m_renderer, entityColor.red, entityColor.green, entityColor.blue, entityColor.alpha);
        SDL_RenderFillRect(m_renderer, &rect);
    }

    SDL_RenderPresent(m_renderer);
}

Game::~Game()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
