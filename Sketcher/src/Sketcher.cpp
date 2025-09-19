#include "stdafx.h"
#include "Sketcher.h"
#include <QString>
#include <QIcon>
#include <QSize>
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
}

Sketcher::~Sketcher() {}

void Sketcher::setupUI()
{
    // Central widget and layout
    mCentralWidget = new QWidget(this);
    mCentralgridWidget = new QGridLayout(mCentralWidget);

    // Scene + Canvas
    mScene = new QGraphicsScene(this);
    mCanvas = new QGraphicsView(mScene, mCentralWidget);
    mCentralgridWidget->addWidget(mCanvas, 0, 0);
    setCentralWidget(mCentralWidget);

    // File Menu
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* saveAction = fileMenu->addAction("Save");
    saveAction->setShortcut(QKeySequence::Save);   // Ctrl+S
    QAction* clearAction = fileMenu->addAction("Clear");
    clearAction->setShortcut(Qt::CTRL | Qt::Key_X); // Ctrl+X

    // Edit Menu
    QMenu* editMenu = menuBar()->addMenu("Edit");
    QAction* undoAction = editMenu->addAction("Undo");
    undoAction->setShortcut(QKeySequence::Undo);   // Ctrl+Z
    QAction* redoAction = editMenu->addAction("Redo");
    redoAction->setShortcut(Qt::ALT | Qt::Key_Z);   // Alt+Z

    mToolBar = new QToolBar(this);
    addToolBar(mToolBar);

    // Point Tool
    mPointTool = new QToolButton(mToolBar);
    mPointTool->setIcon(QIcon(":/Sketcher/Point.png"));
    mPointTool->setIconSize(QSize(32, 32));
    mPointTool->setToolTip("Point");
    mToolBar->addWidget(mPointTool);

    // Line Tool
    mLineTool = new QToolButton(mToolBar);
    mLineTool->setIcon(QIcon(":/Sketcher/Line.png"));
    mLineTool->setIconSize(QSize(32, 32));
    mLineTool->setToolTip("Line");
    mToolBar->addWidget(mLineTool);

    // Triangle Tool
    mTriangleTool = new QToolButton(mToolBar);
    mTriangleTool->setIcon(QIcon(":/Sketcher/Triangle.png"));
    mTriangleTool->setIconSize(QSize(32, 32));
    mTriangleTool->setToolTip("Triangle");
    mToolBar->addWidget(mTriangleTool);

    // Rectangle Tool
    mRectangleTool = new QToolButton(mToolBar);
    mRectangleTool->setIcon(QIcon(":/Sketcher/Rectangle.png"));
    mRectangleTool->setIconSize(QSize(32, 32));
    mRectangleTool->setToolTip("Rectangle");
    mToolBar->addWidget(mRectangleTool);

    // Circle Tool
    mCircleTool = new QToolButton(mToolBar);
    mCircleTool->setIcon(QIcon(":/Sketcher/Circle.png"));
    mCircleTool->setIconSize(QSize(32, 32));
    mCircleTool->setToolTip("Circle");
    mToolBar->addWidget(mCircleTool);

    // Text
    QToolButton* Text_btn = new QToolButton(mToolBar);
    Text_btn->setText("Text");
    mToolBar->addWidget(Text_btn);

    // Connections
    connect(mPointTool, &QToolButton::clicked, this, &Sketcher::onPointToolClicked);
    connect(mLineTool, &QToolButton::clicked, this, &Sketcher::onLineToolClicked);
    connect(mTriangleTool, &QToolButton::clicked, this, &Sketcher::onTriangleToolClicked);
    connect(mRectangleTool, &QToolButton::clicked, this, &Sketcher::onRectangleToolClicked);
    connect(mCircleTool, &QToolButton::clicked, this, &Sketcher::onCircleToolClicked);
}

// --- Slots for drawing ---

void Sketcher::onPointToolClicked()
{
    double x = QInputDialog::getDouble(this, "Point", "Enter X coordinate:", 0, -10000, 10000, 2);
    double y = -QInputDialog::getDouble(this, "Point", "Enter Y coordinate:", 0, -10000, 10000, 2);
    Point p(x, y);
    QBrush brush(QColor("#3DB9E7"));
    mScene->addEllipse(p.x - 2, p.y - 2, 4, 4, QPen(Qt::transparent), brush);
}

void Sketcher::onLineToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Line", "Enter X coordinate of 1st Point:", 0, -10000, 10000, 2);
    double y1 = -QInputDialog::getDouble(this, "Line", "Enter Y coordinate of 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Line", "Enter X coordinate of 2nd Point:", 1, -10000, 10000, 2);
    double y2 = -QInputDialog::getDouble(this, "Line", "Enter Y coordinate of 2nd Point:", 1, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Line l(p1, p2);
    std::vector<Point> p = l.getCoordinates();
    QLineF line(QPointF(l.getCoordinates()[0].x, l.getCoordinates()[0].y), QPointF(l.getCoordinates()[1].x, l.getCoordinates()[1].y));
    mScene->addLine(line, QPen(Qt::blue, 2));
}

void Sketcher::onTriangleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate of 1st Point:", 0, -10000, 10000, 2);
    double y1 = -QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate of 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate of 2nd Point:", 1, -10000, 10000, 2);
    double y2 = -QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate of 2nd Point:", 1, -10000, 10000, 2);
    double x3 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate of 3rd Point:", 0, -10000, 10000, 2);
    double y3 = -QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate of 3rd Point:", 1, -10000, 10000, 2);
    Point a(x1, y1);
    Point b(x2, y2);
    Point c(x3, y3);
    Triangle t(a, b, c);
    std::vector<Point> p = t.getCoordinates();
    QPolygonF shape;
    for (int i = 0; i < p.size(); i++) {
        shape << QPointF(p[i].x, p[i].y);
    }
    mScene->addPolygon(shape, QPen(Qt::darkCyan, 2));
}

void Sketcher::onRectangleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Rectangle", "Enter X coordinate of 1st Point:", 0, -10000, 10000, 2);
    double y1 = -QInputDialog::getDouble(this, "Rectangle", "Enter Y coordinate of 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Rectangle", "Enter X coordinate of 2nd Point:", 1, -10000, 10000, 2);
    double y2 = -QInputDialog::getDouble(this, "Rectangle", "Enter Y coordinate of 2nd Point:", 1, -10000, 10000, 2);
    Point a(x1, y1);
    Point c(x2, y2);
    Rectangles r(a, c);
    std::vector<Point> p = r.getCoordinates();
    QPolygonF shape;
    for (int i = 0; i < p.size(); i++) {
        shape << QPointF(p[i].x, p[i].y);
    }
    mScene->addPolygon(shape, QPen(Qt::darkYellow, 2));
}

void Sketcher::onCircleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Circle", "Enter X coordinate of Center:", 0, -10000, 10000, 2);
    double y1 = -QInputDialog::getDouble(this, "Circle", "Enter Y coordinate of Center:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Circle", "Enter X coordinate of a circumference Point:", 1, -10000, 10000, 2);
    double y2 = -QInputDialog::getDouble(this, "Circle", "Enter Y coordinate of a circumference Point:", 1, -10000, 10000, 2);
    Point Center(x1, y1);
    Point onCircle(x2, y2);
    Circle c(Center, onCircle);
    std::vector<Point> p = c.getCoordinates();
    QPolygonF shape;
    for (int i = 0; i < p.size(); i++) {
        shape << QPointF(p[i].x, p[i].y);
    }
    mScene->addPolygon(shape, QPen(Qt::green, 2));
    QBrush brush(QColor("#3DB9E7"));
    mScene->addEllipse(x1 - 2, y1 - 2, 4, 4, QPen(Qt::transparent), brush);
}