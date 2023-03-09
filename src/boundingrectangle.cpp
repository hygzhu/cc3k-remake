#include "boundingrectangle.h"
#include <algorithm>
#include <utility>

BoundingRectangle::BoundingRectangle(int x, int y, int width, int height) 
    : m_x(x), m_y(y), m_width(width), m_height(height) {}

bool BoundingRectangle::isCollidingWith(const BoundingRectangle& other) const {
    return (m_x + m_width > other.m_x && m_x < other.m_x + other.m_width &&
            m_y + m_height > other.m_y && m_y < other.m_y + other.m_height);
}

BoundingRectangle BoundingRectangle::getIntersection(const BoundingRectangle& other) const {
    int x1 = std::max(m_x, other.m_x);
    int y1 = std::max(m_y, other.m_y);
    int x2 = std::min(m_x + m_width, other.m_x + other.m_width);
    int y2 = std::min(m_y + m_height, other.m_y + other.m_height);
    int width = x2 - x1;
    int height = y2 - y1;
    if (width > 0 && height > 0) {
        return BoundingRectangle(x1, y1, width, height);
    }
    else {
        // The two rectangles do not intersect
        return BoundingRectangle(0, 0, 0, 0);
    }
}

int BoundingRectangle::getX() const {
    return m_x;
}

int BoundingRectangle::getY() const {
    return m_y;
}

int BoundingRectangle::getWidth() const {
    return m_width;
}

int BoundingRectangle::getHeight() const {
    return m_height;
}


void BoundingRectangle::setX(int x){
    m_x = x;
}
void BoundingRectangle::setY(int y){
    m_y = y;
}
void BoundingRectangle::setWidth(int width){
    m_width = width;
}
void BoundingRectangle::setHeight(int height){
    m_height = height;
}


std::pair<int,int> BoundingRectangle::getCenterPoint(){
    std::pair<int,int> centerPoint;
    centerpoint_first = m_x + (m_width/2);
    centerpoint_second = m_y + (m_width/2);
    return centerPoint;
}


std::pair<int,int> BoundingRectangle::getClosestPointTo(std::pair<int,int> startPoint){

    int point_x = startpoint_first;
    int point_y = startpoint_second;

       // Find the closest point on the left edge of the rectangle
    int closestX = m_x;
    int closestY = point_y;
    if (point_y < m_y) {
        closestY = m_y;
    } else if (point_y > m_y + m_height) {
        closestY = m_y + m_height;
    }

    // Find the closest point on the right edge of the rectangle
    if (point_x > m_x + m_width) {
        closestX = m_x + m_width;
    } else if (point_x > m_x) {
        closestX = point_x;
    }

    // Find the closest point on the top edge of the rectangle
    if (point_y < m_y) {
        closestY = m_y;
    } else if (point_y > m_y + m_height ) {
        closestY = m_y + m_height;
    }

    // Find the closest point on the bottom edge of the rectangle
    if (point_x < m_x) {
        closestX = m_x;
    } else if (point_x < m_x + m_width && point_y > m_y + m_height) {
        closestY = m_y + m_height;
    }

    // Calculate the distance between the closest point and the given point
    double distance = sqrt(pow(point_x - closestX, 2) + pow(point_y - closestY, 2));


    // TODO: Logic for when point is inside box

    // Return the closest point on the rectangle
    return {closestX, closestY};
}