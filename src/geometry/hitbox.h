#ifndef HITBOX_H
#define HITBOX_H

#include <vector>
#include "rectangle.h"
#include "point.h"

class Hitbox{
public:
    Hitbox();
    Hitbox(Rectangle rect, Point p);
    Hitbox(std::vector<Rectangle> rectangles, Point p);
    bool collidesWith(const Hitbox& other);
    bool collidesWith(const Rectangle& other);
    bool collidesWith(const Point& other);
    void setPoint(Point p);
    Point getPoint();
    void printHitbox();

private:
    Rectangle relativeRectangle(Rectangle rect) const;
    std::vector<Rectangle> m_rectangles;
    Point m_point;
};

#endif