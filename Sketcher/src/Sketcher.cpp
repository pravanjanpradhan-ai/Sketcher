#include "stdafx.h"
#include "Sketcher.h"
#include <QString>
#include <QIcon>
#include <QSize>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainterPath>
#include <QStatusBar>
#include <QLabel>
#include <QMouseEvent>
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
    //mCanvas = new QGraphicsView(mScene, mCentralWidget);
    mCanvas = new CanvasView(mScene, mCentralWidget);
    static_cast<CanvasView*>(mCanvas)->setSketcher(this);
    mCentralgridWidget->addWidget(mCanvas, 0, 0);
    setCentralWidget(mCentralWidget);
    mCanvas->scale(1, -1);
    /*QVBoxLayout* layout = new QVBoxLayout(mCentralWidget);
    layout->addWidget(mCanvas);*/
   
  //  mScene->addRect(0, 0, 400, 300);

     //Add a grid for reference
    int width = 2000;
    int height = 2000;
    for (int x = -width; x <= width; x += 50)
        mScene->addLine(x, -width, x, width, QPen(Qt::lightGray));
    for (int y = -height; y <= height; y += 50)
        mScene->addLine(-height, y, height, y, QPen(Qt::lightGray));


    // File Menu
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* newAction = fileMenu->addAction(this->style()->standardIcon(QStyle::SP_FileIcon), "New");
    newAction->setShortcut(QKeySequence::New);   // Ctrl+N
    QAction* openAction = fileMenu->addAction(this->style()->standardIcon(QStyle::SP_DirOpenIcon), "Open");
    openAction->setShortcut(QKeySequence::Open);   // Ctrl+O
    QAction* saveAction = fileMenu->addAction(this->style()->standardIcon(QStyle::SP_DialogSaveButton), "Save");
    saveAction->setShortcut(QKeySequence::Save);   // Ctrl+S


    // Edit Menu
    QMenu* editMenu = menuBar()->addMenu("Edit");
    QAction* cleanAction = editMenu->addAction(this->style()->standardIcon(QStyle::SP_TrashIcon), "Clean");
    cleanAction->setShortcut(Qt::CTRL | Qt::Key_X); // Ctrl+X
    QAction* undoAction = editMenu->addAction(this->style()->standardIcon(QStyle::SP_ArrowBack), "Undo");
    undoAction->setShortcut(QKeySequence::Undo);   // Ctrl+Z
    QAction* redoAction = editMenu->addAction(this->style()->standardIcon(QStyle::SP_ArrowForward), "Redo");
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
    mAxesTool->setIcon(QIcon(":/Sketcher/PolyLine.png"));
    mAxesTool->setIconSize(QSize(32, 32));
    mAxesTool->setToolTip("PolyLine");
    mToolBar->addWidget(mAxesTool);



    setMouseTracking(true);
    if (mCentralWidget)
        mCentralWidget->setMouseTracking(true);

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
   // connect(mAxesTool, &QToolButton::clicked, this, &Sketcher::drawAxesTool);
   //connect(mCanvas, &QGraphicsScene::mouseMoved, this, &Sketcher::mouseMoveEvent);
   //connect(mCanvas, SIGNAL(mouseMovedOnScene(QPointF)), this, SLOT(updateMousePosition(QPointF)));
    connect(mPolygonTool, &QToolButton::clicked, this, &Sketcher::onPolygonToolClicked);
    connect(mPolyLineTool, &QToolButton::clicked, this, &Sketcher::onPolyLineToolClicked);

    connect(newAction, &QAction::triggered, this, &Sketcher::onNewActionTriggered); 
    connect(openAction, &QAction::triggered, this, &Sketcher::onOpenActionTriggered);
    connect(saveAction, &QAction::triggered, this, &Sketcher::onSaveActionTriggered);
    
    connect(cleanAction, &QAction::triggered, this, &Sketcher::onCleanActionTriggered);
   // connect(undoAction, &QAction::triggered, this, &Sketcher::onUndoActionTriggered);
   // connect(redoAction, &QAction::triggered, this, &Sketcher::onRedoActionTriggered);
}


void Sketcher::mouseMoveEvent(QMouseEvent* event)
{
    // Check if mouse is over the canvas
    QPoint viewPos = mCanvas->mapFromParent(event->pos());
    if (mCanvas->rect().contains(viewPos)) {
        // Map to scene coordinates
        QPointF scenePos = mCanvas->mapToScene(viewPos);
        int x = static_cast<int>(scenePos.x());
        int y = static_cast<int>(scenePos.y());
        mStatusLabel->setText(QString("X: %1, Y: %2").arg(x).arg(y));
    }
    else {
        mStatusLabel->setText("X: -, Y: -");
    }

    QMainWindow::mouseMoveEvent(event);
}
//void Sketcher::mouseMoveEvent(QMouseEvent* event)
//{
//    int x = event->pos().x();
//    int y = event->pos().y();
//    posLabel->setText(QString("X: %1, Y: %2").arg(x).arg(y));
//}

void Sketcher::drawConnectedPoints(std::vector<Point> p, Shape* shapes)
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
    mShapes[mShapeId++].push_back(shapes);
    mUndoRedo->recordAdd(item, shapes);
}

void Sketcher::drawAxesTool()
{
	//int width = this->size().width();
	//int height = this->size().height();

    int width = 2000;
    int height = 2000;
	double x1 = -width ;
	double y1 = 0;
	double x2 = width;
	double y2 = 0;
    Point px1(x1, y1);
    Point px2(x2, y2);
    Line* xAxes = new Line(px1, px2);
    std::vector<Point> px = xAxes->getCoordinates();
    drawConnectedPoints(px, xAxes);
	/*QGraphicsPolygonItem* itemX = new QGraphicsPolygonItem(xAxes);  
   itemX->setPen(QPen(Qt::blue, 1));
  mScene->addItem(itemX);*/


	double x3 = 0;
	double y3 = -height;
	double x4 = 0;
    double y4 = height;
    Point py1(x3, y3);
    Point py2(x4, y4);
    Line* yAxes = new Line(py1, py2);
    std::vector<Point> py = yAxes->getCoordinates();
	drawConnectedPoints(py, yAxes);
	/*QGraphicsPolygonItem* itemY = new QGraphicsPolygonItem(yAxes);
	itemY->setPen(QPen(Qt::blue, 1));
	mScene->addItem(itemY);*/


    // Draw origin point
        Point origin(0, 0);
    QBrush brush(QColor("#FF0000"));
    QGraphicsEllipseItem* itemOrigin = new QGraphicsEllipseItem(origin.x - 3, origin.y - 3, 6, 6);
    itemOrigin->setPen(QPen(Qt::transparent));   // border color
    itemOrigin->setBrush(brush);
    mScene->addItem(itemOrigin);

}

// --- Slots for drawing ---
void Sketcher::finishShape() {
    if (mCurrentTool == ToolType::Polygon && tempPoints.size() >= 3) {
        Polygons* poly = new Polygons(tempPoints);
        drawConnectedPoints(poly->getCoordinates(), poly);
    }
    else if (mCurrentTool == ToolType::PolyLine && tempPoints.size() >= 2) {
        PolyLine* pl = new PolyLine(tempPoints);

void Sketcher::onPointToolClicked()
{
    double x = QInputDialog::getDouble(this, "Point", "Enter X coordinate:", 0, -10000, 10000, 2);
    double y = QInputDialog::getDouble(this, "Point", "Enter Y coordinate:", 0, -10000, 10000, 2);
    Point p(x, y);
    QBrush brush(QColor("#3DB9E7"));
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(p.x - 2, p.y - 2, 4, 4);
    item->setPen(QPen(Qt::transparent));   // border color
    item->setBrush(brush);
    
   // mScene->addItem(item);
    mShapes[mShapeId++].push_back(p);
    mUndoRedo->recordData(mShapes);
}
        QPainterPath path;
        path.moveTo(tempPoints[0].x, tempPoints[0].y);
        for (size_t i = 1; i < tempPoints.size(); ++i) {
            path.lineTo(tempPoints[i].x, tempPoints[i].y);
        }

        QGraphicsPathItem* item = new QGraphicsPathItem(path);
        QPen pen(Qt::black, 2);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setCapStyle(Qt::RoundCap);
        item->setPen(pen);
        mScene->addItem(item);
        mShapes[mShapeId++].push_back(pl);
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
        auto* item = new QGraphicsEllipseItem(p.x - 2, p.y - 2, 4, 4);
        item->setPen(QPen(Qt::transparent));
        item->setBrush(brush);
        mScene->addItem(item);
        mShapes[mShapeId++].push_back(p);
        mUndoRedo->recordAdd(item, p);
        break;
    }
    case ToolType::Line:
        tempPoints.push_back(p);
        if (tempPoints.size() == 2) {
            Line* l = new Line(tempPoints[0], tempPoints[1]);
            auto coords = l->getCoordinates();
            drawConnectedPoints(coords, l);
            tempPoints.clear();
        }
        break;

    case ToolType::Triangle:
        tempPoints.push_back(p);
        if (tempPoints.size() == 3) {
            Triangle* t = new Triangle(tempPoints[0], tempPoints[1], tempPoints[2]);
            auto coords = t->getCoordinates();
            drawConnectedPoints(coords, t);
            tempPoints.clear();
        }
        break;

    case ToolType::Rectangle:
        tempPoints.push_back(p);
        if (tempPoints.size() == 2) {
            Rectangles* r = new Rectangles(tempPoints[0], tempPoints[1]);
            auto coords = r->getCoordinates();
            drawConnectedPoints(coords, r);
            tempPoints.clear();
        }
        break;

    case ToolType::Circle:
        tempPoints.push_back(p);
        if (tempPoints.size() == 2) {
            Circle* c = new Circle(tempPoints[0], tempPoints[1]);
            auto coords = c->getCoordinates();
            drawConnectedPoints(coords, c);
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
        this, "Open Shapes", "", "Text Files (*.txt)");

    if (mfilename.isEmpty())
        return;

    std::string filename = mfilename.toStdString();

    // Create a new Sketcher window
    Sketcher* newWindow = new Sketcher();
    newWindow->show();

    // Load shapes into new window
    FileWrite input;
    if (!input.read(filename, newWindow->mShapes)) {
        QMessageBox::warning(this, "Error", "Failed to open file!");
        newWindow->close();
        return;
    }

    // Draw loaded shapes into new window's scene
    for (const auto& pair : newWindow->mShapes) {
        for (const auto& item : pair.second) {
            if (std::holds_alternative<Shape*>(item)) {
                Shape* shape = std::get<Shape*>(item);
                if (shape) {
                    std::vector<Point> p = shape->getCoordinates();
                    //newWindow->drawConnectedPoints(p, shape);
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
                    newWindow->mScene->addItem(item);
                }
            }
            else if (std::holds_alternative<Point>(item)) {
                Point pt = std::get<Point>(item);
                QBrush brush(QColor("#3DB9E7"));
                //newWindow->mScene->addEllipse(pt.x - 2, pt.y - 2, 4, 4,
                   // QPen(Qt::transparent), brush);
            }
        }
    }

    QMessageBox::information(this, "Opened", "Shapes loaded successfully!");
}

void Sketcher::onSaveActionTriggered()
{
    QString mfilename = QFileDialog::getSaveFileName(
        this, "Save Shapes", "", "Text Files (*.txt)");

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

    // Clear scene
   // mScene->clear();
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

//void Sketcher::onUndoActionTriggered() {
//    mUndoRedo->undo(mScene, mShapes);
//}
void Sketcher::onUndoActionTriggered() {
    if (mUndoRedo->canUndo()) {
        mUndoRedo->undo(mScene);
    }
}

//void Sketcher::onRedoActionTriggered() {
//    mUndoRedo->redo(mScene, mShapes);
//}
void Sketcher::onRedoActionTriggered() {
    if (mUndoRedo->canRedo()) {
        mUndoRedo->redo(mScene);
    }
}