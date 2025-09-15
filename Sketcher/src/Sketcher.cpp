#include "stdafx.h"
#include "Sketcher.h"

Sketcher::Sketcher(QWidget* parent)
    : QMainWindow(parent)
{

    setupUI();
    resize(800, 600);
}

Sketcher::~Sketcher()
{
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

    mRectabgleTool = new QToolButton(mToolBar);
    mRectabgleTool->setText("Rectangle");
    mToolBar->addWidget(mRectabgleTool);

    mCircleTool = new QToolButton(mToolBar);
    mCircleTool->setText("Circle");
    mToolBar->addWidget(mCircleTool);



}