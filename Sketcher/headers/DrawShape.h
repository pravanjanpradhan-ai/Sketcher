#pragma once
#include <vector>
#include "Point.h"
#include <QGraphicsScene>
#include <QGridLayout>
#include "Sketcher.h"

class DrawShape
{
    DrawShape() {}
	~DrawShape() {}

public:
    void drawConnectedPoints(std::vector<Point> p);
    void handleCanvasClick(QPointF pos);
    void finishShape();
    void cancelShape();

private:
    enum class ToolType { None, Point, Line, Triangle, Rectangle, Circle, Polygon, PolyLine };
    ToolType mCurrentTool = ToolType::None;

    std::vector<Point> tempPoints;
    Sketcher* mSketcher;

};
