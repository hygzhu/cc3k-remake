// BoundingRectangle.h
#ifndef BOUNDINGRECTANGLE_H
#define BOUNDINGRECTANGLE_H

#include <utility>

class BoundingRectangle {
public:
    BoundingRectangle(int x, int y, int width, int height);
    bool isCollidingWith(const BoundingRectangle& other) const;
    BoundingRectangle getIntersection(const BoundingRectangle& other) const;

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    std::pair<int,int> getCenterPoint();
    std::pair<int,int> getClosestPointTo(std::pair<int,int> startPoint);



private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

#endif // BOUNDINGRECTANGLE_H