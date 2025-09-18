#include "stdafx.h"
#include "Sketcher.h"
#include <QString>
#include "Point.h"
#include "Line.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"



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
void Sketcher::onPointToolClicked()
{
    double x = mX1LineEdit->text().toDouble();
    double y = mY1LineEdit->text().toDouble();
    Point p1(x, y);
    QString solution = QString("X: ").append(QString::number(p1.x)).append(" Y: ").append(QString::number(p1.y));
    mShapeoutput->setText(solution);
}
void Sketcher::onLineToolClicked()
{
    double x1 = mX1LineEdit->text().toDouble();
    double y1 = mY1LineEdit->text().toDouble();
    double x2 = mX2LineEdit->text().toDouble();
    double y2 = mY2LineEdit->text().toDouble();

    Point p1(x1, y1);
    Point p2(x2, y2);
    Line l1(p1, p2);
    std::vector<Point> coord = l1.getCoordinates();
    mShapeoutput->setText(Sketcher::printout(coord));
}
void Sketcher::onTriangleToolClicked()
{
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
    std::vector<Point> coord = t.getCoordinates();
    mShapeoutput->setText(Sketcher::printout(coord));
}

void Sketcher::onRectangleToolClicked()
{
    double x1 = mX1LineEdit->text().toDouble();
    double y1 = mY1LineEdit->text().toDouble();
    double x2 = mX2LineEdit->text().toDouble();
    double y2 = mY2LineEdit->text().toDouble();
    Point p1(x1, y1);
    Point p2(x2, y2);
    Rectangles r1(p1, p2);
    std::vector<Point> coord = r1.getCoordinates();
    mShapeoutput->setText(Sketcher::printout(coord));
}

void Sketcher::onCircleToolClicked()
{
    double x1 = mX1LineEdit->text().toDouble();
    double y1 = mY1LineEdit->text().toDouble();
    double x2 = mX2LineEdit->text().toDouble();
    double y2 = mY2LineEdit->text().toDouble();
    Point p1(x1, y1);
    Point p2(x2, y2);
    Circle c1(p1, p2);
    std::vector<Point> coord = c1.getCoordinates();
    mShapeoutput->setText(Sketcher::printout(coord));
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

  
    
	connect(mPointTool, &QToolButton::clicked, this, &Sketcher::onPointToolClicked);
    connect(mLineTool, &QToolButton::clicked, this ,&Sketcher::onLineToolClicked);
    connect(mTriangleTool, &QToolButton::clicked, this, &Sketcher::onTriangleToolClicked);
    connect(mRectangleTool, &QToolButton::clicked, this, &Sketcher::onRectangleToolClicked);
	connect(mCircleTool, &QToolButton::clicked, this, &Sketcher::onCircleToolClicked);
    

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