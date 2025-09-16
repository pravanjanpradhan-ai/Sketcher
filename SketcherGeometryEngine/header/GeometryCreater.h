#pragma once
#include <vector>
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Polygon.h"

class GeometryCreater
{
public:
    GeometryCreater() {};
    ~GeometryCreater() {};

    void createGeometry();
};