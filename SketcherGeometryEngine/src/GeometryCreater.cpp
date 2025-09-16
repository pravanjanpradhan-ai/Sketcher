#include "GeometryCreater.h"
#include <iostream>
#include "FileWriter.h"

void GeometryCreater::createGeometry()
{
    std::string shapeName;
    std::cout << "Enter Shape Name from(Point, Line, Triangle, Rectangle, Circle, Polygon): ";
    std::cin >> shapeName;

    double P1x, P1y, P2x, P2y, P3x, P3y;
    std::vector<Point> shapes;
    std::cout << "1st Point: ";
    std::cin >> P1x >> P1y;
    Point p1(P1x, P1y);

    if (shapeName == "Point")
    {
        shapes.push_back(p1);
    }
    else if (shapeName == "Line")
    {
        std::cout << "2nd Point: ";
        std::cin >> P2x >> P2y;
        Point p2(P2x, P2y);
        Line l(p1, p2);
        shapes = l.getPoints();
    }
    else if (shapeName == "Triangle")
    {
        std::cout << "2nd Point: ";
        std::cin >> P2x >> P2y;
        std::cout << "3rd Point: ";
        std::cin >> P3x >> P3y;
        Point p2(P2x, P2y);
        Point p3(P3x, P3y);
        Triangle t(p1, p2, p3);
        shapes = t.getPoints();
    }
    else if (shapeName == "Rectangle")
    {
        std::cout << "3rd Point: ";
        std::cin >> P3x >> P3y;
        Point p3(P3x, P3y);
        Rectangle r(p1, p3);
        shapes = r.getPoints();
    }
    else if (shapeName == "Circle")
    {
        std::cout << "2nd Point: ";
        std::cin >> P2x >> P2y;
        Point p2(P2x, P2y);
        Circle c(p1, p2);
        shapes = c.getOnCirclePoint();
    }
    else if (shapeName == "Polygon")
    {
        int s = 0;
        std::cout << "2nd Point: ";
        std::cin >> P2x >> P2y;
        Point p2(P2x, P2y);
        std::cout << "Enter Number of Sides: ";
        std::cin >> s;
        Polygon p(p1, p2, s);
        shapes = p.getOnPolygonPoint();
    }
    else
    {
        std::cout << "You give wrong input";
    }

    // Write to file
    std::string fileName, extantionName = ".dat";
    std::cout << "Enter your file name: ";
    std::cin >> fileName;
    fileName = fileName + extantionName;
    FileWriter writer;
    writer.writeShapes(shapes, fileName);
}