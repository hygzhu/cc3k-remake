// rectangle.h
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <utility>
#include <string>
#include "point.h"
#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int width, int height);

    bool isCollidingWith(const Rectangle& other) const;
    bool surrounds(const Rectangle& other) const;
    bool isCollidingWithPoint(const Point& point) const;
    Rectangle getIntersection(const Rectangle& other) const;

    virtual double getArea() const override;
    virtual double getPerimeter() const override;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    Point getCenterPoint();
    Point getClosestPointTo(Point startPoint);
    void print() const; // new print method
    std::string toString();



private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

#endif // Rectangle_H