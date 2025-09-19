#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>
#include "Point.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QToolBar>
#include <QToolButton>

class Sketcher : public QMainWindow
{
    Q_OBJECT

public:
    Sketcher(QWidget* parent = nullptr);
    ~Sketcher();

private:
    void setupUI();

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

private slots:
    void onPointToolClicked();
    void onLineToolClicked();
    void onTriangleToolClicked();
    void onRectangleToolClicked();
    void onCircleToolClicked();
};