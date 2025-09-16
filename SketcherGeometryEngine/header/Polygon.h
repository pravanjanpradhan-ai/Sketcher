#pragma once
#include "Shape.h"
#include "Point.h"
#include "FileWrite.h"

class Polygon : public Shape { // Inheritance
private:
    int sides;
    Point p1;

public:
    Polygon(Point p1,int sides);

    double area() const override;       // Polymorphism
    double perimeter() const override;
    std::vector<Point> getCoordinates() const override;  // Polymorphism
};
