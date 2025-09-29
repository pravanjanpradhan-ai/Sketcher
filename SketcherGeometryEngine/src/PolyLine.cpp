#include "pch.h"
#include "PolyLine.h"
#include <cmath>

PolyLine::PolyLine(const std::vector<Point>& pts)
    : Shape("PolyLine"), vertices(pts)
{
}

double PolyLine::perimeter() const {
    double total = 0.0;
    if (vertices.size() < 2) return 0.0;
    for (size_t i = 0; i + 1 < vertices.size(); ++i) {
        double dx = vertices[i + 1].x - vertices[i].x;
        double dy = vertices[i + 1].y - vertices[i].y;
        total += std::hypot(dx, dy);
    }
    return total;
}

double PolyLine::area() const {
    return 0.0; // open polyline has no area
}

std::vector<Point> PolyLine::getCoordinates() const {
    return vertices;
}
