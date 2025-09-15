// SketcherGeometryEngine.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "SketcherGeometryEngine.h"


// This is an example of an exported variable
SKETCHERGEOMETRYENGINE_API int nSketcherGeometryEngine=0;

// This is an example of an exported function.
SKETCHERGEOMETRYENGINE_API int fnSketcherGeometryEngine(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CSketcherGeometryEngine::CSketcherGeometryEngine()
{
    return;
}
