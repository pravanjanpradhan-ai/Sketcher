#include "pch.h"
#include "Circle.h"
#include <cmath>
#include "Line.h"

Circle::Circle(Point p1,Point p2) : Shape("Circle"),p1(p1), p2(p2),l1(p1,p2) {  
   radius=l1.length();
}

const int numPoints = 800;
const double angleStep = 2 * 3.14 / numPoints;

double Circle::area() const {
    return 3.14159 * radius * radius;
}

double Circle::perimeter() const {
    return 2 * 3.14159 * radius;
}
std::vector<Point> Circle::getCoordinates() const {
    std::vector<Point> coords;
    for (int i = 0; i <= numPoints; ++i) {
        double angle = i * angleStep;
        double x = p1.x + radius * cos(angle);
        double y = p1.y + radius * sin(angle);
        Point p(x,y);
        coords.push_back(p);
    }
    return coords;
}