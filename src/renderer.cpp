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

    

    // std::cout << "-------" << std::endl;
    // Get part of the reactangle in the game that intersects with the game window
    Rectangle rect_intersection = rect.getIntersection(m_game_window);
    // rect.print();
    // m_game_window.print();
    // rect_intersection.print();
    // std::cout << "-------" << std::endl;

    // Map the game window to the screen window
    Rectangle rectMapped(
    static_cast<int>((rect_intersection.getX()-m_game_window.getX())) + m_screen_window.getX(), 
    static_cast<int>((rect_intersection.getY()-m_game_window.getY())) + m_screen_window.getY(),
    static_cast<int>(rect_intersection.getWidth()), 
    static_cast<int>(rect_intersection.getHeight()));

    

    SDL_Rect newRect = { 
        rectMapped.getX(),
        rectMapped.getY(),
        rectMapped.getWidth(),
        rectMapped.getHeight()
    };

    SDL_SetRenderDrawColor(m_renderer, rgba.red, rgba.green, rgba.blue, rgba.alpha);
    SDL_RenderFillRect(m_renderer, &newRect);
}