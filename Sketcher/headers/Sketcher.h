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
    void mousePressEvent(QMouseEvent* event) override; // Rituraj - Takes  mouse click position for coordinates, Pravanjan - panning with middle mouse button
    void keyPressEvent(QKeyEvent* event) override; // for enter - polygon/polyline finish, esc - cancel shape
    void wheelEvent(QWheelEvent* event) override; // zoom with mouse wheel
    void mouseMoveEvent(QMouseEvent* event) override; // panning with middle mouse button
    void mouseReleaseEvent(QMouseEvent* event) override; // stop panning when middle mouse button is released

private:
    void setupUI();
    std::unordered_map<int, std::vector<SketchData>> mShapes;
    int mShapeId = 0;
    bool isSave = false;
    bool isAxis = false;
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
    QGraphicsItem* axisItem = nullptr;
    QToolButton* mPointTool;
    QToolButton* mLineTool;     
    QToolButton* mTriangleTool;
    QToolButton* mRectangleTool;
    QToolButton* mCircleTool;
    QToolButton* mPolygonTool; 
    QToolButton* mPolyLineTool;
    QToolButton* mAxesTool;
    std::vector<Point> tempPoints;

private:
    bool m_panning = false;
    QPoint m_lastPanPoint;

private slots:
    void onPointToolClicked();
    void onLineToolClicked();
    void onTriangleToolClicked();
    void onRectangleToolClicked();
    void onCircleToolClicked();
    void onPolygonToolClicked();
    void onPolyLineToolClicked();

    void ondrawAxesToolClicked();

    void onNewActionTriggered();
    void onOpenActionTriggered();
    void onSaveActionTriggered();

    void onCleanActionTriggered();
    void onUndoActionTriggered();
    void onRedoActionTriggered();
};