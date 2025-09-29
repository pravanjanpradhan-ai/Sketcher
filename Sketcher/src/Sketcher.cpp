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

    
}

void Sketcher::onPointToolClicked()
{
	double x = QInputDialog::getDouble(this, "Point", "Enter X coordinate:", 0, -10000, 10000, 2);
	double y = QInputDialog::getDouble(this, "Point", "Enter Y coordinate:", 0, -10000, 10000, 2);  
    Point p1(x, y);
    int radius = 4;

  
    mScene->addEllipse(p1.x - radius / 2, p1.y - radius / 2,
                                              radius, radius,
                                             QPen(Qt::black),
                                             QBrush(Qt::red));
    mShapes[mShapeId++].push_back( p1);

}
void Sketcher::onLineToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Line", "Enter X coordinate for 1st Point:", 0, -10000, 10000, 2);
    double y1 = QInputDialog::getDouble(this, "Line", "Enter Y coordinate for 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Line", "Enter X coordinate for 2nd Point:", 0, -10000, 10000, 2);
    double y2 = QInputDialog::getDouble(this, "Line", "Enter Y coordinate for 2nd Point:", 0, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Line* l1 = new Line(p1, p2);
    std::vector<Point> coord = l1->getCoordinates();
    drawConnectedPoints(coord);
    mShapes[mShapeId++].push_back(l1);
}
void Sketcher::onTriangleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate for 1st Point:", 0, -10000, 10000, 2);
    double y1 = QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate for 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate for 2nd Point:", 0, -10000, 10000, 2);
    double y2 = QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate for 2nd Point:", 0, -10000, 10000, 2);
    double x3 = QInputDialog::getDouble(this, "Triangle", "Enter X coordinate for 3rd Point:", 0, -10000, 10000, 2);
    double y3 = QInputDialog::getDouble(this, "Triangle", "Enter Y coordinate for 3rd Point:", 0, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Point p3(x3, y3);
    Triangle* t= new Triangle(p1, p2, p3);
    std::vector<Point> coord = t->getCoordinates();
    drawConnectedPoints(coord);
    mShapes[mShapeId++].push_back(t);
}

void Sketcher::onRectangleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Rectangle", "Enter X coordinate for 1st Point:", 0, -10000, 10000, 2);
    double y1 = QInputDialog::getDouble(this, "Rectangle", "Enter Y coordinate for 1st Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Rectangle", "Enter X coordinate for 2nd Point:", 0, -10000, 10000, 2);
    double y2 = QInputDialog::getDouble(this, "Rectangle", "Enter Y coordinate for 2nd Point:", 0, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Rectangles* r1 = new Rectangles(p1, p2);
    std::vector<Point> coord = r1->getCoordinates();
    drawConnectedPoints(coord);
    mShapes[mShapeId++].push_back( r1);
    
    
}

void Sketcher::onCircleToolClicked()
{
    double x1 = QInputDialog::getDouble(this, "Circle", "Enter X coordinate for Center Point:", 0, -10000, 10000, 2);
    double y1 = QInputDialog::getDouble(this, "Circle", "Enter Y coordinate for Center Point:", 0, -10000, 10000, 2);
    double x2 = QInputDialog::getDouble(this, "Circle", "Enter X coordinate for a Point on the circumference:", 0, -10000, 10000, 2);
    double y2 = QInputDialog::getDouble(this, "Circle", "Enter Y coordinate for a Point on the circumference:", 0, -10000, 10000, 2);
    Point p1(x1, y1);
    Point p2(x2, y2);
    Circle* c1= new Circle(p1, p2);
    std::vector<Point> coord = c1->getCoordinates();
    drawConnectedPoints(coord);
    mShapes[mShapeId++].push_back(c1);
}

void Sketcher::onNewFile()
{

}

void Sketcher::onOpenFile() 
{

}

void Sketcher::onSaveFile()
{ 

}

void Sketcher::onSaveAsFile()
{

}

// Simple view with pan (middle mouse) and wheel zoom
class MyGraphicsView : public QGraphicsView {
public:
    MyGraphicsView(QWidget* parent = nullptr) : QGraphicsView(parent) {
        setRenderHint(QPainter::Antialiasing);
		// Added such that shapes are not blurry when zoomed.
        setDragMode(QGraphicsView::NoDrag); 
		// NODrag to implement custom panning we can use middle mouse button, ScrollHandDrag can be used for pannng with left mouse button
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        // Zoom around mouse cursor
        setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    }

protected:
    void wheelEvent(QWheelEvent* event) override {
        // simple step zoom
        const double factor = 1.15;
        if (event->angleDelta().y() > 0) {
            scale(factor, factor); // zoom in
        }
        else {
            scale(1.0 / factor, 1.0 / factor); // zoom out
        }
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::MiddleButton) {
            m_panning = true;
            m_lastPanPoint = event->pos();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
        QGraphicsView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (m_panning) {
            // Move the view by the delta in view coordinates
            QPoint delta = event->pos() - m_lastPanPoint;
            m_lastPanPoint = event->pos();
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
            event->accept();
            return;
        }
        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        if (event->button() == Qt::MiddleButton && m_panning) {
            m_panning = false;
            setCursor(Qt::ArrowCursor);
            event->accept();
            return;
        }
        QGraphicsView::mouseReleaseEvent(event);
    }

private:
    bool m_panning = false;
    QPoint m_lastPanPoint;
};


void Sketcher::setupUI() {
    mCentralWidget = new QWidget(this);
    setCentralWidget(mCentralWidget);
    mCentralgridWidget = new QGridLayout(mCentralWidget);
    
    mToolBar = new QToolBar(this);
    addToolBar(mToolBar);

    mGraphicsView = new MyGraphicsView(this);
    mCentralgridWidget->addWidget(mGraphicsView);
    mScene = new QGraphicsScene(this);
    mGraphicsView->setScene(mScene);


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

 
    connect(mPointTool, &QToolButton::clicked, this, &Sketcher::onPointToolClicked);
    connect(mLineTool, &QToolButton::clicked, this, &Sketcher::onLineToolClicked);
    connect(mTriangleTool, &QToolButton::clicked, this, &Sketcher::onTriangleToolClicked);
    connect(mRectangleTool, &QToolButton::clicked, this, &Sketcher::onRectangleToolClicked);
    connect(mCircleTool, &QToolButton::clicked, this, &Sketcher::onCircleToolClicked);

	mMenuBar = new QMenuBar(this);
	setMenuBar(mMenuBar);

	mFileMenu = new QMenu("File", this);
	mMenuBar->addMenu(mFileMenu);

	QAction* newAction = new QAction("New", this);
    mFileMenu->addAction(newAction);
    newAction->setShortcut(QKeySequence::New);   // Ctrl+N
    newAction->setIcon(style()->standardIcon(QStyle::SP_FileIcon));

	QAction* saveAction = new QAction("Save", this);
	mFileMenu->addAction(saveAction);
    saveAction->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    saveAction->setShortcut(QKeySequence::Save);

	QAction* saveAsAction = new QAction("Save As", this);
	mFileMenu->addAction(saveAsAction);
    saveAsAction->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    saveAsAction->setShortcut(QKeySequence::SaveAs);

	QAction* openAction = new QAction("Open", this);  
	mFileMenu->addAction(openAction);
    openAction->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    openAction->setShortcut(QKeySequence::Open);

	mEditMenu = new QMenu("Edit", this);
	mMenuBar->addMenu(mEditMenu);
	QAction* undoAction = new QAction("Undo", this);
    undoAction->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));
	mEditMenu->addAction(undoAction);
    undoAction->setShortcut(QKeySequence::Undo);

	QAction* redoAction = new QAction("Redo", this);
	mEditMenu->addAction(redoAction);
    redoAction->setIcon(style()->standardIcon(QStyle::SP_ArrowForward));
    redoAction->setShortcut(QKeySequence::Redo);

	QAction* clearAction = new QAction("Clear", this);
	mEditMenu->addAction(clearAction);
    clearAction->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
    clearAction->setShortcut(QKeySequence::Cut);
    
}

