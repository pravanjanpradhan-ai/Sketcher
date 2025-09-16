#include "pch.h"
#include <iostream>
#include "FileWrite.h"



FileWrite::FileWrite()
{
}
FileWrite::~FileWrite(){
}

void FileWrite::write(std::vector<Point> p)
{
    std::ofstream ofs ("coordinates.dat", std::ofstream::out);
    int pSize=p.size();
        
        for (int i=0;i<pSize;i++){
            ofs<<p[i].x<<" "<<p[i].y<<std::endl;
            
        }


    ofs.close();
    
}