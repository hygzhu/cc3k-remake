#include "rectangularsprite.h"
#include <iostream>

RectangularSprite::RectangularSprite(Rectangle rect, RGBA rgba): m_rect(rect), m_color(rgba){
}

void RectangularSprite::render(Renderer renderer, Point p, float xtrans, float ytrans, Point baseviewp, Point relativeviewp, Rectangle viewbox)
{

    //m_rect.print();
    Rectangle m_rect_intersection = Rectangle(p.getX() + m_rect.getX(), p.getY() + m_rect.getY(), m_rect.getWidth(), m_rect.getHeight());
    m_rect_intersection = m_rect_intersection.getIntersection(viewbox);

    Rectangle rect(
    static_cast<int>((m_rect_intersection.getX()-baseviewp.getX())*xtrans) + relativeviewp.getX(), 
    static_cast<int>((m_rect_intersection.getY()-baseviewp.getY())*ytrans) + relativeviewp.getY(),
    static_cast<int>(m_rect_intersection.getWidth()*xtrans), 
    static_cast<int>(m_rect_intersection.getHeight()*ytrans));

    renderer.renderRectangle(rect, m_color);
}