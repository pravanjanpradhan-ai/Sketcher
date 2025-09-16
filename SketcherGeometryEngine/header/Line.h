#pragma once
#include "framework.h"
#include "Shape.h"
#include "Point.h"

class Line : public Shape
{ // Inheritance
private:
    Point p1;
    Point p2;

public:
    Line(const Point &a, const Point &b);
    ~Line() {};
    std::vector<Point> getPoints() const override;

    // Extra:
    double length() const;
    Point midPoint() const;
    double slope() const;
    static Point intersects(const Line &l1, const Line &l2);
};