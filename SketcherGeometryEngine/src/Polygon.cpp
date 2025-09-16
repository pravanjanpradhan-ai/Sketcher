#include "Polygon.h"
#include "Line.h"
#include "Triangle.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

Polygon::Polygon(const Point &center, const Point &onPolygon, int s)
    : Shape("Circle"), p1(center), p2(onPolygon), noSides(s)
{
    if (p1.x == p2.x && p1.y == p2.y)
    {
        throw std::invalid_argument("Center and Edge point cannot be the same.");
    }
    if (noSides < 3)
    {
        throw std::invalid_argument("Number os side must be greater than 2.");
    }
    if (noSides > 36)
    {
        throw std::invalid_argument("Number os side greater than 36 again give Circle.");
    }
}

double Polygon::sideLength() const
{
    Point a(getOnPolygonPoint()[0].x, getOnPolygonPoint()[0].y);
    Point b(getOnPolygonPoint()[1].x, getOnPolygonPoint()[1].y);
    Line l(a, b);
    return l.length();
}

std::vector<Point> Polygon::getPoints() const
{
    std::vector<Point> points;
    points.push_back(p1);
    points = getOnPolygonPoint();
    return points;
}

Point Polygon::getCenter()
{
    return p1;
}

std::vector<Point> Polygon::getOnPolygonPoint() const
{
    std::vector<Point> points;
    int angle = 360 / noSides;
    double rad = 0;
    Line l(p1, p2);

    for (int i = 0; i <= noSides; i++)
    {
        double x = p1.x + l.length() * cos(rad);
        double y = p1.y + l.length() * sin(rad);
        Point p(x, y);
        points.push_back(p);
        rad = rad + (angle * M_PI) / 180.0;
    }

    return points;
}

double Polygon::perimeter() const
{
    return noSides * sideLength();
}

double Polygon::area() const
{
    Point a(getOnPolygonPoint()[0].x, getOnPolygonPoint()[0].y);
    Point b(getOnPolygonPoint()[1].x, getOnPolygonPoint()[1].y);

    Triangle t(a, b, p1);
    double triangleArea = t.area();
    return noSides * triangleArea;
}