#include "Rectangle.h"
#include "Line.h"
#include <stdexcept>

Rectangle::Rectangle(const Point &a, const Point &b)
    : Shape("Rectangle"), p1(a), p3(b), p2(p1.x, p3.y), p4(p3.x, p1.y)
{
    // Check if points are the same
    if (p1.x == p3.x && p1.y == p3.y)
    {
        throw std::invalid_argument("Points must not be identical.");
    }

    // Check if they form a line (same x or same y)
    if (p1.x == p3.x || p1.y == p3.y)
    {
        throw std::invalid_argument("Diagonal points must not be collinear.");
    }
}

double Rectangle::width() const
{
    Line l(p1, p4);
    return l.length();
}

double Rectangle::height() const
{
    Line l(p1, p2);
    return l.length();
}

std::vector<Point> Rectangle::getPoints() const
{
    std::vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    return points;
}

std::pair<double, double> Rectangle::diagonal() const
{
    Line l1(p1, p3);
    Line l2(p2, p4);
    return {l1.length(), l2.length()};
}

double Rectangle::perimeter() const
{
    Line l1(p1, p4);
    Line l2(p1, p2);
    return 2 * (l1.length() + l2.length());
}

double Rectangle::area() const
{
    Line l1(p1, p4);
    Line l2(p1, p2);
    return l1.length() * l2.length();
}