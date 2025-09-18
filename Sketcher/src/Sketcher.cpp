#include "stdafx.h"
#include "Sketcher.h"
#include <QString>
#include "Point.h"
#include "Point.cpp"
#include "Line.cpp"
#include "Line.h"
#include "Shape.h"
#include "Shape.cpp"
#include "Circle.h"
#include "Circle.cpp"
#include "Rectangle.h"
#include "Rectangle.cpp"
#include "Triangle.cpp"


Sketcher::Sketcher(QWidget* parent)
    : QMainWindow(parent)
{

    setupUI();
    resize(800, 600);
}

Sketcher::~Sketcher()
{
}

QString Sketcher::printout(std::vector<Point> p) {
    QString solution;
    for (const auto& point : p) {
        solution.append("X: ").append(QString::number(point.x)).append(" Y: ").append(QString::number(point.y)).append("\n");
    }
    return solution;
}
void Sketcher::setupUI() {
    mCentralWidget = new QWidget(this);
    mCentralgridWidget = new QGridLayout(mCentralWidget);
    setCentralWidget(mCentralWidget);
    mToolBar = new QToolBar(this);
    addToolBar(mToolBar);


    mPointTool = new QToolButton(mToolBar);
    mPointTool->setText("Point");
    mToolBar->addWidget(mPointTool);

    mLineTool = new QToolButton(mToolBar);
    mLineTool->setText("Line");
    mToolBar->addWidget(mLineTool);

    mTriangleTool = new QToolButton(mToolBar);
    mTriangleTool->setText("Triangle");
    mToolBar->addWidget(mTriangleTool);

    mRectangleTool = new QToolButton(mToolBar);
    mRectangleTool->setText("Rectangle");
    mToolBar->addWidget(mRectangleTool);

    mCircleTool = new QToolButton(mToolBar);
    mCircleTool->setText("Circle");
    mToolBar->addWidget(mCircleTool);

    mX1LineEdit = new QLineEdit(mCentralWidget);
    mX1LineEdit->setPlaceholderText("X1");
    mCentralgridWidget->addWidget(mX1LineEdit, 0, 0, 1, 1);

    mY1LineEdit = new QLineEdit(mCentralWidget);
    mY1LineEdit->setPlaceholderText("Y1");
    mCentralgridWidget->addWidget(mY1LineEdit, 0, 1, 1, 1);

    mX2LineEdit = new QLineEdit(mCentralWidget);
    mX2LineEdit->setPlaceholderText("X2");
    mCentralgridWidget->addWidget(mX2LineEdit, 1, 0, 1, 1);

    mY2LineEdit = new QLineEdit(mCentralWidget);
    mY2LineEdit->setPlaceholderText("Y2");
    mCentralgridWidget->addWidget(mY2LineEdit, 1, 1, 1, 1);

    mX3LineEdit = new QLineEdit(mCentralWidget);
    mX3LineEdit->setPlaceholderText("X3");
    mCentralgridWidget->addWidget(mX3LineEdit, 2, 0, 1, 1);

    mY3LineEdit = new QLineEdit(mCentralWidget);
    mY3LineEdit->setPlaceholderText("Y3");
    mCentralgridWidget->addWidget(mY3LineEdit, 2, 1, 1, 1);

    mShapeoutput = new QLabel(mCentralWidget);
    mShapeoutput->setText("Coordinates:");
    mCentralgridWidget->addWidget(mShapeoutput, 3, 0, 1, 2);


    // Point
    connect(mPointTool, &QToolButton::clicked, this, &Sketcher::CreatePoint);

    //Line
    connect(mLineTool, &QToolButton::clicked, this, &Sketcher::CreateLine);

    //Circle
    connect(mCircleTool, &QToolButton::clicked, this, &Sketcher::CreateCircle);

    //Rectangle
    connect(mRectangleTool, &QToolButton::clicked, this, &Sketcher::CreateRectangle);

    //Triangle
    connect(mTriangleTool, &QToolButton::clicked, this, &Sketcher::CreateTriangle);

}


// Point
void Sketcher::CreatePoint() {
    double x = mX1LineEdit->text().toDouble();
    double y = mY1LineEdit->text().toDouble();

    Point p1(x, y);
    QString solution = QString("X: ").append(QString::number(p1.x)).append(" Y: ").append(QString::number(p1.y));
    mShapeoutput->setText(solution);
}


//Line
void Sketcher::CreateLine() {
    double x1 = mX1LineEdit->text().toDouble();
    double y1 = mY1LineEdit->text().toDouble();
    double x2 = mX2LineEdit->text().toDouble();
    double y2 = mY2LineEdit->text().toDouble();

    Point p1(x1, y1);
    Point p2(x2, y2);
    Line l1(p1, p2);
    std::vector<Point> cordL = l1.getCoordinates();
    mShapeoutput->setText(Sketcher::printout(cordL));
}

//Rectangle
void Sketcher::CreateRectangle() {
    double x1 = mX1LineEdit->text().toDouble();
    double y1 = mY1LineEdit->text().toDouble();
    double x2 = mX2LineEdit->text().toDouble();
    double y2 = mY2LineEdit->text().toDouble();
    Point p1(x1, y1);
    Point p2(x2, y2);
    Rectangles r1(p1, p2);
    std::vector<Point> cordL = r1.getCoordinates();
    mShapeoutput->setText(Sketcher::printout(cordL));
}


//Triangle
void Sketcher::CreateTriangle() {
    double x1 = mX1LineEdit->text().toDouble();
    double y1 = mY1LineEdit->text().toDouble();
    double x2 = mX2LineEdit->text().toDouble();
    double y2 = mY2LineEdit->text().toDouble();
    double x3 = mX3LineEdit->text().toDouble();
    double y3 = mY3LineEdit->text().toDouble();
    Point p1(x1, y1);
    Point p2(x2, y2);
    Point p3(x3, y3);
    Triangle t(p1, p2, p3);
    std::vector<Point> cordL = t.getCoordinates();
    mShapeoutput->setText(Sketcher::printout(cordL));
}

//Circle
void Sketcher::CreateCircle() {
    double x1 = mX1LineEdit->text().toDouble();
    double y1 = mY1LineEdit->text().toDouble();
    double x2 = mX2LineEdit->text().toDouble();
    double y2 = mY2LineEdit->text().toDouble();
    Point p1(x1, y1);
    Point p2(x2, y2);
    Circle c1(p1, p2);
    std::vector<Point> cordL = c1.getCoordinates();
    mShapeoutput->setText(Sketcher::printout(cordL));
}