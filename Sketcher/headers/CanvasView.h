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
	void mousePressEvent(QMouseEvent* event) override; // Rituraj - Takes  mouse click position for coordinates, Pravanjan - panning with middle mouse button
	void keyPressEvent(QKeyEvent* event) override; // for enter - polygon/polyline finish, esc - cancel shape
	void wheelEvent(QWheelEvent* event) override; // zoom with mouse wheel
	void mouseMoveEvent(QMouseEvent* event) override; // panning with middle mouse button
	void mouseReleaseEvent(QMouseEvent* event) override; // stop panning when middle mouse button is released

private:
    bool m_panning = false;
    QPoint m_lastPanPoint;

private:
    Sketcher* mSketcher;
};
