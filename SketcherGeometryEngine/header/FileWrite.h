#pragma once
#include "Exports.h"
#include <fstream>
#include <vector>
#include "Point.h"



class SKETCHERGEOMETRYENGINE_API FileWrite
{
public:
    FileWrite();
    ~FileWrite();

    void write(std::vector<Point>);
};
