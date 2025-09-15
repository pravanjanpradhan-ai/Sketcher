#pragma once

#include <QtWidgets/QMainWindow>


class Sketcher : public QMainWindow
{
    Q_OBJECT

public:
    Sketcher(QWidget* parent = nullptr);
    ~Sketcher();

private:
    void setupUI();

public:
    QWidget* mCentralWidget;
    QGridLayout* mCentralgridWidget;
    QToolBar* mToolBar;
    QToolButton* mPointTool;
    QToolButton* mLineTool;
    QToolButton* mTriangleTool;
    QToolButton* mRectabgleTool;
    QToolButton* mCircleTool;
};