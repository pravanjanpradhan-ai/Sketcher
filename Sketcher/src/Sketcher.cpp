#include "stdafx.h"
#include "Sketcher.h"
#include <QString>
#include <QIcon>
#include <QSize>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainterPath>
#include "Shape.h"
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
    
    mCentralgridWidget->addWidget(mCanvas,0,0);
	//Mouse click
    mCanvas = new CanvasView(mScene, mCentralWidget);
    mCanvas->setSketcher(this);
    mCanvas->setMouseTracking(true); // important
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