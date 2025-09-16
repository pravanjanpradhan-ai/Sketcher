#pragma once
#include <vector>
#include <string>
#include "Point.h"

class FileWriter
{
public:
    FileWriter() {};
    ~FileWriter() {};

    void writeShapes(const std::vector<Point> shapes, const std::string &fileName);
};
