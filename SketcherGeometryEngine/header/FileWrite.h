#pragma once
#include "Exports.h"
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include "Point.h"
#include "Shape.h"

using SketchData = std::variant<Shape*, Point>;
class SKETCHERGEOMETRYENGINE_API FileWrite
{
public:
    FileWrite();
    ~FileWrite();

    bool write(const std::string& filename, const std::unordered_map<int, std::vector<SketchData>>& shapes);
};
