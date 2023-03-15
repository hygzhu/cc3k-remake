#ifndef HITBOX_H
#define HITBOX_H

#include <vector>
#include "rectangle.h"

class Hitbox{
public:
    Hitbox();
    Hitbox(Rectangle rect);
    Hitbox(std::vector<Rectangle> rectangles);
    bool collidesWith(const Hitbox& other);

private:
    std::vector<Rectangle> m_rectangles;
};

#endif