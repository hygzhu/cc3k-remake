#include "point.h"
#include <cmath>

Point::Point() : m_x(0.0), m_y(0.0) {}

Point::Point(int x, int y) : m_x(x), m_y(y) {}

Point::Point(const Point& other) : m_x(other.m_x), m_y(other.m_y) {} // copy constructor

bool Point::operator==(const Point& other) const {
    return (m_x == other.m_x) && (m_y == other.m_y);
}

int Point::getX() const {
    return m_x;
}

int Point::getY() const {
    return m_y;
}

void Point::setX(int x) {
    m_x = x;
}

void Point::setY(int y) {
    m_y = y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.m_x << ", " << point.m_y << ")";
    return os;
}

void Point::print() const {
    std::cout << "(" << m_x << ", " << m_y << ")" << std::endl;
}

double Point::distanceTo(const Point& other) const {
    int dx = m_x - other.getX();
    int dy = m_y - other.getY();
    return std::sqrt(dx * dx + dy * dy);
}


std::string Point::toString()
{
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}