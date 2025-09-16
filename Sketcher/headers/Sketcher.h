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
	QLineEdit* mX1LineEdit;
	QLineEdit* mY1LineEdit;
    QLineEdit* mX2LineEdit;
    QLineEdit* mY2LineEdit;
    QLineEdit* mX3LineEdit;
    QLineEdit* mY3LineEdit;
	QLabel* mShapeoutput;
    QString printout(std::vector<Point> p);


};