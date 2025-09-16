#include "FileWriter.h"
#include <fstream>
#include <iostream>

void FileWriter::writeShapes(const std::vector<Point> shapes, const std::string &fileName)
{
    std::ofstream fout(fileName);
    if (!fout.is_open())
    {
        std::cerr << "Error: Could not open file " << fileName << "\n";
    }

    for (int i = 0; i < shapes.size(); i++)
    {
        fout << shapes[i].x << " " << shapes[i].y << "\n";
    }
    fout.close();
}
