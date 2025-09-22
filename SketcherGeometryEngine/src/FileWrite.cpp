#include "pch.h"
#include <iostream>
#include "FileWrite.h"



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