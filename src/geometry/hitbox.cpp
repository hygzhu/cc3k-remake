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

// TODO: Fix this to consider the case where a rectangle is covered by two others
bool Hitbox::surrounds(const Hitbox& other){

    // std::cout << "Surrounds?" << std::endl;
    // this->m_point.print();
    // printHitbox();
    // other.m_point.print();
    // other.printHitbox();
    for(const auto thisRect : m_rectangles){
        // check if surroundeds all
        for(const auto otherRect : other.m_rectangles){

            if(!this->relativeRectangle(thisRect).surrounds(other.relativeRectangle(otherRect))){

                // std::cout << "Nope" << std::endl;
                return false;
            }
        }
    }


    // std::cout << "Yes" << std::endl;
    return true;
}


void Hitbox::setPoint(Point p){
    m_point = p;
}

void Hitbox::printHitbox() const{

    std::cout << "Hitbox: \n";
    for(const auto thisRect : m_rectangles){
        std::cout << relativeRectangle(thisRect).toString() << " \n";
    }
    std::cout << std::endl;
}


std::string Hitbox::toString(){

    std::string ret = "";
    ret += "Hitbox: \n";
    for(const auto thisRect : m_rectangles){
        ret += relativeRectangle(thisRect).toString() + " \n";
    }
    
    ret += "\n";
    return ret;
}


Point Hitbox::getPoint(){
    return m_point;
}


Point Hitbox::getCenter(){
    int totalCenterX = 0;
    int totalCenterY = 0;

    for (Rectangle rect : m_rectangles) {
        Point center  = rect.getCenterPoint();
        totalCenterX += center.getX();
        totalCenterY += center.getY();
    }

    int averageCenterX = totalCenterX / m_rectangles.size();
    int averageCenterY = totalCenterY / m_rectangles.size();

    return Point(averageCenterX, averageCenterY);

}