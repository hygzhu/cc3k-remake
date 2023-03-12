#include "game.h"
#include "entity/player.h"
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
    m_map = std::make_shared<Map>(player,1,40,25);
    bool quit = false;
    SDL_Event event;

    const int fps = 60;
    const int frameDelay = 1000 / fps;
    Uint32 frameStart;
    int frameTime;

    bool downKeys[SDL_NUM_SCANCODES] = { false };
    while (!quit) {

        frameStart = SDL_GetTicks();

        const int speed = 250;
        std::pair<int,int> new_location;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    downKeys[event.key.keysym.scancode] = true;
                    break;
                case SDL_KEYUP:
                    downKeys[event.key.keysym.scancode] = false;
                    break;
            }
        }

        if (downKeys[SDL_SCANCODE_LEFT])
        {
            player->getAccelX() = -speed;
        }
        if (downKeys[SDL_SCANCODE_RIGHT])
        {
            
            player->getAccelX() = speed;
        }
        if((!downKeys[SDL_SCANCODE_RIGHT] && !downKeys[SDL_SCANCODE_LEFT])|| downKeys[SDL_SCANCODE_RIGHT] && downKeys[SDL_SCANCODE_LEFT]){
            player->getAccelX() = 0;
        }

        if (downKeys[SDL_SCANCODE_UP])
        {
            player->getAccelY() = -speed;
        }
        if (downKeys[SDL_SCANCODE_DOWN])
        {
            // Move player down

            player->getAccelY() = speed;
        }
        if((!downKeys[SDL_SCANCODE_UP] && !downKeys[SDL_SCANCODE_DOWN])||downKeys[SDL_SCANCODE_UP] && downKeys[SDL_SCANCODE_DOWN]){
            player->getAccelY() = 0;
        }

        // Update all movable entity location
        double frame_delay = static_cast<double>(frameDelay) / 1000;
        m_map->updateAllMovableEntityLocations(frame_delay);

        render();

        // Control game loop timing
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
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
