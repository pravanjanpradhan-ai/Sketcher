#pragma once
#include "Point.h"
#include "Shape.h"
#include "Exports.h"
#include <vector>
#include "FileWrite.h"

class SKETCHERGEOMETRYENGINE_API Polygons : public Shape {
private:
    std::vector<Point> vertices;

public:
    // Constructor that takes a list of points
    Polygons(const std::vector<Point>& pts);
    //Polygon(std::vector<Point> pts);   // <-- add by value

    double area() const override;
    double perimeter() const override;
    std::vector<Point> getCoordinates() const override;
};