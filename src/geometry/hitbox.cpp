#include "hitbox.h"


Hitbox::Hitbox(){

}

Hitbox::Hitbox(Rectangle rect){
    m_rectangles.push_back(rect);
}

Hitbox::Hitbox(std::vector<Rectangle> rectangles){
    m_rectangles = rectangles;
}

bool Hitbox::collidesWith(const Hitbox& other){
    for(const auto otherRect : other.m_rectangles ){
        for(const auto thisRect : m_rectangles){
            if(otherRect.isCollidingWith(thisRect)){
                return true;
            }
        }
    }
    return false;
}