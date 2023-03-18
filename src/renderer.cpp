#include "renderer.h"
#include <SDL_image.h>

Renderer::Renderer(SDL_Renderer* renderer):m_renderer(renderer){}

void Renderer::renderRectangle(Rectangle rect, RGBA rgba){

    SDL_Rect newRect = { 
        rect.getX(),
        rect.getY(),
        rect.getWidth(),
        rect.getHeight()
    };

    SDL_SetRenderDrawColor(m_renderer, rgba.red, rgba.green, rgba.blue, rgba.alpha);
    SDL_RenderFillRect(m_renderer, &newRect);
}