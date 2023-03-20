// rectangle.h
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "shape.h"
#include <string>
#include <utility>

class Rectangle : public Shape {
public:
  Rectangle(int x, int y, int width, int height);
  Rectangle(Point p, int width, int height);
  ~Rectangle();

  virtual double getArea() const override;
  virtual double getPerimeter() const override;

  bool isCollidingWith(const Rectangle &other) const;
  bool surrounds(const Rectangle &other) const;
  bool isCollidingWithPoint(const Point &point) const;

  int getX() const;
  int getY() const;
  int getWidth() const;
  int getHeight() const;

  Rectangle getIntersection(const Rectangle &other) const;

  void setX(int x);
  void setY(int y);
  void setWidth(int width);
  void setHeight(int height);
  void print() const;

  Point getCoordinates();
  Point getCenterPoint();
  Point getClosestPointTo(Point startPoint);
  std::string toString();

private:
  int m_x;
  int m_y;
  int m_width;
  int m_height;
};

#endif // Rectangle_H