#pragma once
#include "Shape.h"
#include "Line.h"
#include "Point.h"

class Rectangle : public Shape
{
private:
    Point p1;
    Point p3;
    Point p2;
    Point p4;

public:
    Rectangle(const Point &a, const Point &b);
    ~Rectangle() {};
    double width() const;
    double height() const;
    std::vector<Point> getPoints() const override;

    // Extra:
    std::pair<double, double> diagonal() const;
    double perimeter() const;
    double area() const;
};