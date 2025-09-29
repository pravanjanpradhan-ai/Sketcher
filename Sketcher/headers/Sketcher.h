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

    //protected:
    //void mouseMoveEvent(QMouseEvent* event) override;  // handle mouse movement
//
//signals:
//    void mouseMoved(const QPointF& pos);   // signal to send scene coordinates

private:
    void setupUI();
    std::unordered_map<int, std::vector<SketchData>> mShapes;
    int mShapeId = 0;
    bool isSave = false;
    UndoRedoManager* mUndoRedo = new UndoRedoManager();

private:
    QWidget* mCentralWidget;
    QGraphicsView* mCanvas;
    QGraphicsScene* mScene;
    QGridLayout* mCentralgridWidget;
    QToolBar* mToolBar;
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

private slots:
    void onPointToolClicked();
    void onLineToolClicked();
    void onTriangleToolClicked();
    void onRectangleToolClicked();
    void onCircleToolClicked();

    void onNewActionTriggered();
    void onOpenActionTriggered();
    void onSaveActionTriggered();

    void onCleanActionTriggered();
    void onUndoActionTriggered();
    void onRedoActionTriggered();
};