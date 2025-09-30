#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>
#include "Point.h"
#include <variant>
#include "Shape.h"
#include <QToolBar>
#include <QToolButton>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPolygonF>
#include <QPen>
#include <QBrush>



using SketchData = std::variant<Point, Shape*>;

class Sketcher : public QMainWindow
{
    Q_OBJECT

public:
    Sketcher(QWidget* parent = nullptr);
    ~Sketcher();

private:
    void setupUI();
	std::unordered_map<int,std::vector< SketchData> > mShapes;
	int mShapeId = 0;
	bool isSave = false;
public:
    QWidget* mCentralWidget;
    QGridLayout* mCentralgridWidget;
    QToolBar* mToolBar;
    QToolButton* mPointTool;
    QToolButton* mLineTool;
    QToolButton* mTriangleTool;
    QToolButton* mRectangleTool;
    QToolButton* mCircleTool;
	QMenu* mFileMenu;
	QMenuBar* mMenuBar;
	QMenu* mEditMenu;
    QAction* newAction;
    QAction* saveAction;
    void drawConnectedPoints(std::vector<Point>& points);
	QGraphicsView* mGraphicsView;
    QGraphicsScene* mScene;


private slots:
    void onPointToolClicked();
	void onLineToolClicked();
	void onTriangleToolClicked();
	void onRectangleToolClicked();
	void onCircleToolClicked();
	void onNewFile();
	void onOpenFile();
	void onSaveFile();
	void onSaveAsFile();
   
};