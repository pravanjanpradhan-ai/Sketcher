#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "FileWrite.h"



class SKETCHERGEOMETRYENGINE_API Triangle : public Shape {
private:
    Point p1;
    Point p2;
    Point p3;
    double sideA;
    double sideB;
    double sideC;

public:
    Triangle(Point p1,Point p2,Point p3);

    double area() const override;
    double perimeter() const override;
    std::vector<Point> getCoordinates() const override;
};