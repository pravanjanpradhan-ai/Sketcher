#include "stdafx.h"
#include "DrawShape.h"
#include "Shape.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Polygon.h"
#include "PolyLine.h"

void DrawShape::drawConnectedPoints(std::vector<Point> p)
{

    if (p.size() > 36)
    {
        p.erase(p.begin());
        p.erase(p.begin());
    }
    QPolygonF shape;
    for (int i = 0; i < p.size(); i++) {
        shape << QPointF(p[i].x, p[i].y);
    }
    QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
    item->setPen(QPen(Qt::black, 2));
    mSketcher->mScene->addItem(item);
}


// --- Slots for drawing ---
void DrawShape::finishShape() {
    if (mCurrentTool == ToolType::Polygon && tempPoints.size() >= 3) {
        Polygons* poly = new Polygons(tempPoints);
        std::vector<Point> pts = poly->getCoordinates();
        QPolygonF shape;
        for (int i = 0; i < pts.size(); i++) {
            shape << QPointF(pts[i].x, pts[i].y);
        }
        QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
        item->setPen(QPen(Qt::black, 2));
        mSketcher->mScene->addItem(item);
    }
    else if (mCurrentTool == ToolType::PolyLine && tempPoints.size() >= 2) {
        PolyLine* pl = new PolyLine(tempPoints);
        std::vector<Point> pts = pl->getCoordinates();

        QPainterPath path;
        path.moveTo(pts[0].x, pts[0].y);
        for (size_t i = 1; i < pts.size(); ++i) {
            path.lineTo(pts[i].x, pts[i].y);
        }

        QGraphicsPathItem* item = new QGraphicsPathItem(path);
        QPen pen(Qt::black, 2);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setCapStyle(Qt::RoundCap);
        item->setPen(pen);
        mSketcher->mScene->addItem(item);
    }

    tempPoints.clear();
}

void DrawShape::cancelShape() {
    tempPoints.clear();
}


void DrawShape::handleCanvasClick(QPointF pos) {
    Point p(pos.x(), pos.y());

    switch (mCurrentTool) {
    case ToolType::Point: {
        QBrush brush(QColor("#3DB9E7"));
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem(p.x - 2, p.y - 2, 4, 4);
        item->setPen(QPen(Qt::transparent));
        item->setBrush(brush);
        mSketcher->mScene->addItem(item);
        break;
    }
    case ToolType::Line:
        tempPoints.push_back(p);
        if (tempPoints.size() == 2) {
            Line* l = new Line(tempPoints[0], tempPoints[1]);
            std::vector<Point> p = l->getCoordinates();
            QPolygonF shape;
            for (int i = 0; i < p.size(); i++) {
                shape << QPointF(p[i].x, p[i].y);
            }
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
            item->setPen(QPen(Qt::black, 2));
            mSketcher->mScene->addItem(item);
            tempPoints.clear();
        }
        break;

    case ToolType::Triangle:
        tempPoints.push_back(p);
        if (tempPoints.size() == 3) {
            Triangle* t = new Triangle(tempPoints[0], tempPoints[1], tempPoints[2]);
            std::vector<Point> p = t->getCoordinates();
            QPolygonF shape;
            for (int i = 0; i < p.size(); i++) {
                shape << QPointF(p[i].x, p[i].y);
            }
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
            item->setPen(QPen(Qt::black, 2));
            mSketcher->mScene->addItem(item);
            tempPoints.clear();
        }
        break;

    case ToolType::Rectangle:
        tempPoints.push_back(p);
        if (tempPoints.size() == 2) {
            Rectangles* r = new Rectangles(tempPoints[0], tempPoints[1]);
            std::vector<Point> p = r->getCoordinates();
            QPolygonF shape;
            for (int i = 0; i < p.size(); i++) {
                shape << QPointF(p[i].x, p[i].y);
            }
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
            item->setPen(QPen(Qt::black, 2));
            mSketcher->mScene->addItem(item);
            tempPoints.clear();
        }
        break;

    case ToolType::Circle:
        tempPoints.push_back(p);
        if (tempPoints.size() == 2) {
            Circle* c = new Circle(tempPoints[0], tempPoints[1]);
            std::vector<Point> p = c->getCoordinates();
            p.erase(p.begin());
            p.erase(p.begin());
            QPolygonF shape;
            for (int i = 0; i < p.size(); i++) {
                shape << QPointF(p[i].x, p[i].y);
            }
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(shape);
            item->setPen(QPen(Qt::black, 2));
            mSketcher->mScene->addItem(item);
            tempPoints.clear();
        }
        break;

    case ToolType::Polygon:
    case ToolType::PolyLine:
        // here you can collect multiple clicks until user presses "Enter" or right-clicks
        tempPoints.push_back(p);
        break;

    default: break;
    }
}