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
    QToolButton* mRectangleTool;
    QToolButton* mCircleTool;
	QLineEdit* mXLineEdit;
	QLineEdit* mYLineEdit;
    QLineEdit* mXLineEdit2;
    QLineEdit* mYLineEdit2;
    QLineEdit* mXLineEdit3;
    QLineEdit* mYLineEdit3;
	QLabel* mLabel;
    QLabel* mInstructorLabel;
	QPushButton* mEnterButton;
};