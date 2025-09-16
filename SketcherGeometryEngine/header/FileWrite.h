#pragma once
#include <fstream>
#include <vector>
#include "Point.h"




class FileWrite
{
public:
    FileWrite();
    ~FileWrite();

    void write(std::vector<Point>);
};
