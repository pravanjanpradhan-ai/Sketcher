#include "stdafx.h"
#include"MyGraphicsView.h"


MyGraphicsView::MyGraphicsView(QWidget* parent)
	: QGraphicsView(parent) {
	setRenderHint(QPainter::Antialiasing);
	// Added such that shapes are not blurry when zoomed.
	setDragMode(QGraphicsView::NoDrag);
	// NODrag to implement custom panning we can use middle mouse button, ScrollHandDrag can be used for pannng with left mouse button
	// There are some other options as well like.
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	// Zoom around mouse cursor
	setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}
void MyGraphicsView::wheelEvent(QWheelEvent* event) {
	// simple step zoom with mouse wheel
	const double factor = 1.15;
	if (event->angleDelta().y() > 0) {
		scale(factor, factor); // zoom in (when wheel is scrolled up and it is taken as +ve) 
	}
	else {
		scale(1.0 / factor, 1.0 / factor); // zoom out (when wheel is scrolled up and it is taken as -ve)
	}
}
void MyGraphicsView::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::MiddleButton) {
		m_panning = true;
		m_lastPanPoint = event->pos();
		setCursor(Qt::ClosedHandCursor);
		event->accept();
		return;
	}
	QGraphicsView::mousePressEvent(event);
}
void MyGraphicsView::mouseMoveEvent(QMouseEvent* event) {
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