#include "stdafx.h"
#include "Sketcher.h"
#include <QString>
#include <QIcon>
#include <QSize>
#include <QInputDialog>
#include <QMessageBox>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
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
    mCentralgridWidget->addWidget(mCanvas, 0, 0);
    setCentralWidget(mCentralWidget);

    // File Menu
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* newAction = fileMenu->addAction("New");
    newAction->setShortcut(QKeySequence::New);   // Ctrl+N
    QAction* openAction = fileMenu->addAction("Open");
    openAction->setShortcut(QKeySequence::Open);   // Ctrl+O
    QAction* saveAction = fileMenu->addAction("Save");
    saveAction->setShortcut(QKeySequence::Save);   // Ctrl+S


    // Edit Menu
    QMenu* editMenu = menuBar()->addMenu("Edit");
    QAction* cleanAction = editMenu->addAction("Clean");
    cleanAction->setShortcut(Qt::CTRL | Qt::Key_X); // Ctrl+X
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

    // Text
    //QToolButton* Text_btn = new QToolButton(mToolBar);
    //Text_btn->setText("Text");
    //mToolBar->addWidget(Text_btn);

    // Connections
    connect(mPointTool, &QToolButton::clicked, this, &Sketcher::onPointToolClicked);
    connect(mLineTool, &QToolButton::clicked, this, &Sketcher::onLineToolClicked);
    connect(mTriangleTool, &QToolButton::clicked, this, &Sketcher::onTriangleToolClicked);
    connect(mRectangleTool, &QToolButton::clicked, this, &Sketcher::onRectangleToolClicked);
    connect(mCircleTool, &QToolButton::clicked, this, &Sketcher::onCircleToolClicked);

    connect(newAction, &QAction::triggered, this, &Sketcher::onNewActionTriggered);
    connect(openAction, &QAction::triggered, this, &Sketcher::onOpenActionTriggered);
    connect(saveAction, &QAction::triggered, this, &Sketcher::onSaveActionTriggered);

    connect(cleanAction, &QAction::triggered, this, &Sketcher::onCleanActionTriggered);
    connect(undoAction, &QAction::triggered, this, &Sketcher::onUndoActionTriggered);
    connect(redoAction, &QAction::triggered, this, &Sketcher::onRedoActionTriggered);
}

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

// --- Slots for drawing ---

void Sketcher::onPointToolClicked()
{
    double x = QInputDialog::getDouble(this, "Point", "Enter X coordinate:", 0, -10000, 10000, 2);
    double y = QInputDialog::getDouble(this, "Point", "Enter Y coordinate:", 0, -10000, 10000, 2);
    Point p(x, y);
    QBrush brush(QColor("#3DB9E7"));
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(p.x - 2, p.y - 2, 4, 4);
    item->setPen(QPen(Qt::transparent));   // border color
    item->setBrush(brush);
    
    mScene->addItem(item);
    mShapes[mShapeId++].push_back(p);
    mUndoRedo->recordAdd(item, p);
}

void Sketcher::onLineToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Line", "Enter X coordinate of 1st Point:", 0, -10000, 10000, 2);
    double y1 = QInputDialog::getDouble(this, "Line", "Enter Y coordinate of 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Line", "Enter X coordinate of 2nd Point:", 1, -10000, 10000, 2);
    double y2 = QInputDialog::getDouble(this, "Line", "Enter Y coordinate of 2nd Point:", 1, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Line* l = new Line(p1, p2);
    std::vector<Point> p = l->getCoordinates();
    drawConnectedPoints(p, l);
    //mShapes[mShapeId++].push_back(l);
    //mUndoRedo->recordData(mShapes);
}

void Sketcher::onTriangleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate of 1st Point:", 0, -10000, 10000, 2);
    double y1 = QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate of 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate of 2nd Point:", 1, -10000, 10000, 2);
    double y2 = QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate of 2nd Point:", 1, -10000, 10000, 2);
    double x3 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate of 3rd Point:", 0, -10000, 10000, 2);
    double y3 = QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate of 3rd Point:", 1, -10000, 10000, 2);
    Point a(x1, y1);
    Point b(x2, y2);
    Point c(x3, y3);
    Triangle* t = new Triangle(a, b, c);
    std::vector<Point> p = t->getCoordinates();
    drawConnectedPoints(p, t);
    //mShapes[mShapeId++].push_back(t);
    //mUndoRedo->recordData(mShapes);
}

void Sketcher::onRectangleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Rectangle", "Enter X coordinate of 1st Point:", 0, -10000, 10000, 2);
    double y1 = QInputDialog::getDouble(this, "Rectangle", "Enter Y coordinate of 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Rectangle", "Enter X coordinate of 2nd Point:", 1, -10000, 10000, 2);
    double y2 = QInputDialog::getDouble(this, "Rectangle", "Enter Y coordinate of 2nd Point:", 1, -10000, 10000, 2);
    Point a(x1, y1);
    Point c(x2, y2);
    Rectangles* r = new Rectangles(a, c);
    std::vector<Point> p = r->getCoordinates();
    drawConnectedPoints(p, r);
    //mShapes[mShapeId++].push_back(r);
    //mUndoRedo->recordData(mShapes);
}

void Sketcher::onCircleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Circle", "Enter X coordinate of Center:", 0, -10000, 10000, 2);
    double y1 = QInputDialog::getDouble(this, "Circle", "Enter Y coordinate of Center:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Circle", "Enter X coordinate of a circumference Point:", 1, -10000, 10000, 2);
    double y2 = QInputDialog::getDouble(this, "Circle", "Enter Y coordinate of a circumference Point:", 1, -10000, 10000, 2);
    Point Center(x1, y1);
    Point onCircle(x2, y2);
    Circle* c = new Circle(Center, onCircle);
    std::vector<Point> p = c->getCoordinates();
    drawConnectedPoints(p, c);
    //mShapes[mShapeId++].push_back(c);
    //mUndoRedo->recordData(mShapes);
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

    // Open a new Sketcher window
    Sketcher* newWindow = new Sketcher();
    newWindow->show();
    // Close current window
    this->close();
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
                newWindow->mScene->addEllipse(pt.x - 2, pt.y - 2, 4, 4,
                    QPen(Qt::transparent), brush);
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