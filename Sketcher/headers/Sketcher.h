#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>
#include <variant>
#include "Point.h"
#include "Shape.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QToolBar>
#include <QToolButton>
using SketchData = std::variant<Shape* ,Point>;
class Sketcher : public QMainWindow
{
    Q_OBJECT

public:
    Sketcher(QWidget* parent = nullptr);
    ~Sketcher();
    void drawConnectedPoints(std::vector<Point> p);

private:
    void setupUI();
	std::unordered_map<int, std::vector<SketchData>> mshapes; // Store shapes with unique IDs
	int shapeIDCounter = 0; // Counter to assign unique IDs to shapes

private:
    QWidget* mCentralWidget;
    QGraphicsView* mCanvas;
    QGraphicsScene* mScene;
    QGridLayout* mCentralgridWidget;
    QToolBar* mToolBar;
    QToolButton* mPointTool;
    QToolButton* mLineTool;
    QToolButton* mTriangleTool;
    QToolButton* mRectangleTool;
    QToolButton* mCircleTool;
    QToolButton* mPolygonTool;
    QToolButton* mPolyLineTool;

private slots:
    void onPointToolClicked();
    void onLineToolClicked();
    void onTriangleToolClicked();
    void onRectangleToolClicked();
    void onCircleToolClicked();
};