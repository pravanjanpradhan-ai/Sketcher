#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>
#include "Point.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QToolBar>
#include <QToolButton>
#include <QMouseEvent>

class Sketcher : public QMainWindow
{
    Q_OBJECT

public:
    Sketcher(QWidget* parent = nullptr);
    ~Sketcher();
    void drawConnectedPoints(std::vector<Point> p);
    void drawPolyline(const std::vector<Point>& p);


private:
    void setupUI();
	bool mpointToolActive = false;
	bool mlineToolActive = false;

protected:
	void mousePressEvent(QMouseEvent* event) override;

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
	std::vector<Point> tempPoints;

private slots:
    void onPointToolClicked();
    void onLineToolClicked();
    void onTriangleToolClicked();
    void onRectangleToolClicked();
    void onCircleToolClicked();
    void onPolygonToolClicked();
    void onPolyLineToolClicked();
};