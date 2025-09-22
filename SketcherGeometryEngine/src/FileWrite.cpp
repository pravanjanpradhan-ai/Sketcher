#include "pch.h"
#include <iostream>
#include "FileWrite.h"
#include <sstream>
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"



FileWrite::FileWrite()
{
}
FileWrite::~FileWrite(){
}

bool FileWrite::write(const std::string& filename, const std::unordered_map<int, std::vector<SketchData>>& shapes)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        return false;

    for (const auto& pair : shapes) {
        for (const auto& item : pair.second) {  // use 'item' here
            if (std::holds_alternative<Shape*>(item)) {
                Shape* shape = std::get<Shape*>(item);
                if (shape) {
                    fout << shape->getName() << ":\n";
                    const auto& coords = shape->getCoordinates();
                    for (const auto& pt : coords) {
                        fout << pt.x << ", " << pt.y << "\n";
                    }
                }
            }
            else if (std::holds_alternative<Point>(item)) {
                const Point& pt = std::get<Point>(item);
                fout << "Point:\n" << pt.x << ", " << pt.y << "\n";
            }
        }
    }

    fout.close();
    return true;
}

bool FileWrite::read(const std::string& filename, std::unordered_map<int, std::vector<SketchData>>& shapes)
{
    std::ifstream fin(filename);
    if (!fin.is_open())
        return false;

    shapes.clear();
    std::string line;
    int currentId = 0;

    std::string currentShapeName;
    std::vector<Point> tempPoints;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        if (line.back() == ':') {
            // Finalize previous shape
            if (!currentShapeName.empty() && currentShapeName != "Point" && !tempPoints.empty()) {
                Shape* newShape = nullptr;

                if (currentShapeName == "Line") {
                    newShape = new Line(tempPoints[0], tempPoints[1]);
                }
                else if (currentShapeName == "Rectangle") {
                    newShape = new Rectangles(tempPoints[0], tempPoints[2]);
                }
                else if (currentShapeName == "Circle") {
                    newShape = new Circle(tempPoints[0], tempPoints[1]);
                }
                else if (currentShapeName == "Triangle") {
                    newShape = new Triangle(tempPoints[0], tempPoints[1], tempPoints[2]);
                }

                if (newShape) {
                    shapes[currentId++].push_back(newShape);
                }
                tempPoints.clear();
            }

            // Start new shape
            currentShapeName = line.substr(0, line.size() - 1);
        }
        else {
            // Parse coordinates
            std::istringstream iss(line);
            double x, y;
            char comma;
            if (!(iss >> x >> comma >> y)) {
                continue;
            }

            if (currentShapeName == "Point") {
                Point pt(x, y);
                shapes[currentId++].push_back(pt);
            }
            else {
                tempPoints.push_back(Point(x, y));
            }
        }
    }

    // Final shape at EOF
    if (!currentShapeName.empty() && currentShapeName != "Point" && !tempPoints.empty()) {
        Shape* newShape = nullptr;

        if (currentShapeName == "Line") {
            newShape = new Line(tempPoints[0], tempPoints[1]);
        }
        else if (currentShapeName == "Rectangle") {
            newShape = new Rectangles(tempPoints[0], tempPoints[2]);
        }
        else if (currentShapeName == "Circle") {
            newShape = new Circle(tempPoints[0], tempPoints[1]);
        }
        else if (currentShapeName == "Triangle") {
            newShape = new Triangle(tempPoints[0], tempPoints[1], tempPoints[2]);
        }

        if (newShape) {
            shapes[currentId++].push_back(newShape);
        }
    }

    fin.close();
    return true;
}