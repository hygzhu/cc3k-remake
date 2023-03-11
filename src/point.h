#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>

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
    std::vector<Point> allPointsInManhattanDistanceAway(int n);
    std::vector<Point> allPointsInEuclidianDistanceAway(int n);
    int manhattanDistanceFrom(Point b);
    std::vector<Point> getSurroundingPoints();
    std::vector<Point> getCompassSurroundingPoints();

    struct HashFunction
    {
        size_t operator()(const Point& point) const
        {
        size_t xHash = std::hash<int>()(point.getX());
        size_t yHash = std::hash<int>()(point.getY()) << 1;
        return xHash ^ yHash;
        }
    };

    static bool doLinesIntersect(Point p1, Point p2, Point q1, Point q2);
    static Point findIntersection(Point p1, Point p2, Point p3, Point p4);
private:

    static void getSlopeIntercept(Point p1, Point p2, double& slope, double& y_intercept);

    int m_x;
    int m_y;


};

#endif
