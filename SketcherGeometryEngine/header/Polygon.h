#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>

class Polygon : public Shape
{ // Inheritance
private:
    Point p1;
    Point p2;
    int noSides;

public:
    Polygon(const Point &center, const Point &onPolygon, int s);
    ~Polygon() {};
    double sideLength() const;
    std::vector<Point> getPoints() const override;

    // Extra:
    Point getCenter();
    std::vector<Point> getOnPolygonPoint() const;
    double perimeter() const;
    double area() const;
};