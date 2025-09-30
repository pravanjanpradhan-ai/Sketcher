#pragma once

#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>

class Sketcher;  // Forward declaration

class CanvasView : public QGraphicsView {
    Q_OBJECT
public:
    CanvasView(QGraphicsScene* scene, QWidget* parent = nullptr);

    void setSketcher(Sketcher* s);

protected:
	void mousePressEvent(QMouseEvent* event) override; // Rituraj - Takes  mouse click position for coordinates
	void keyPressEvent(QKeyEvent* event) override; // for enter - polygon/polyline finish, esc - cancel shape

private:
    Sketcher* mSketcher;
};
