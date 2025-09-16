#include "stdafx.h"
#include "Sketcher.h"
#include "Point.cpp"
#include "Line.cpp"
#include "Triangle.cpp"
#include "Rectangles.cpp"
#include "Circle.cpp"
#include "Shape.cpp"

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

    mRectangleTool = new QToolButton(mToolBar);
    mRectangleTool->setText("Rectangle");
    mToolBar->addWidget(mRectangleTool);

    mCircleTool = new QToolButton(mToolBar);
    mCircleTool->setText("Circle");
    mToolBar->addWidget(mCircleTool);

    mXLineEdit = new QLineEdit(mCentralWidget);
    mXLineEdit->setPlaceholderText("X1");
    mCentralgridWidget->addWidget(mXLineEdit, 0, 0);  

    mYLineEdit = new QLineEdit(mCentralWidget);
    mYLineEdit->setPlaceholderText("Y1");
    mCentralgridWidget->addWidget(mYLineEdit, 0, 1);

    mXLineEdit2 = new QLineEdit(mCentralWidget);
    mXLineEdit2->setPlaceholderText("X2");
    mCentralgridWidget->addWidget(mXLineEdit2, 1, 0);

    mYLineEdit2 = new QLineEdit(mCentralWidget);
    mYLineEdit2->setPlaceholderText("Y2");
    mCentralgridWidget->addWidget(mYLineEdit2, 1, 1);

    mXLineEdit3 = new QLineEdit(mCentralWidget);
    mXLineEdit3->setPlaceholderText("X3");
    mCentralgridWidget->addWidget(mXLineEdit3, 2, 0);

    mYLineEdit3 = new QLineEdit(mCentralWidget);
    mYLineEdit3->setPlaceholderText("Y3");
    mCentralgridWidget->addWidget(mYLineEdit3, 2, 1);

    mLabel = new QLabel(mCentralWidget);
    mLabel->setText("Coordinates:");
    mCentralgridWidget->addWidget(mLabel, 3, 0, 1, 2); 

    connect(mPointTool, &QToolButton::clicked, this, [=]() {
        bool okX, okY;
        double x = mXLineEdit->text().toDouble(&okX);
        double y = mYLineEdit->text().toDouble(&okY);

        Point p(x, y);
        
        if (okX && okY) {
            mLabel->setText(QString("%1, %2").arg(p.x).arg(p.y));
        }
        else {
            mLabel->setText("Invalid input. Please enter valid numbers.");
        }
    });

    connect(mLineTool, &QToolButton::clicked, this, [=]() {
        bool okX, okY;
        double x1 = mXLineEdit->text().toDouble(&okX);
        double y1 = mYLineEdit->text().toDouble(&okY);
        double x2 = mXLineEdit2->text().toDouble(&okX);
        double y2 = mYLineEdit2->text().toDouble(&okY);

        Point p1(x1, y1);
        Point p2(x2, y2);
        Line l(p1, p2);
        if (okX && okY) {
            QString text;
            for (int i = 0; i < l.getPoints().size(); i++) {
                text += QString("%1, %2\n").arg(l.getPoints()[i].x).arg(l.getPoints()[i].y);
            }
            mLabel->setText(text);
        }
        else {
            mLabel->setText("Invalid input. Please enter valid numbers.");
        }
    });

    connect(mTriangleTool, &QToolButton::clicked, this, [=]() {
        bool okX, okY;
        double x1 = mXLineEdit->text().toDouble(&okX);
        double y1 = mYLineEdit->text().toDouble(&okY);
        double x2 = mXLineEdit2->text().toDouble(&okX);
        double y2 = mYLineEdit2->text().toDouble(&okY);
        double x3 = mXLineEdit3->text().toDouble(&okX);
        double y3 = mYLineEdit3->text().toDouble(&okY);

        Point p1(x1, y1);
        Point p2(x2, y2);
        Point p3(x3, y3);
        Triangle t(p1, p2, p3);
        if (okX && okY) {
            QString text;
            for (int i = 0; i < t.getPoints().size(); i++) {
                text += QString("%1, %2\n").arg(t.getPoints()[i].x).arg(t.getPoints()[i].y);
            }
            mLabel->setText(text);
        }
        else {
            mLabel->setText("Invalid input. Please enter valid numbers.");
        }
    });

    connect(mRectangleTool, &QToolButton::clicked, this, [=]() {
        bool okX, okY;
        double x1 = mXLineEdit->text().toDouble(&okX);
        double y1 = mYLineEdit->text().toDouble(&okY);
        double x2 = mXLineEdit2->text().toDouble(&okX);
        double y2 = mYLineEdit2->text().toDouble(&okY);

        Point p1(x1, y1);
        Point p2(x2, y2);
        Rectangles r(p1, p2);
        if (okX && okY) {
            QString text;
            for (int i = 0; i < r.getPoints().size(); i++) {
                text += QString("%1, %2\n").arg(r.getPoints()[i].x).arg(r.getPoints()[i].y);
            }
            mLabel->setText(text);
        }
        else {
            mLabel->setText("Invalid input. Please enter valid numbers.");
        }
    });

    connect(mCircleTool, &QToolButton::clicked, this, [=]() {
        bool okX, okY;
        double x1 = mXLineEdit->text().toDouble(&okX);
        double y1 = mYLineEdit->text().toDouble(&okY);
        double x2 = mXLineEdit2->text().toDouble(&okX);
        double y2 = mYLineEdit2->text().toDouble(&okY);

        Point p1(x1, y1);
        Point p2(x2, y2);
        Circle c(p1, p2);
        if (okX && okY) {
            QString text;
            for (int i = 0; i < c.getPoints().size(); i++) {
                text += QString("%1, %2\n").arg(c.getPoints()[i].x).arg(c.getPoints()[i].y);
            }
            mLabel->setText(text);
        }
        else {
            mLabel->setText("Invalid input. Please enter valid numbers.");
        }
    });

}