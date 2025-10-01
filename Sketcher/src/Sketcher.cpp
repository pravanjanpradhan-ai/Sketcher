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
    drawAxesTool();
    //mouseMoveEvent();

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

    connect(mAxesTool, &QToolButton::clicked, this, &Sketcher::drawAxesTool);

    connect(newAction, &QAction::triggered, this, &Sketcher::onNewActionTriggered); 
    connect(openAction, &QAction::triggered, this, &Sketcher::onOpenActionTriggered);
    connect(saveAction, &QAction::triggered, this, &Sketcher::onSaveActionTriggered);
    
    connect(cleanAction, &QAction::triggered, this, &Sketcher::onCleanActionTriggered);
    connect(undoAction, &QAction::triggered, this, &Sketcher::onUndoActionTriggered);
    connect(redoAction, &QAction::triggered, this, &Sketcher::onRedoActionTriggered);

   // connect(redoAction, &QGraphicsView::triggered, this, &Sketcher::mouseMoveEvent);
	//connect(mCanvas, &QGraphicsView::setMouseTracking, this, &Sketcher::mouseMoveEvent);
}

void Sketcher::mouseMoveEvent(QMouseEvent* event)
{
 
    QPointF scenePos = mCanvas->mapToScene(event->pos());
    int x = event->pos().x();
    int y = event->pos().y();
    mStatusLabel->setText(QString("Scene X: %1, Y: %2").arg(x).arg(y));
}


//void Sketcher::mouseMoveEvent(QMouseEvent* event)
//{
//    // Check if mouse is over the canvas
//    QPoint viewPos = mCanvas->mapFromParent(event->pos());
//    if (mCanvas->rect().contains(viewPos)) {
//        // Map to scene coordinates
//        QPointF scenePos = mCanvas->mapToScene(viewPos);
//        int x = event->pos().x();
//        int y = event->pos().y();
//       /* int x = static_cast<int>(scenePos.x());
//        int y = static_cast<int>(scenePos.y());*/
//        mStatusLabel->setText(QString("X: %1, Y: %2").arg(x).arg(y));
//    }
//    else {
//        mStatusLabel->setText("X: -, Y: -");
//    }
//
//    QMainWindow::mouseMoveEvent(event);
//}
// 


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

void Sketcher::drawAxesTool()
{
    //Add a grid for reference
    int width = 20000;
    int height = 20000;
    //addLine(x1, y1, x2, y2), pen).
    for (int x = -width; x <= width; x += 50)
        mScene->addLine(x, -width, x, width, QPen(Qt::lightGray));
    for (int y = -height; y <= height; y += 50)
        mScene->addLine(-height, y, height, y, QPen(Qt::lightGray));

    // Axes lines
    mScene->addLine(-width, 0, width, 0, QPen(Qt::black));
    mScene->addLine(0, -height, 0, height, QPen(Qt::black));

	// Axes lines
	/*double x1 = -width ;
	double y1 = 0;
	double x2 = width;
	double y2 = 0;
    Point px1(x1, y1);
    Point px2(x2, y2);
    Line* xAxes = new Line(px1, px2);
    std::vector<Point> px = xAxes->getCoordinates();
    QPolygonF shapeX;
    for (int i = 0; i < px.size(); i++) {
        shapeX << QPointF(px[i].x, px[i].y);
    }
    QGraphicsPolygonItem* itemX = new QGraphicsPolygonItem(shapeX);
    itemX->setPen(QPen(Qt::blue, 1));
    mScene->addItem(itemX);

	double x3 = 0;
	double y3 = -height;
	double x4 = 0;
    double y4 = height;
    Point py1(x3, y3);
    Point py2(x4, y4);
    Line* yAxes = new Line(py1, py2);
    std::vector<Point> py = yAxes->getCoordinates();
    QPolygonF shapeY;
    for (int i = 0; i < py.size(); i++) {
        shapeY << QPointF(py[i].x, py[i].y);
    }
	QGraphicsPolygonItem* itemY = new QGraphicsPolygonItem(shapeY);
	itemY->setPen(QPen(Qt::blue, 1));
	mScene->addItem(itemY);*/

    // Draw origin point
    Point origin(0, 0);
    QBrush brush(QColor("#FF0000"));
    QGraphicsEllipseItem* itemOrigin = new QGraphicsEllipseItem(origin.x - 2, origin.y - 2, 4, 4);
    itemOrigin->setPen(QPen(Qt::transparent));   // border color
    itemOrigin->setBrush(brush);
    mScene->addItem(itemOrigin);

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

void Sketcher::onNewActionTriggered()
{
    if (!mShapes.empty() && !isSave) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(
            this,
            "Save Shapes",
            "Do you want to save your current shapes before starting a new sketch?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );

        if (reply == QMessageBox::Yes) {
            // Call your existing save slot
            onSaveActionTriggered();
        }
        else if (reply == QMessageBox::Cancel) {
            return;
        }
        // if No → continue without saving
    }

    mScene->clear();

    // Delete logical shapes
    for (auto& [id, vec] : mShapes) {
        for (auto& item : vec) {
            if (std::holds_alternative<Shape*>(item)) {
                delete std::get<Shape*>(item);
            }
        }
    }
    mShapes.clear();
    mShapeId = 0;
}

void Sketcher::onOpenActionTriggered()
{
    QString mfilename = QFileDialog::getOpenFileName(
        this, "Open Shapes", "", "Sketcher Files (*.skt)");

    if (mfilename.isEmpty())
        return;

    std::string filename = mfilename.toStdString();

    FileWrite input;
    if (!input.read(filename, mShapes)) {
        QMessageBox::warning(this, "Error", "Failed to open file!");
        return;
    }

    // Draw loaded shapes into new window's scene
    for (const auto& pair : mShapes) {
        for (const auto& item : pair.second) {
            if (std::holds_alternative<Shape*>(item)) {
                Shape* shape = std::get<Shape*>(item);
                if (shape) {
                    std::vector<Point> p = shape->getCoordinates();
                    if (shape->getName() == "PolyLine") {
                        QPainterPath path;
                        path.moveTo(p[0].x, p[0].y);
                        for (size_t i = 1; i < p.size(); ++i) {
                            path.lineTo(p[i].x, p[i].y);
                        }

                        QGraphicsPathItem* item = new QGraphicsPathItem(path);
                        QPen pen(Qt::black, 2);
                        pen.setJoinStyle(Qt::RoundJoin);
                        pen.setCapStyle(Qt::RoundCap);
                        item->setPen(pen);
                        mScene->addItem(item);
                    }
                    else drawConnectedPoints(p);
                }
            }
            else if (std::holds_alternative<Point>(item)) {
                Point pt = std::get<Point>(item);
                QBrush brush(QColor("#3DB9E7"));
                mScene->addEllipse(pt.x - 2, pt.y - 2, 4, 4,
                    QPen(Qt::transparent), brush);
            }
        }
    }

    QMessageBox::information(this, "Opened", "Shapes loaded successfully!");
}

void Sketcher::onSaveActionTriggered()
{
    QString mfilename = QFileDialog::getSaveFileName(
        this, "Save Shapes", "", "Sketcher Files (*.skt)");

    if (!mfilename.isEmpty()) {
        std::string filename = mfilename.toStdString();
        FileWrite output;
        output.write(filename, mShapes);
        QMessageBox::information(this, "Saved", "Shapes saved successfully!");
        isSave = true;
    }
}

void Sketcher::onCleanActionTriggered()
{
    if (!mShapes.empty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(
            this,
            "Clean All",
            "Are you sure you want to remove all shapes?",
            QMessageBox::Yes | QMessageBox::No
        );
        if (reply != QMessageBox::Yes)
            return;
    }

    // Collect all current items into a snapshot
    std::vector<Action> snapshot;
    for (auto& [id, vec] : mShapes) {
        for (auto& item : vec) {
            if (std::holds_alternative<Point>(item)) {
                Point p = std::get<Point>(item);
                QBrush brush(QColor("#3DB9E7"));
                QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(p.x - 2, p.y - 2, 4, 4);
                ellipse->setPen(QPen(Qt::transparent));
                ellipse->setBrush(brush);
                snapshot.push_back({ ActionType::AddItem, ellipse, p, {} });
            }
            else if (std::holds_alternative<Shape*>(item)) {
                Shape* s = std::get<Shape*>(item);
                if (s) {
                    std::vector<Point> p = s->getCoordinates();
                    if (p.size() > 36)
                    {
                        p.erase(p.begin());
                        p.erase(p.begin());
                    }
                    QPolygonF shape;
                    for (int i = 0; i < p.size(); i++) {
                        shape << QPointF(p[i].x, p[i].y);
                    }
                    QGraphicsPolygonItem* poly = new QGraphicsPolygonItem(shape);
                    poly->setPen(QPen(Qt::black, 2));
                    snapshot.push_back({ ActionType::AddItem, poly, s, {} });
                }
            }
        }
    }

    // Record clear action
    mUndoRedo->recordClear(snapshot);

    // Now actually clear scene
    mScene->clear();

    // Delete logical shapes
    for (auto& [id, vec] : mShapes) {
        for (auto& item : vec) {
            if (std::holds_alternative<Shape*>(item)) {
                delete std::get<Shape*>(item);
            }
        }
    }
    mShapes.clear();
    mShapeId = 0;
}

void Sketcher::onUndoActionTriggered() {
    if (mUndoRedo->canUndo()) {
        mUndoRedo->undo(mScene);
    }
}

void Sketcher::onRedoActionTriggered() {
    if (mUndoRedo->canRedo()) {
        mUndoRedo->redo(mScene);
    }
}