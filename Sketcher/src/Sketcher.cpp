#include "stdafx.h"
#include "Sketcher.h"
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
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
    mScene = new QGraphicsScene(this);
    mGraphicsView->setScene(mScene);
}

Sketcher::~Sketcher()
{
}


void Sketcher::drawConnectedPoints( std::vector<Point>& points)
{
    //mScene->clear();  // Clear previous drawings

    QPolygonF polygon;
    for (int i = 0; i < points.size(); ++i) {
        polygon << QPointF(points[i].x, points[i].y);
    }
    mScene->addPolygon(polygon, QPen(Qt::blue, 2));


    //To draw small circles at each point
    int radius = 4;
    for (const auto& point : points) {
        mScene->addEllipse(point.x - radius / 2, point.y - radius / 2,
            radius, radius,
            QPen(Qt::black),
            QBrush(Qt::red));
    }
}

void Sketcher::onPointToolClicked()
{
	double x = QInputDialog::getDouble(this, "Point", "Enter X coordinate:", 0, -10000, 10000, 2);
	double y = - QInputDialog::getDouble(this, "Point", "Enter Y coordinate:", 0, -10000, 10000, 2);  
    Point p1(x, y);
    std::vector<Point> coord;
	coord.push_back(p1);
    drawConnectedPoints(coord);
}
void Sketcher::onLineToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Line", "Enter X coordinate for 1st Point:", 0, -10000, 10000, 2);
    double y1 = - QInputDialog::getDouble(this, "Line", "Enter Y coordinate for 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Line", "Enter X coordinate for 2nd Point:", 0, -10000, 10000, 2);
    double y2 = - QInputDialog::getDouble(this, "Line", "Enter Y coordinate for 2nd Point:", 0, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Line l1(p1, p2);
    std::vector<Point> coord = l1.getCoordinates();
    drawConnectedPoints(coord);
}
void Sketcher::onTriangleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate for 1st Point:", 0, -10000, 10000, 2);
    double y1 = - QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate for 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate for 2nd Point:", 0, -10000, 10000, 2);
    double y2 = - QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate for 2nd Point:", 0, -10000, 10000, 2);
    double x3 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate for 3rd Point:", 0, -10000, 10000, 2);
    double y3 = - QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate for 3rd Point:", 0, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Point p3(x3, y3);
    Triangle t(p1, p2, p3);
    std::vector<Point> coord = t.getCoordinates();
    drawConnectedPoints(coord);
}

void Sketcher::onRectangleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Rectangle", "Enter X coordinate for 1st Point:", 0, -10000, 10000, 2);
    double y1 = - QInputDialog::getDouble(this, "Rectangle", "Enter Y coordinate for 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Rectangle", "Enter X coordinate for 2nd Point:", 0, -10000, 10000, 2);
    double y2 = - QInputDialog::getDouble(this, "Rectangle", "Enter Y coordinate for 2nd Point:", 0, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Rectangles r1(p1, p2);
    std::vector<Point> coord = r1.getCoordinates();
    drawConnectedPoints(coord);
}

void Sketcher::onCircleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Circle", "Enter X coordinate for Center Point:", 0, -10000, 10000, 2);
    double y1 = - QInputDialog::getDouble(this, "Circle", "Enter Y coordinate for Center Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Circle", "Enter X coordinate for a Point on the circumference:", 0, -10000, 10000, 2);
    double y2 = - QInputDialog::getDouble(this, "Circle", "Enter Y coordinate for a Point on the circumference:", 0, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Circle c1(p1, p2);
    std::vector<Point> coord = c1.getCoordinates();
    drawConnectedPoints(coord);
}
void Sketcher::setupUI() {
    mCentralWidget = new QWidget(this);
    mCentralgridWidget = new QGridLayout(mCentralWidget);
    setCentralWidget(mCentralWidget);
    mToolBar = new QToolBar(this);
    addToolBar(mToolBar);


    mPointTool = new QToolButton(mToolBar);
    QIcon pointIcon(":/Sketcher/Point.png");
    mPointTool->setIcon(pointIcon);
    mPointTool->setIconSize(QSize(32, 32));
    mPointTool->setToolTip("Point");
    mToolBar->addWidget(mPointTool);

    mLineTool = new QToolButton(mToolBar);
    QIcon LineIcon(":/Sketcher/Line.png");
    mLineTool->setIcon(LineIcon);
    mLineTool->setIconSize(QSize(32, 32));
    mLineTool->setToolTip("Line");
    mToolBar->addWidget(mLineTool);

    mTriangleTool = new QToolButton(mToolBar);
    QIcon TriangleIcon(":/Sketcher/Triangle.png");
    mTriangleTool->setIcon(TriangleIcon);
    mTriangleTool->setIconSize(QSize(32, 32));
    mTriangleTool->setToolTip("Triangle");
    mToolBar->addWidget(mTriangleTool);

    mRectangleTool = new QToolButton(mToolBar);
    QIcon RectangleIcon(":/Sketcher/Rectangle.png");
    mRectangleTool->setIcon(RectangleIcon);
    mRectangleTool->setIconSize(QSize(32, 32));
    mRectangleTool->setToolTip("Rectangle");
    mToolBar->addWidget(mRectangleTool);

    mCircleTool = new QToolButton(mToolBar);
    QIcon CircleIcon(":/Sketcher/Circle.png");
    mCircleTool->setIcon(CircleIcon);
    mCircleTool->setIconSize(QSize(32, 32));
    mCircleTool->setToolTip("Circle");
    mToolBar->addWidget(mCircleTool);

    

   

    mGraphicsView = new QGraphicsView(this);
    mCentralgridWidget->addWidget(mGraphicsView, 0, 0, 1, 2);


    connect(mPointTool, &QToolButton::clicked, this, &Sketcher::onPointToolClicked);
    connect(mLineTool, &QToolButton::clicked, this, &Sketcher::onLineToolClicked);
    connect(mTriangleTool, &QToolButton::clicked, this, &Sketcher::onTriangleToolClicked);
    connect(mRectangleTool, &QToolButton::clicked, this, &Sketcher::onRectangleToolClicked);
    connect(mCircleTool, &QToolButton::clicked, this, &Sketcher::onCircleToolClicked);


}