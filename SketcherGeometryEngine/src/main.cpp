#include <iostream>
#include <vector>
#include <string>
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "FileWriter.h"
#include "GeometryCreater.h"
#include "Polygon.h"

int main()
{
    GeometryCreater creater;
    creater.createGeometry();

    std::cout << "Click Enter to make your file";
    std::cin.get();
    std::cin.get();

    return 0;
}