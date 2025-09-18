#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Point.h"
#include "FileWrite.h"
#include "Line.h"

class SKETCHERGEOMETRYENGINE_API Circle : public Shape { // Inheritance
private:
    double radius;
    Point p1;
    Point p2;
    Line l1;

public:
    Circle(Point p1,Point p2);

    double area() const override;       // Polymorphism
    double perimeter() const override;
    std::vector<Point> getCoordinates() const override;  // Polymorphism
};
