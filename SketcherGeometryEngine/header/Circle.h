#pragma once
#include "framework.h"
#include "Shape.h"
#include "Point.h"
#include <vector>

class Circle : public Shape
{ // Inheritance
private:
    Point p1;
    Point p2;

public:
    Circle(const Point &center, const Point &onCircle);
    ~Circle() {};
    double radius() const;
    std::vector<Point> getPoints() const override;

    // Extra:
    Point getCenter();
    std::vector<Point> getOnCirclePoint() const;
    double area() const;
    double circumference() const;
};