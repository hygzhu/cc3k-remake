#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "graphics/rgba.h"
#include "geometry/rectangle.h"


// Renders objects in a predefined area on the screen
class Renderer{
public:
    Renderer(
        SDL_Renderer* renderer,
        Rectangle screen,
        Rectangle screen_window,
        Rectangle game_window
    );
    void renderRectangle(Rectangle rect, RGBA rgba);
private:
    SDL_Renderer* m_renderer;

    // Values associated to what is shown
    Rectangle m_screen;
    Rectangle m_screen_window;

    // Values associated with the game
    Rectangle m_game_window;

};

#endif