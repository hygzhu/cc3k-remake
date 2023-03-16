#include "hitbox.h"
#include <iostream>

Hitbox::Hitbox(){

}

Hitbox::Hitbox(Rectangle rect, Point p): m_point(p){
    m_rectangles.push_back(rect);
}

Hitbox::Hitbox(std::vector<Rectangle> rectangles, Point p): m_point(p) {
    m_rectangles = rectangles;
}

Rectangle Hitbox::relativeRectangle(Rectangle rect) const{
    // Get the relative rectangle to the hitbox location
    Rectangle relativeRect(rect.getX()+ m_point.getX() ,rect.getY()+ m_point.getY(), rect.getWidth(), rect.getHeight() );
    return relativeRect;
}

bool Hitbox::collidesWith(const Hitbox& other){
    for(const auto otherRect : other.m_rectangles ){
        for(const auto thisRect : m_rectangles){
            if(other.relativeRectangle(otherRect).isCollidingWith(relativeRectangle(thisRect))){
                return true;
            }
        }
    }
    return false;
}


bool Hitbox::collidesWith(const Rectangle& other){
    for(const auto thisRect : m_rectangles){
        if(other.isCollidingWith(relativeRectangle(thisRect))){
            return true;
        }
    }
    return false;
}


bool Hitbox::collidesWith(const Point& other){
    for(const auto thisRect : m_rectangles){
        if(relativeRectangle(thisRect).isCollidingWithPoint(other)){
            return true;
        }
    }
    return false;
}


void Hitbox::setPoint(Point p){
    m_point = p;
}

void Hitbox::printHitbox(){

    std::cout << "Hitbox: \n";
    for(const auto thisRect : m_rectangles){
        std::cout << relativeRectangle(thisRect).toString() << " \n";
    }
    std::cout << std::endl;
}


Point Hitbox::getPoint(){
    return m_point;
}