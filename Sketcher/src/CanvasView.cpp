#include "stdafx.h"
#include "CanvasView.h"
#include "Sketcher.h"   // Needed for calling Sketcher methods

CanvasView::CanvasView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent), mSketcher(nullptr) {
    setMouseTracking(true);
}

void CanvasView::setSketcher(Sketcher* s) {
    mSketcher = s;
}

void CanvasView::mousePressEvent(QMouseEvent* event) {
    if (!mSketcher) return;

    QPointF pos = mapToScene(event->pos());

    //if (event->button() == Qt::RightButton) {
    //    // Right click -> finish polygon/polyline
    //    mSketcher->finishShape();
    //}
    if (event->button() == Qt::LeftButton) {
        // Left click -> add point
        mSketcher->handleCanvasClick(pos);
    }
}

void CanvasView::keyPressEvent(QKeyEvent* event) {
    if (!mSketcher) return;

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        mSketcher->finishShape();
    }
    else if (event->key() == Qt::Key_Escape) {
        mSketcher->cancelShape();
    }
    else {
        QGraphicsView::keyPressEvent(event);
    }
}
