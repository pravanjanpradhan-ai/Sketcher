#include "pch.h"
#include "Triangle.h"
#include "Line.h"
#include <cmath>

Triangle::Triangle(Point p1,Point p2,Point p3)
    : Shape("Triangle"), p1(p1),p2(p2),p3(p3)
    {
        Line l1(p1,p3);
        Line l2(p2,p3);
        Line l3(p1,p2);
        double sideA = l1.length();
        double sideB = l2.length();
        double sideC = l3.length();
    }
double Triangle::perimeter() const {  
    return sideA+sideB+sideC;
}

double Triangle::area() const {
    // Heron's formula
    double s = perimeter() / 2.0;
    return std::sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
}
std::vector<Point> Triangle::getCoordinates() const  {
    std::vector<Point> coords;
    coords.push_back(p1); 
    coords.push_back(p2); 
    coords.push_back(p3); 
    return coords;
}