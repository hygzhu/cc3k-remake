#include "game.h"
#include "player.h"
//Using SDL, SDL_image, standard IO, and strings
#include <SDL_image.h>
#include <stdio.h>


//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Game::Game(/* args */)
{
 
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Move Square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Player square(renderer, 320, 240, 50);

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
                    square.move(0, -10);
                    break;
                case SDLK_DOWN:
                    square.move(0, 10);
                    break;
                case SDLK_LEFT:
                    square.move(-10, 0);
                    break;
                case SDLK_RIGHT:
                    square.move(10, 0);
                    break;
                }
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        square.render();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Game::~Game()
{
}
