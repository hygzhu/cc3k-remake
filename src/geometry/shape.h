
#ifndef SHAPE_H
#define SHAPE_H

#include <utility>
#include <string>

class Shape {
public:
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
};

#endif // Rectangle_H