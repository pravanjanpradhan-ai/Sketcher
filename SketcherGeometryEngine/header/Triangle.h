#pragma once
#include "framework.h"
#include "Shape.h"
#include "Point.h"

class Triangle : public Shape
{
private:
    Point p1;
    Point p2;
    Point p3;

public:
    Triangle(const Point &a, const Point &b, const Point &c);
    ~Triangle() {};
    std::vector<Point> getPoints() const override;

    // Extra:
    double lengthOfSide(const Point &a, const Point &b);
    double perimeter() const;
    double area() const;
};