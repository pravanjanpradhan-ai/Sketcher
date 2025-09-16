#include "pch.h"
#include "Polygon.h"
#include <cmath>

Polygon::Polygon(Point p1,int sides) : Shape("Polygon"),p1(p1), sides(sides) {}

const int radius = 5;

double Polygon::area() const {
    return 3.14159 * radius * radius;
}

double Polygon::perimeter() const {
    return 2 * 3.14159 * radius;
}
std::vector<Point> Polygon::getCoordinates() const {
    std::vector<Point> coords;
    for (int i = 0; i <= sides; ++i) {
        double angleStep= 2 * M_PI / sides;
        double angle = i * angleStep;
        double x = p1.x + radius * cos(angle);
        double y = p1.y + radius * sin(angle);
        Point p(x,y);
        coords.push_back(p);
    }
    return coords;
}