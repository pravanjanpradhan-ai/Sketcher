#include "pch.h"
#include "Line.h"
// #include "Point.h"
#include <cmath>


Line::Line(Point p1,Point p2): Shape("Line"), p1(p1),p2(p2) {}


double Line::length() const{
    double l = std::sqrt((std::pow(p2.x-p1.x,2)+(std::pow(p2.y-p1.y,2))));
    return l;
}
double Line::perimeter() const {
    return  length();
}

double Line::area() const {
    
    return 0;
}
 std::vector<Point> Line::getCoordinates() const{
    std::vector<Point> coords;
    coords.push_back(p1);
    coords.push_back(p2);
    return coords;
}