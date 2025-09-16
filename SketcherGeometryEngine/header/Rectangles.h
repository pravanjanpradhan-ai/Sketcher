#pragma once
#include "framework.h"
#include "Shape.h"
#include "Point.h"

class Rectangles : public Shape
{
private:
    Point p1;
    Point p3;
    Point p2;
    Point p4;

public:
    Rectangles(const Point& a, const Point& b);
    ~Rectangles() {};
    double width() const;
    double height() const;
    std::vector<Point> getPoints() const override;

    // Extra:
    std::pair<double, double> diagonal() const;
    double perimeter() const;
    double area() const;
};
