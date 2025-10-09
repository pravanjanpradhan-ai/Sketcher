#include "stdafx.h"
#include "Sketcher.h"
#include <QString>
#include <QIcon>
#include <QSize>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainterPath>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Polygon.h"
#include "PolyLine.h"
#include "FileWrite.h"


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
    mCanvas->setMouseTracking(true); // important
    mCentralgridWidget->addWidget(mCanvas,0,0);
	//Mouse click
    mCanvas = new CanvasView(mScene, mCentralWidget);
    static_cast<CanvasView*>(mCanvas)->setSketcher(this);
    mCentralgridWidget->addWidget(mCanvas, 0, 0);

    setCentralWidget(mCentralWidget);
    mCanvas->scale(1, -1);
    
	mMenuBar = new QMenuBar(this);
	setMenuBar(mMenuBar);
    // File Menu
    QMenu* fileMenu = mMenuBar->addMenu("File");
    QAction* newAction = fileMenu->addAction(mMenuBar->style()->standardIcon(QStyle::SP_FileIcon), "New");
    newAction->setShortcut(QKeySequence::New);   // Ctrl+N
    QAction* openAction = fileMenu->addAction(mMenuBar->style()->standardIcon(QStyle::SP_DirOpenIcon), "Open");
    openAction->setShortcut(QKeySequence::Open);   // Ctrl+O
    QAction* saveAction = fileMenu->addAction(mMenuBar->style()->standardIcon(QStyle::SP_DialogSaveButton), "Save");
    saveAction->setShortcut(QKeySequence::Save);   // Ctrl+S


    // Edit Menu
    QMenu* editMenu = mMenuBar->addMenu("Edit");
    QAction* cleanAction = editMenu->addAction(mMenuBar->style()->standardIcon(QStyle::SP_TrashIcon), "Clean");
    cleanAction->setShortcut(Qt::CTRL | Qt::Key_X); // Ctrl+X
    QAction* undoAction = editMenu->addAction(mMenuBar->style()->standardIcon(QStyle::SP_ArrowBack), "Undo");
    undoAction->setShortcut(QKeySequence::Undo);   // Ctrl+Z
    QAction* redoAction = editMenu->addAction(mMenuBar->style()->standardIcon(QStyle::SP_ArrowForward), "Redo");
    redoAction->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_Z);   // Ctrl+Shift+Z

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

    // Polygon Tool
    mPolygonTool = new QToolButton(mToolBar);
    mPolygonTool->setIcon(QIcon(":/Sketcher/Polygon.png"));
    mPolygonTool->setIconSize(QSize(32, 32));
    mPolygonTool->setToolTip("Polygon");
    mToolBar->addWidget(mPolygonTool);

    // PolyLine Tool
    mPolyLineTool = new QToolButton(mToolBar);
    mPolyLineTool->setIcon(QIcon(":/Sketcher/PolyLine.png"));
    mPolyLineTool->setIconSize(QSize(32, 32));
    mPolyLineTool->setToolTip("PolyLine");
    mToolBar->addWidget(mPolyLineTool);

    // Axes Tool
    mAxesTool = new QToolButton(mToolBar);
    mAxesTool->setIcon(QIcon(":/Sketcher/axis.jpg"));
    mAxesTool->setIconSize(QSize(32, 32));
    mAxesTool->setToolTip("Axis");
    mToolBar->addWidget(mAxesTool);



    setMouseTracking(true);
    //if (mCentralWidget)
    mCanvas->setMouseTracking(true);

    // Status Bar
    mStatusBar = new QStatusBar(this);
    setStatusBar(mStatusBar);
    posLabel = new QLabel(this);
    //posLabel = new QLabel("X: 0, Y: 0", this);
    mStatusBar->showMessage("Application Started");
    // status bar label for mouse position
    mStatusBar->addPermanentWidget(posLabel);
    // Add a permanent widget (label)
    mStatusLabel = new QLabel("Ready", this);
    mStatusBar->addPermanentWidget(mStatusLabel);

    // Connections
    connect(mPointTool, &QToolButton::clicked, this, &Sketcher::onPointToolClicked);
    connect(mLineTool, &QToolButton::clicked, this, &Sketcher::onLineToolClicked);
    connect(mTriangleTool, &QToolButton::clicked, this, &Sketcher::onTriangleToolClicked);
    connect(mRectangleTool, &QToolButton::clicked, this, &Sketcher::onRectangleToolClicked);
    connect(mCircleTool, &QToolButton::clicked, this, &Sketcher::onCircleToolClicked);
    connect(mPolygonTool, &QToolButton::clicked, this, &Sketcher::onPolygonToolClicked);
    connect(mPolyLineTool, &QToolButton::clicked, this, &Sketcher::onPolyLineToolClicked);

  /* connect(mAxesTool, &QToolButton::clicked, this, &Sketcher::drawAxesTool);

    connect(newAction, &QAction::triggered, this, &Sketcher::onNewActionTriggered); 
    connect(openAction, &QAction::triggered, this, &Sketcher::onOpenActionTriggered);
    connect(saveAction, &QAction::triggered, this, &Sketcher::onSaveActionTriggered);
    
    connect(cleanAction, &QAction::triggered, this, &Sketcher::onCleanActionTriggered);
    connect(undoAction, &QAction::triggered, this, &Sketcher::onUndoActionTriggered);
    connect(redoAction, &QAction::triggered, this, &Sketcher::onRedoActionTriggered);*/

	//connect(mCanvas, &QGraphicsView::setMouseTracking, this, &Sketcher::mouseMoveEvent);

}

void Sketcher::drawConnectedPoints(std::vector<Point> p)
{

    if (p.size() > 36)
    {
        p.erase(p.begin());
        p.erase(p.begin());
    }
    QPolygonF shape;
    for (int i = 0; i < p.size(); i++) {
        shape << QPointF(p[i].x, p[i].y);
    }
    QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
    item->setPen(QPen(Qt::black, 2));
    mScene->addItem(item);
}


// --- Slots for drawing ---
void Sketcher::finishShape() {
    if (mCurrentTool == ToolType::Polygon && tempPoints.size() >= 3) {
        Polygons* poly = new Polygons(tempPoints);
        std::vector<Point> pts = poly->getCoordinates();
        QPolygonF shape;
        for (int i = 0; i < pts.size(); i++) {
            shape << QPointF(pts[i].x, pts[i].y);
        }
        QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
        item->setPen(QPen(Qt::black, 2));
        mScene->addItem(item);
        mShapes[6].push_back(poly);
        mUndoRedo->recordAdd(item, poly);
    }
    else if (mCurrentTool == ToolType::PolyLine && tempPoints.size() >= 2) {
        PolyLine* pl = new PolyLine(tempPoints);
        std::vector<Point> pts = pl->getCoordinates();

        QPainterPath path;
        path.moveTo(pts[0].x, pts[0].y);
        for (size_t i = 1; i < pts.size(); ++i) {
            path.lineTo(pts[i].x, pts[i].y);
        }

        QGraphicsPathItem* item = new QGraphicsPathItem(path);
        QPen pen(Qt::black, 2);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setCapStyle(Qt::RoundCap);
        item->setPen(pen);
        mScene->addItem(item);
        mShapes[7].push_back(pl);
        mUndoRedo->recordAdd(item, pl);
    }

    tempPoints.clear();
}

void Sketcher::cancelShape() {
    tempPoints.clear();
}


void Sketcher::handleCanvasClick(QPointF pos) {
    Point p(pos.x(), pos.y());

    switch (mCurrentTool) {
    case ToolType::Point: {
        QBrush brush(QColor("#3DB9E7"));
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem(p.x - 2, p.y - 2, 4, 4);
        item->setPen(QPen(Qt::transparent));
        item->setBrush(brush);
        mScene->addItem(item);
        mShapes[1].push_back(p);
        mUndoRedo->recordAdd(item, p);
        break;
    }
    case ToolType::Line:
        tempPoints.push_back(p);
        if (tempPoints.size() == 2) {
            Line* l = new Line(tempPoints[0], tempPoints[1]);
            std::vector<Point> p = l->getCoordinates();
            QPolygonF shape;
            for (int i = 0; i < p.size(); i++) {
                shape << QPointF(p[i].x, p[i].y);
            }
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
            item->setPen(QPen(Qt::black, 2));
            mScene->addItem(item);
            mShapes[2].push_back(l);
            mUndoRedo->recordAdd(item, l);
            tempPoints.clear();
        }
        break;

    case ToolType::Triangle:
        tempPoints.push_back(p);
        if (tempPoints.size() == 3) {
            Triangle* t = new Triangle(tempPoints[0], tempPoints[1], tempPoints[2]);
            std::vector<Point> p = t->getCoordinates();
            QPolygonF shape;
            for (int i = 0; i < p.size(); i++) {
                shape << QPointF(p[i].x, p[i].y);
            }
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
            item->setPen(QPen(Qt::black, 2));
            mScene->addItem(item);
            mShapes[3].push_back(t);
            mUndoRedo->recordAdd(item, t);
            tempPoints.clear();
        }
        break;

    case ToolType::Rectangle:
        tempPoints.push_back(p);
        if (tempPoints.size() == 2) {
            Rectangles* r = new Rectangles(tempPoints[0], tempPoints[1]);
            std::vector<Point> p = r->getCoordinates();
            QPolygonF shape;
            for (int i = 0; i < p.size(); i++) {
                shape << QPointF(p[i].x, p[i].y);
            }
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
            item->setPen(QPen(Qt::black, 2));
            mScene->addItem(item);
            mShapes[4].push_back(r);
            mUndoRedo->recordAdd(item, r);
            tempPoints.clear();
        }
        break;

    case ToolType::Circle:
        tempPoints.push_back(p);
        if (tempPoints.size() == 2) {
            Circle* c = new Circle(tempPoints[0], tempPoints[1]);
            std::vector<Point> p = c->getCoordinates();
            p.erase(p.begin());
            p.erase(p.begin());
            QPolygonF shape;
            for (int i = 0; i < p.size(); i++) {
                shape << QPointF(p[i].x, p[i].y);
            }
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
            item->setPen(QPen(Qt::black, 2));
            mScene->addItem(item);
            mShapes[5].push_back(c);
            mUndoRedo->recordAdd(item, c);
            tempPoints.clear();
        }
        break;

    case ToolType::Polygon:
    case ToolType::PolyLine:
        // here you can collect multiple clicks until user presses "Enter" or right-clicks
        tempPoints.push_back(p);
        break; 

    default: break;
    }
}

// --- Slots for drawing ---

void Sketcher::onPointToolClicked()
{
    mCurrentTool = ToolType::Point;
}

void Sketcher::onLineToolClicked()
{
    mCurrentTool = ToolType::Line;
}

void Sketcher::onTriangleToolClicked()
{
    mCurrentTool = ToolType::Triangle;
}

void Sketcher::onRectangleToolClicked()
{
    mCurrentTool = ToolType::Rectangle;
}

void Sketcher::onCircleToolClicked()
{
    mCurrentTool = ToolType::Circle;
}

void Sketcher::onPolygonToolClicked()
{
    mCurrentTool = ToolType::Polygon;
}

void Sketcher::onPolyLineToolClicked()
{
    mCurrentTool = ToolType::PolyLine;
}