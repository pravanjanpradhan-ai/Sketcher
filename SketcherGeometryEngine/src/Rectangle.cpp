#include "pch.h"
#include "Rectangle.h"
#include "Point.h"

Rectangles::Rectangles(Point p1,Point p3)
    : Shape("Rectangle"), p1(p1),p3(p3),p2(p3.x,p1.y),p4(p1.x,p3.y) 
    {
        width = abs(p2.x-p1.x);
        height = abs(p3.y-p2.y);
    }

double Rectangles::area() const {
    return width * height;
}

double Rectangles::perimeter() const {
    return 2 * (width + height);
}
std::vector<Point> Rectangles::getCoordinates() const {
    std::vector<Point> coords;
    coords.push_back(p1);
    coords.push_back(p2);
    coords.push_back(p3);
    coords.push_back(p4);
    return coords;
}