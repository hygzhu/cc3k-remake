#include "rectangularsprite.h"
#include <iostream>

RectangularSprite::RectangularSprite(Rectangle rect, RGBA rgba): m_rect(rect), m_color(rgba){
}

void RectangularSprite::render(Renderer renderer, Point p, float xtrans, float ytrans, Point baseviewp, Point relativeviewp)
{

    //m_rect.print();
    Rectangle rect(
    static_cast<int>((p.getX() + m_rect.getX()-baseviewp.getX())*xtrans) + relativeviewp.getX(), 
    static_cast<int>((p.getY() + m_rect.getY()-baseviewp.getY())*ytrans) + relativeviewp.getY(),
    static_cast<int>(m_rect.getWidth()*xtrans), 
    static_cast<int>(m_rect.getHeight()*ytrans));

    renderer.renderRectangle(rect, m_color);
}