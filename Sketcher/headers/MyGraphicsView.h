
#pragma once

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPainter>
#include <QWidget>

// Ensure your class definition starts correctly
class MyGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    MyGraphicsView(QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    bool m_panning = false;
    QPoint m_lastPanPoint;
};