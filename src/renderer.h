#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "graphics/rgba.h"
#include "geometry/rectangle.h"

class Renderer{
public:
    Renderer(SDL_Renderer* renderer);
    void renderRectangle(Rectangle rect, RGBA rgba);
private:
    SDL_Renderer* m_renderer;

};

#endif