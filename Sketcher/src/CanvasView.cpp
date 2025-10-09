#include "stdafx.h"
#include "CanvasView.h"

CanvasView::CanvasView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent), mSketcher(nullptr) {
    setMouseTracking(true);
}

void CanvasView::setSketcher(Sketcher* s) {
    mSketcher = s;
}

void CanvasView::mousePressEvent(QMouseEvent* event) {

    // pos() - returns the position of the mouse cursor relative to the widget that received the event.
    QPointF pos = mapToScene(event->pos());

    //if (event->button() == Qt::RightButton) {
    //    // Right click -> finish polygon/polyline
    //    mSketcher->finishShape();
    //}
    if (event->button() == Qt::LeftButton) {
        // Left click -> add point
        mDrawShape->handleCanvasClick(pos);
    }
    if (event->button() == Qt::MiddleButton) {
        m_panning = true;
        m_lastPanPoint = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    QGraphicsView::mousePressEvent(event);
}

void CanvasView::wheelEvent(QWheelEvent* event) {
    // simple step zoom with mouse wheel
    const double factor = 1.15;
    if (event->angleDelta().y() > 0) {
        scale(factor, factor); // zoom in (when wheel is scrolled up and it is taken as +ve) 
    }
    else {
        scale(1.0 / factor, 1.0 / factor); // zoom out (when wheel is scrolled up and it is taken as -ve)
    }
}

void CanvasView::mouseMoveEvent(QMouseEvent* event) {
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

void CanvasView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton && m_panning) {
        m_panning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void CanvasView::keyPressEvent(QKeyEvent* event) {

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        mDrawShape->finishShape();
    }
    else if (event->key() == Qt::Key_Escape) {
        mDrawShape->cancelShape();
    }
    else {
        QGraphicsView::keyPressEvent(event);
    }
}
