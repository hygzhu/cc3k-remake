#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

class Point {
public:
    Point();
    Point(int x, int y);
    Point(const Point& other); // copy constructor
    bool operator==(const Point& other) const; // equality operator
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    friend std::ostream& operator<<(std::ostream& os, const Point& point); // overload << operator for printing to std::ostream
    void print() const; // print method
    double distanceTo(const Point& other) const;
    std::string toString();
private:
    int m_x;
    int m_y;
};

#endif
