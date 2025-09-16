#pragma once
#include <string>
#include "Point.h"


class GeometryEngine
{
public:
    GeometryEngine();
    ~GeometryEngine();

    void createline(Point p1, Point p2);
    //void createrectangle(Point p1, Point p3);
    void createtriangle(Point p1, Point p2, Point p3);
   // void createcircle(Point p1, Point p2);

    //void createpolygon(Point p1, int sides);
};
