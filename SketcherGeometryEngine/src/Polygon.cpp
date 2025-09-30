#include "pch.h"
#include "Polygon.h"
#include <cmath>

// Constructor: forwards "Polygon" to base Shape
Polygons::Polygons(const std::vector<Point>& pts)
    : Shape("Polygon"), vertices(pts) {
}

double Polygons::area() const {
    // Shoelace formula for polygon area
    double A = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n; // wrap around
        A += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
    }
    return std::abs(A) / 2.0;
}

double Polygons::perimeter() const {
    double P = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double dx = vertices[j].x - vertices[i].x;
        double dy = vertices[j].y - vertices[i].y;
        P += std::sqrt(dx * dx + dy * dy);
    }
    return P;
}

std::vector<Point> Polygons::getCoordinates() const {
    return vertices;
}