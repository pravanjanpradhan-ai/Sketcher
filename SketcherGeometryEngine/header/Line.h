#pragma once
#include "Shape.h"
#include "Point.h"
#include "FileWrite.h"

class Line : public Shape {
private:
    Point p1;
    Point p2;

public:
    Line(Point p1,Point p2);
    double length() const;
    double area() const override;
    double perimeter() const override;
    std::vector<Point> getCoordinates() const override;
};