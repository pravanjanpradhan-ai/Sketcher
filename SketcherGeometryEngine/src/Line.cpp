#include "pch.h"
#include "Line.h"
#include <cmath>
#include <stdexcept>

Line::Line(const Point &a, const Point &b) : Shape("Line"), p1(a), p2(b)
{
    if (p1.x == p2.x && p1.y == p2.y)
    {
        throw std::invalid_argument("Two point cannot be the same.");
    }
}

std::vector<Point> Line::getPoints() const
{
    std::vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    return points;
}

double Line::length() const
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double Length = sqrt(dx * dx + dy * dy);
    return Length;
}

Point Line::midPoint() const
{
    double mx = (p1.x + p2.y) / 2;
    double my = (p1.y + p2.y) / 2;
    return Point(mx, my);
}

double Line::slope() const
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return dy / dx;
}

Point Line::intersects(const Line &l1, const Line &l2)
{
    double a1 = l1.p2.y - l1.p1.y;
    double b1 = l1.p1.x - l1.p2.x;
    double c1 = a1 * l1.p1.x + b1 * l1.p1.y;

    double a2 = l2.p2.y - l2.p1.y;
    double b2 = l2.p1.x - l2.p2.x;
    double c2 = a2 * l2.p1.x + b2 * l2.p1.y;

    double det = a1 * b2 - a2 * b1;

    if (det == 0)
    {
        throw std::runtime_error("Lines are parallel or coincident, no unique intersection.");
    }

    double x = (c1 * b2 - c2 * b1) / det;
    double y = (a1 * c2 - a2 * c1) / det;

    return Point(x, y);
}