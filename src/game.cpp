#include "game.h"
#include "player.h"
//Using SDL, SDL_image, standard IO, and strings
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>


//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Game::Game(/* args */)
{
 
    SDL_Init(SDL_INIT_VIDEO);

    m_window = SDL_CreateWindow("CC3K", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    std::shared_ptr<Player> square = std::make_shared<Player>(320, 240, 50);

    m_map.setEntity(0,0,square);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    square->move(0, -10);
                    break;
                case SDLK_DOWN:
                    square->move(0, 10);
                    break;
                case SDLK_LEFT:
                    square->move(-10, 0);
                    break;
                case SDLK_RIGHT:
                    square->move(10, 0);
                    break;
                }
                break;
            }
        }

        render();

    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    // Render all entities
    for (const auto& row : m_map.getGrid()) {
        std::cout << "Looking in the rows" << std::endl;
        for (const auto& col : row) {
            std::cout << "Looking in the cols" << std::endl;
            for (const auto& entity : col) {
                std::cout << "Found one" << std::endl;
                SDL_Rect rect = { entity->getX(), entity->getY(), entity->getSize(), entity->getSize() };
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(m_renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(m_renderer);
}

Game::~Game()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
