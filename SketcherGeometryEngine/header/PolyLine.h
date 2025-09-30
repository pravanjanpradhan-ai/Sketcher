#pragma once
#include "Exports.h"
#include "Shape.h"
#include "Point.h"
#include <vector>

class SKETCHERGEOMETRYENGINE_API PolyLine : public Shape {
private:
    std::vector<Point> vertices;

public:
    // Construct from list of points
    PolyLine(const std::vector<Point>& pts);

    // Length of polyline (sum of segment lengths)
    double perimeter() const override;

    // Area for open polyline is zero
    double area() const override;

    // Return coordinates in order
    std::vector<Point> getCoordinates() const override;
};
