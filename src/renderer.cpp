#include "renderer.h"
#include <SDL_image.h>
#include <iostream>

Renderer::Renderer(
        SDL_Renderer* renderer,
        Rectangle screen,
        Rectangle screen_window,
        Rectangle game_window):
        m_renderer(renderer),
        m_screen(screen),
        m_screen_window(screen_window),
        m_game_window(game_window)
{}

void Renderer::renderRectangle(Rectangle rect, RGBA rgba){

    Rectangle rect_intersection = rect.getIntersection(m_game_window);
    float window_ratio_width = m_game_window.getWidth()*1.0/m_screen_window.getWidth();
    float window_ratio_height = m_game_window.getHeight()*1.0/m_screen_window.getHeight();

    Rectangle rectMapped(
    static_cast<int>((rect_intersection.getX()-m_game_window.getX())/window_ratio_width) + m_screen_window.getX(), 
    static_cast<int>((rect_intersection.getY()-m_game_window.getY())/window_ratio_height) + m_screen_window.getY(),
    static_cast<int>(rect_intersection.getWidth()/window_ratio_width), 
    static_cast<int>(rect_intersection.getHeight()/window_ratio_height));

    

    SDL_Rect newRect = { 
        rectMapped.getX(),
        rectMapped.getY(),
        rectMapped.getWidth(),
        rectMapped.getHeight()
    };

    SDL_SetRenderDrawColor(m_renderer, rgba.red, rgba.green, rgba.blue, rgba.alpha);
    SDL_RenderFillRect(m_renderer, &newRect);
}