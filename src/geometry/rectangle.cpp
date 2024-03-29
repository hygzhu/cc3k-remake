#include "rectangle.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

Rectangle::Rectangle(int x, int y, int width, int height)
    : m_x(x), m_y(y), m_width(width), m_height(height) {}

Rectangle::Rectangle(Point p, int width, int height)
    : m_x(p.getX()), m_y(p.getY()), m_width(width), m_height(height) {}

Rectangle::~Rectangle() {}

bool Rectangle::isCollidingWith(const Rectangle &other) const {
  return (m_x + m_width > other.m_x && m_x < other.m_x + other.m_width &&
          m_y + m_height > other.m_y && m_y < other.m_y + other.m_height);
}

bool Rectangle::isCollidingWithPoint(const Point &p) const {
  return (m_x + m_width >= p.getX() && m_x <= p.getX() &&
          m_y + m_height >= p.getY() && m_y <= p.getY());
}

Rectangle Rectangle::getIntersection(const Rectangle &other) const {
  int x1 = std::max(m_x, other.m_x);
  int y1 = std::max(m_y, other.m_y);
  int x2 = std::min(m_x + m_width, other.m_x + other.m_width);
  int y2 = std::min(m_y + m_height, other.m_y + other.m_height);
  int width = x2 - x1;
  int height = y2 - y1;
  if (width > 0 && height > 0) {
    return Rectangle(x1, y1, width, height);
  } else {
    // The two rectangles do not intersect
    return Rectangle(0, 0, 0, 0);
  }
}

int Rectangle::getX() const { return m_x; }

int Rectangle::getY() const { return m_y; }

int Rectangle::getWidth() const { return m_width; }

int Rectangle::getHeight() const { return m_height; }

void Rectangle::setX(int x) { m_x = x; }
void Rectangle::setY(int y) { m_y = y; }
void Rectangle::setWidth(int width) { m_width = width; }
void Rectangle::setHeight(int height) { m_height = height; }

Point Rectangle::getCoordinates() { return Point(m_x, m_y); }

Point Rectangle::getCenterPoint() {
  Point centerpoint;
  centerpoint.setX(m_x + (m_width / 2));
  centerpoint.setY(m_y + (m_width / 2));
  return centerpoint;
}

Point Rectangle::getClosestPointTo(Point startPoint) {
  int p_x = startPoint.getX();
  int p_y = startPoint.getY();

  bool insideX = m_x + m_width >= p_x && p_x >= m_x;
  bool insideY = m_y + m_height >= p_y && p_y >= m_y;
  bool pointInsideRectangle = insideX && insideY;

  int closestX = 0;
  int closestY = 0;

  if (!pointInsideRectangle) {

    // std::cerr << "OUTSIDE" <<std::endl;
    // Outside
    closestX = std::max(m_x, std::min(p_x, m_x + m_width));
    closestY = std::max(m_y, std::min(p_y, m_y + m_height));
  } else {
    // Inside
    //  std::cerr << "INSIDE" <<std::endl;
    int upDistance = std::abs(p_y - m_y);
    int downDistance = std::abs(m_y + m_height - p_y);
    int leftDistance = std::abs(p_x - m_x);
    int rightDistance = std::abs(m_x + m_width - p_x);

    // std::cerr << upDistance <<std::endl;
    // std::cerr << downDistance <<std::endl;
    // std::cerr << leftDistance <<std::endl;
    // std::cerr << rightDistance <<std::endl;

    Point upPoint(p_x, m_y);
    Point downPoint(p_x, m_y + m_height);
    Point leftPoint(m_x, p_y);
    Point rightPoint(m_x + m_width, p_y);

    int upLeftDistance =
        std::sqrt((upDistance * upDistance) + (leftDistance * leftDistance));
    int upRightDistance =
        std::sqrt((upDistance * upDistance) + (rightDistance * rightDistance));
    int downLeftDistance = std::sqrt((downDistance * downDistance) +
                                     (leftDistance * leftDistance));
    int downRightDistance = std::sqrt((downDistance * downDistance) +
                                      (rightDistance * rightDistance));

    // std::cerr << upLeftDistance <<std::endl;
    // std::cerr << upRightDistance <<std::endl;
    // std::cerr << downLeftDistance <<std::endl;
    // std::cerr << downRightDistance <<std::endl;

    if (upLeftDistance <= upRightDistance &&
        upLeftDistance <= downLeftDistance &&
        upLeftDistance <= downRightDistance) {
      if (upDistance <= leftDistance) {
        return upPoint;
      } else {
        return leftPoint;
      }
    } else if (upRightDistance <= downLeftDistance &&
               upRightDistance <= downRightDistance) {
      if (upDistance <= rightDistance) {
        return upPoint;
      } else {
        return rightPoint;
      }
    } else if (downLeftDistance <= downRightDistance) {
      if (downDistance <= leftDistance) {
        return downPoint;
      } else {
        return leftPoint;
      }
    } else {
      if (downDistance <= rightDistance) {
        return downPoint;
      } else {
        return rightPoint;
      }
    }
  }
  Point point(closestX, closestY);
  return point;
}

void Rectangle::print() const {
  std::cout << "( x:" << m_x << ", y: " << m_y << ", w: " << m_width
            << ", h: " << m_height << ")" << std::endl;
}

std::string Rectangle::toString() {
  return "( x:" + std::to_string(m_x) + ", y: " + std::to_string(m_y) +
         ", w: " + std::to_string(m_width) +
         ", h: " + std::to_string(m_height) + ")";
}

bool Rectangle::surrounds(const Rectangle &other) const {
  if (m_x <= other.getX() && other.getX() + other.getWidth() <= m_x + m_width &&
      m_y <= other.getY() &&
      other.getY() + other.getHeight() <= m_y + m_height) {
    return true;
  }
  return false;
}

double Rectangle::getArea() const { return m_width * m_height; }
double Rectangle::getPerimeter() const { return (m_height + m_width) * 2; }