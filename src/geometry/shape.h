
#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <utility>

class Shape {
public:
  virtual ~Shape() {}
  virtual double getArea() const = 0;
  virtual double getPerimeter() const = 0;
};

#endif // Rectangle_H