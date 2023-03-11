#include "point.h"
#include <cmath>

Point::Point() : m_x(0.0), m_y(0.0) {}

Point::Point(int x, int y) : m_x(x), m_y(y) {}

Point::Point(const Point& other) : m_x(other.m_x), m_y(other.m_y) {} // copy constructor

bool Point::operator==(const Point& other) const {
    return (m_x == other.m_x) && (m_y == other.m_y);
}


bool Point::operator!=(const Point& other) const {
    return (m_x != other.m_x) || (m_y != other.m_y);
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

int Point::manhattanDistanceFrom(Point b)
{
    return std::abs(m_x - b.getX()) + std::abs(m_y - b.getY());
}

std::vector<Point> Point::allPointsInManhattanDistanceAway(int n)
{
    // WARNING: THIS CODE IS VERY SLOW 
    std::vector<Point> ret;
    int startX = m_x - n;
    int startY = m_y - n;
    for(int i = 0; i < n*2; ++i){
        for(int j = 0; j < n*2; ++i){
            Point b(startX+i, startY+j);
            if(manhattanDistanceFrom(b) == n)
            {
                ret.push_back(b);
            }
        }
    }
    return ret;
}

std::vector<Point> Point::allPointsInEuclidianDistanceAway(int n){
    std::vector<Point> ret;
    int startX = m_x - n;
    int startY = m_y - n;
    for(int i = 0; i < n*2; ++i){

        Point top(startX+i, startY+0);
        Point bottom(startX+i, startY+(n*2));
        ret.push_back(top);
        ret.push_back(bottom);


        Point left(startX, startY+i);
        Point right(startX+(n*2), startY+i);
        ret.push_back(left);
        ret.push_back(right);
    }


    return ret;
}



bool Point::doLinesIntersect(Point p1, Point p2, Point q1, Point q2) {
    // Calculate slopes and y-intercepts of the two lines
    double m1 = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
    double b1 = p1.getY() - m1 * p1.getX();
    double m2 = (q2.getY() - q1.getY()) / (q2.getX() - q1.getX());
    double b2 = q1.getY() - m2 * q1.getX();

    // Check if the two lines are parallel
    if (m1 == m2) {
        return false;
    }

    // Calculate the intersection point of the two lines
    double x = (b2 - b1) / (m1 - m2);
    double y = m1 * x + b1;

    // Check if the intersection point lies on both line segments
    if (x >= std::min(p1.getX(), p2.getX()) && x <= std::max(p1.getX(), p2.getX()) &&
        x >= std::min(q1.getX(), q2.getX()) && x <= std::max(q1.getX(), q2.getX()) &&
        y >= std::min(p1.getY(), p2.getY()) && y <= std::max(p1.getY(), p2.getY()) &&
        y >= std::min(q1.getY(), q2.getY()) && y <= std::max(q1.getY(), q2.getY())) {
        return true;
    }

    return false;
}

void Point::getSlopeIntercept(Point p1, Point p2, double& slope, double& y_intercept)
{
    slope = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
    y_intercept = p1.getY() - slope * p1.getX();
}

// Function to find the point of intersection between two lines given their endpoints
Point Point::findIntersection(Point p1, Point p2, Point p3, Point p4) {
    double slope1, slope2, y_intercept1, y_intercept2;
    getSlopeIntercept(p1, p2, slope1, y_intercept1);
    getSlopeIntercept(p3, p4, slope2, y_intercept2);
    
    if (slope1 == slope2) {
        // lines are parallel or coincident
        return Point();  // special value to indicate no intersection
    }
    else {
        double x_int = (y_intercept2 - y_intercept1) / (slope1 - slope2);
        double y_int = slope1 * x_int + y_intercept1;
        //std::cout << x_int << " AND " << y_int << std::endl;
        return Point(x_int, y_int);
    }
}


std::vector<Point> Point::getSurroundingPoints()
{
    std::vector<Point> neighbours;
    int x = m_x, y = m_y;
    neighbours.push_back(Point(x, y+1)); // up
    neighbours.push_back(Point(x, y-1)); // down
    neighbours.push_back(Point(x-1, y)); // left
    neighbours.push_back(Point(x+1, y)); // right
    neighbours.push_back(Point(x+1, y+1));
    neighbours.push_back(Point(x+1, y-1));
    neighbours.push_back(Point(x-1, y+1));
    neighbours.push_back(Point(x-1, y-1));
    return neighbours;
}

std::vector<Point> Point::getCompassSurroundingPoints()
{
    std::vector<Point> neighbours;
    int x = m_x, y = m_y;
    neighbours.push_back(Point(x, y+1)); // up
    neighbours.push_back(Point(x, y-1)); // down
    neighbours.push_back(Point(x-1, y)); // left
    neighbours.push_back(Point(x+1, y)); // right
    return neighbours;
}