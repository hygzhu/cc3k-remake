#include "rectangularsprite.h"
#include <iostream>

RectangularSprite::RectangularSprite(Rectangle rect, RGBA rgba)
    : m_rect(rect), m_color(rgba) {}

void RectangularSprite::render(Renderer renderer, Point p) {

  // m_rect.print();
  Rectangle spriteLocation = m_rect;
  spriteLocation.setX(m_rect.getX() + p.getX());
  spriteLocation.setY(m_rect.getY() + p.getY());

  renderer.renderRectangle(spriteLocation, m_color);
}