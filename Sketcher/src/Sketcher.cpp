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

    mInstructorLabel = new QLabel(mCentralWidget);
    mInstructorLabel->setText("Select a tool to start drawing.");
    mCentralgridWidget->addWidget(mInstructorLabel, 0, 0, 1, 2);  

    mXLineEdit = new QLineEdit(mCentralWidget);
    mXLineEdit->setPlaceholderText("X");
    mCentralgridWidget->addWidget(mXLineEdit, 1, 0);  

    mYLineEdit = new QLineEdit(mCentralWidget);
    mYLineEdit->setPlaceholderText("Y");
    mCentralgridWidget->addWidget(mYLineEdit, 1, 1);

    mLabel = new QLabel(mCentralWidget);
    mLabel->setText("Coordinates:");
    mCentralgridWidget->addWidget(mLabel, 3, 0, 1, 2); 

    mEnterButton = new QPushButton("Enter", mCentralWidget);
    mCentralgridWidget->addWidget(mEnterButton, 2, 0, 1, 1);

    connect(mPointTool, &QToolButton::clicked, this, [=]() {
        mInstructorLabel->setText("Enter X and Y coordinates for the point.");
    });
	
    connect(mEnterButton, &QPushButton::clicked, this, [=]() {
        bool okX, okY;
        double x = mXLineEdit->text().toDouble(&okX);
        double y = mYLineEdit->text().toDouble(&okY);

        if (okX && okY) {
            mLabel->setText(QString("Point(%1, %2)").arg(x).arg(y));
        }
        else {
            mLabel->setText("Invalid input. Please enter valid numbers.");
        }
    });

}