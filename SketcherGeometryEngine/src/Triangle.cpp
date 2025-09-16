#include "pch.h"
#include "Triangle.h"
#include "Line.h"
#include <cmath>
#include <stdexcept>

Triangle::Triangle(const Point &a, const Point &b, const Point &c)
    : Shape("Triangle"), p1(a), p2(b), p3(c)
{
    // Check if any two points are identical
    if ((p1.x == p2.x && p1.y == p2.y) || (p2.x == p3.x && p2.y == p3.y) || (p1.x == p3.x && p1.y == p3.y))
    {
        throw std::invalid_argument("Points must be distinct.");
    }

    // Check collinearity using area formula
    double area = (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0;
    if (area == 0)
    {
        throw std::invalid_argument("Points are collinear.");
    }
}

std::vector<Point> Triangle::getPoints() const
{
    std::vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    return points;
}

double Triangle::lengthOfSide(const Point &a, const Point &b)
{
    double abX = b.x - a.x;
    double abY = b.y - a.y;

    return sqrt(abX * abX + abY * abY);
}

double Triangle::perimeter() const
{
    Line A(p1, p2);
    Line B(p2, p3);
    Line C(p1, p3);
    return (A.length() + B.length() + C.length());
}

double Triangle::area() const
{
    Line A(p1, p2);
    Line B(p2, p3);
    Line C(p1, p3);

    double s = perimeter() / 2;
    return sqrt(s * (s - A.length()) * (s - B.length()) * (s - C.length()));
}