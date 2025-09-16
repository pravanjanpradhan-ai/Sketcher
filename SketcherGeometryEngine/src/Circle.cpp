#include "pch.h"
#include "Circle.h"
#include "Line.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

Circle::Circle(const Point &center, const Point &onCircle)
    : Shape("Circle"), p1(center), p2(onCircle)
{
    if (p1.x == p2.x && p1.y == p2.y)
    {
        throw std::invalid_argument("Center and circumference point cannot be the same.");
    }
}

double Circle::radius() const
{
    Line l(p1, p2);
    return l.length();
}

std::vector<Point> Circle::getPoints() const
{
    std::vector<Point> points;
    points.push_back(p1);
    points = getOnCirclePoint();
    return points;
}

Point Circle::getCenter()
{
    return p1;
}

std::vector<Point> Circle::getOnCirclePoint() const
{
    std::vector<Point> points;
    int angle = 360 / 36;
    double rad = 0;

    for (int i = 0; i <= 36; i++)
    {
        double x = p1.x + radius() * cos(rad);
        double y = p1.y + radius() * sin(rad);
        Point p(x, y);
        points.push_back(p);
        rad = rad + (angle * 3.14) / 180.0;
    }

    return points;
}

double Circle::area() const
{
    double r = radius();
    return 3.14 * r * r;
}

double Circle::circumference() const
{
    return 2 * 3.14 * radius();
}