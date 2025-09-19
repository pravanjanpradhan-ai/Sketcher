#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>
#include "Point.h"





class Sketcher : public QMainWindow
{
    Q_OBJECT

public:
    Sketcher(QWidget* parent = nullptr);
    ~Sketcher();

private:
    void setupUI();

public:
    QWidget* mCentralWidget;
    QGridLayout* mCentralgridWidget;
    QToolBar* mToolBar;
    QToolButton* mPointTool;
    QToolButton* mLineTool;
    QToolButton* mTriangleTool;
    QToolButton* mRectangleTool;
    QToolButton* mCircleTool;
    void drawConnectedPoints(std::vector<Point>& points);
	QGraphicsView* mGraphicsView;
    QGraphicsScene* mScene;


private slots:
    void onPointToolClicked();
	void onLineToolClicked();
	void onTriangleToolClicked();
	void onRectangleToolClicked();
	void onCircleToolClicked();

    

    
};