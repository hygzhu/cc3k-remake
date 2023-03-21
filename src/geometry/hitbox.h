#ifndef HITBOX_H
#define HITBOX_H

#include "point.h"
#include "rectangle.h"
#include <string>
#include <vector>
#include <memory>

class Hitbox {
public:
  Hitbox();
  Hitbox(const Hitbox& other);
  Hitbox(Rectangle rect, Point p);
  Hitbox(std::vector<Rectangle> rectangles, Point p);
  bool collidesWith(const Hitbox &other);
  bool collidesWith(const Rectangle &other);
  bool collidesWith(const Point &other);
  bool surrounds(const Hitbox &other);
  void setPoint(std::shared_ptr<Point> p);
  std::shared_ptr<Point> getPoint();
  Point getCenter();
  void printHitbox() const;
  std::string toString();

private:
  Rectangle relativeRectangle(Rectangle rect) const;
  std::vector<Rectangle> m_rectangles;
  std::shared_ptr<Point> m_point;
};

#endif