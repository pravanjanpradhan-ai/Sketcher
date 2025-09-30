#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>
#include <unordered_map>
#include <variant>
#include <QStatusBar>
#include <QLabel>
#include <QMouseEvent>
#include "Point.h"
#include "Shape.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include "UndoRedo.h"
#include "CanvasView.h"

using SketchData = std::variant<Shape*, Point>;
class Sketcher : public QMainWindow
{
    Q_OBJECT

public:
    Sketcher(QWidget* parent = nullptr);
    ~Sketcher();
    void drawConnectedPoints(std::vector<Point> p);
    void drawAxesTool();
    void handleCanvasClick(QPointF pos);
    void finishShape();
    void cancelShape();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;  //Latesh -  status bar - handle mouse movement

private:
    void setupUI();
    std::unordered_map<int, std::vector<SketchData>> mShapes;
    int mShapeId = 0;
    bool isSave = false;
    UndoRedoManager* mUndoRedo = new UndoRedoManager();
    enum class ToolType { None, Point, Line, Triangle, Rectangle, Circle, Polygon, PolyLine };
    ToolType mCurrentTool = ToolType::None;

private:
    QWidget* mCentralWidget;
    QGraphicsView* mCanvas;
    QGraphicsScene* mScene;
    QGridLayout* mCentralgridWidget;
    QToolBar* mToolBar;
	QMenuBar* mMenuBar;
	QStatusBar* mStatusBar;
	QLabel* mStatusLabel;
    QLabel* posLabel;   // Label to display mouse position

    QToolButton* mPointTool;
    QToolButton* mLineTool;     
    QToolButton* mTriangleTool;
    QToolButton* mRectangleTool;
    QToolButton* mCircleTool;
    QToolButton* mPolygonTool; 
    QToolButton* mPolyLineTool;
    QToolButton* mAxesTool;
    std::vector<Point> tempPoints;

private slots:
    void onPointToolClicked();
    void onLineToolClicked();
    void onTriangleToolClicked();
    void onRectangleToolClicked();
    void onCircleToolClicked();
    void onPolygonToolClicked();
    void onPolyLineToolClicked();

    void onNewActionTriggered();
    void onOpenActionTriggered();
    void onSaveActionTriggered();

    void onCleanActionTriggered();
    void onUndoActionTriggered();
    void onRedoActionTriggered();
};