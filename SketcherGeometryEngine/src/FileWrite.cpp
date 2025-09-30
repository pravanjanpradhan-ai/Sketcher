#include "pch.h"
#include <iostream>
#include "FileWrite.h"
#include <sstream>
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Polygon.h"
#include "PolyLine.h"


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
        bool headerPrinted = false; // track header per group

        for (const auto& item : pair.second) {
            if (std::holds_alternative<Shape*>(item)) {
                Shape* shape = std::get<Shape*>(item);
                if (shape) {
                    if (!headerPrinted) {
                        fout << shape->getName() << ":\n";
                        headerPrinted = true;
                    }

                    const std::vector<Point>& coords = shape->getCoordinates();
                    if (coords.size() > 36) {
                        fout << "(" << coords[0].x << " " << coords[0].y << ") ";
                        fout << "(" << coords[1].x << " " << coords[1].y << ") \n";
                    }
                    else{
                        for (const auto& pt : coords) {
                            fout << "(" << pt.x << " " << pt.y << ") ";
                        }
                        fout << "\n";
                    }
                }
            }
            else if (std::holds_alternative<Point>(item)) {
                const Point& pt = std::get<Point>(item);
                if (!headerPrinted) {
                    fout << "Point:\n";
                    headerPrinted = true;
                }
                fout << "(" << pt.x << " " << pt.y << ")\n";
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
    std::string currentShape;

    while (std::getline(fin, line)) {
        if (line.empty()) continue; // skip blank lines

        // If line ends with ":", it’s a new shape section
        if (line.back() == ':') {
            currentShape = line.substr(0, line.size() - 1);
            continue;
        }

        std::stringstream ss(line);

        // ----- Point section -----
        if (currentShape == "Point") {
            double x, y;
            char ch; // to skip '(' , ')' , spaces
            if (ss >> ch >> x >> y >> ch) {
                shapes[1].push_back(Point(x, y));
            }
        }
        else {
            // ----- Other Shape section -----
            std::vector<Point> coords;
            double x, y;
            char ch;

            // Parse all coordinate pairs in this line
            while (ss >> ch >> x >> y >> ch) {
                coords.emplace_back(x, y);
            }

            if (!coords.empty()) {
                if (currentShape == "Line") {
                    Shape* l = new Line(coords[0], coords[1]);
                    shapes[2].push_back(l);
                }
                else if (currentShape == "Triangle") {
                    Shape* t = new Triangle(coords[0], coords[1], coords[2]);
                    shapes[3].push_back(t);
                }
                else if (currentShape == "Rectangle") {
                    Shape* r = new Rectangles(coords[0], coords[2]);
                    shapes[4].push_back(r);
                }
                else if (currentShape == "Circle") {
                    Shape* c = new Circle(coords[0], coords[1]);
                    shapes[5].push_back(c);
                }
                else if (currentShape == "Polygon") {
                    Shape* poly = new Polygons(coords);
                    shapes[6].push_back(poly);
                }
                else if (currentShape == "PolyLine") {
                    Shape* pl = new PolyLine(coords);
                    shapes[6].push_back(pl);
                }
            }
        }
    }

    fin.close();
    return true;
}

//bool FileWrite::read(const std::string& filename, std::unordered_map<int, std::vector<SketchData>>& shapes)
//{
//    std::ifstream fin(filename);
//    if (!fin.is_open())
//        return false;
//
//    shapes.clear();
//    std::string line;
//    int currentId = 0;
//
//    std::string currentShapeName;
//    std::vector<Point> tempPoints;
//    bool anyValidData = false;   // track if we parsed at least one valid shape/point
//
//    auto finalizeShape = [&](std::string shapeName, std::vector<Point>& pts) -> bool {
//        Shape* newShape = nullptr;
//        if (shapeName == "Line" && pts.size() >= 2) {
//            newShape = new Line(pts[0], pts[1]);
//        }
//        else if (shapeName == "Rectangle" && pts.size() >= 4) {
//            newShape = new Rectangles(pts[0], pts[2]);
//        }
//        else if (shapeName == "Circle" && pts.size() >= 2) {
//            newShape = new Circle(pts[0], pts[1]);
//        }
//        else if (shapeName == "Triangle" && pts.size() >= 3) {
//            newShape = new Triangle(pts[0], pts[1], pts[2]);
//        }
//
//        if (newShape) {
//            shapes[currentId++].push_back(newShape);
//            pts.clear();
//            return true;
//        }
//        return false;
//        };
//
//    while (std::getline(fin, line)) {
//        if (line.empty()) continue;
//
//        if (line.back() == ':') {
//            // Finalize previous shape
//            if (!currentShapeName.empty() && currentShapeName != "Point" && !tempPoints.empty()) {
//                if (!finalizeShape(currentShapeName, tempPoints)) {
//                    return false; // invalid shape format
//                }
//                anyValidData = true;
//            }
//
//            // Start new shape
//            currentShapeName = line.substr(0, line.size() - 1);
//
//            // Validate shape name
//            if (currentShapeName != "Point" && currentShapeName != "Line" &&
//                currentShapeName != "Triangle" && currentShapeName != "Rectangle" &&
//                currentShapeName != "Circle") {
//                return false; // unknown shape
//            }
//        }
//        else {
//            // Parse coordinates
//            std::istringstream iss(line);
//            double x, y;
//            char comma;
//            if (!(iss >> x >> comma >> y) || comma != ',') {
//                return false;
//            }
//
//            if (currentShapeName == "Point") {
//                shapes[currentId++].push_back(Point(x, y));
//                anyValidData = true;
//            }
//            else {
//                tempPoints.push_back(Point(x, y));
//            }
//        }
//    }
//
//    // Final shape at EOF
//    if (!currentShapeName.empty() && currentShapeName != "Point" && !tempPoints.empty()) {
//        if (!finalizeShape(currentShapeName, tempPoints)) {
//            return false; // incomplete shape
//        }
//        anyValidData = true;
//    }
//
//    fin.close();
//    return anyValidData; // false if file empty or no valid shape/point
//}
