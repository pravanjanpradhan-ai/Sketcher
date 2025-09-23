#pragma once
#include <deque>
#include <unordered_map>
#include <variant>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <cmath>
#include <algorithm>
#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

using SketchData = std::variant<Shape*, Point>;

struct ShapeSnapshot {
    enum Kind { LINE, TRIANGLE, RECTANGLE, CIRCLE, POLYGON, POLYLINE, UNKNOWN } kind = UNKNOWN;
    std::vector<Point> params; // parameters needed to recreate the shape
};

using SketchHistoryData = std::variant<Point, ShapeSnapshot>;

class UndoRedoManager {
public:
    enum ActionType { DRAW, CLEAN };

    struct Action {
        ActionType type;
        std::unordered_map<int, std::vector<SketchHistoryData>> snapshot;
    };

private:
    std::deque<Action> undoStack;
    std::deque<Action> redoStack;
    const int MAX_LIMIT = 10;

public:
    // convert live shapes into safe snapshot (no raw Shape* pointers)
    std::unordered_map<int, std::vector<SketchHistoryData>>
    makeSnapshot(const std::unordered_map<int, std::vector<SketchData>>& shapes) {
        std::unordered_map<int, std::vector<SketchHistoryData>> snap;
        for (const auto& [id, vec] : shapes) {
            for (const auto& item : vec) {
                if (std::holds_alternative<Point>(item)) {
                    snap[id].push_back(std::get<Point>(item));
                }
                else if (std::holds_alternative<Shape*>(item)) {
                    Shape* shape = std::get<Shape*>(item);
                    if (!shape) continue; // skip null

                    // prefer to identify concrete type via dynamic_cast when possible
                    if (auto ln = dynamic_cast<Line*>(shape)) {
                        ShapeSnapshot ss; ss.kind = ShapeSnapshot::LINE;
                        ss.params = ln->getCoordinates(); // two end points
                        snap[id].push_back(ss);
                    }
                    else if (auto tr = dynamic_cast<Triangle*>(shape)) {
                        ShapeSnapshot ss; ss.kind = ShapeSnapshot::TRIANGLE;
                        ss.params = tr->getCoordinates();
                        snap[id].push_back(ss);
                    }
                    else if (auto rect = dynamic_cast<Rectangles*>(shape)) {
                        ShapeSnapshot ss; ss.kind = ShapeSnapshot::RECTANGLE;
                        auto pts = rect->getCoordinates();
                        // store two opposite corners if available
                        if (pts.size() >= 4) {
                            ss.params.push_back(pts[0]);
                            ss.params.push_back(pts[2]);
                        } else {
                            ss.params = pts;
                        }
                        snap[id].push_back(ss);
                    }
                    else if (auto circ = dynamic_cast<Circle*>(shape)) {
                        ShapeSnapshot ss; ss.kind = ShapeSnapshot::CIRCLE;
                        auto pts = circ->getCoordinates();
                        if (!pts.empty()) {
                            // compute center by averaging sample points (robust even if Circle stores many sample points)
                            double cx = 0.0, cy = 0.0;
                            for (auto &pp : pts) { cx += pp.x; cy += pp.y; }
                            cx /= pts.size(); cy /= pts.size();
                            Point center(cx, cy);
                            Point onCirc = pts.front();
                            ss.params.push_back(center);
                            ss.params.push_back(onCirc);
                        } else {
                            // fallback: try to use getCoordinates (empty) -> store nothing
                        }
                        snap[id].push_back(ss);
                    }
                    else {
                        // unknown shape: store its coordinates as POLYGON so we can at least redraw
                        ShapeSnapshot ss; ss.kind = ShapeSnapshot::POLYGON;
                        ss.params = shape->getCoordinates();
                        snap[id].push_back(ss);
                    }
                }
            }
        }
        return snap;
    }

    void recordDraw(const std::unordered_map<int, std::vector<SketchData>>& currentShapes) {
        Action act;
        act.type = DRAW;
        act.snapshot = makeSnapshot(currentShapes);
        undoStack.push_back(std::move(act));
        trimUndo();
        redoStack.clear();
    }

    void recordClean(const std::unordered_map<int, std::vector<SketchData>>& beforeClean) {
        Action act;
        act.type = CLEAN;
        act.snapshot = makeSnapshot(beforeClean);
        undoStack.push_back(std::move(act));
        trimUndo();
        redoStack.clear();
    }

    void undo(QGraphicsScene* scene,
        std::unordered_map<int, std::vector<SketchData>>& shapes) {
        if (undoStack.empty()) return;

        Action act = std::move(undoStack.back());
        undoStack.pop_back();

        // save current state for redo
        Action redoAct;
        redoAct.type = act.type;
        redoAct.snapshot = makeSnapshot(shapes);
        redoStack.push_back(std::move(redoAct));
        trimRedo();

        // restore snapshot
        restore(scene, shapes, act.snapshot);
    }

    void redo(QGraphicsScene* scene,
        std::unordered_map<int, std::vector<SketchData>>& shapes) {
        if (redoStack.empty()) return;

        Action act = std::move(redoStack.back());
        redoStack.pop_back();

        // save current state for undo
        Action undoAct;
        undoAct.type = act.type;
        undoAct.snapshot = makeSnapshot(shapes);
        undoStack.push_back(std::move(undoAct));
        trimUndo();

        // restore snapshot
        restore(scene, shapes, act.snapshot);
    }

private:
    void restore(QGraphicsScene* scene,
        std::unordered_map<int, std::vector<SketchData>>& shapes,
        const std::unordered_map<int, std::vector<SketchHistoryData>>& snapshot) {
        // clear scene and free existing shape objects
        scene->clear();

        for (auto& [id, vec] : shapes) {
            for (auto& item : vec) {
                if (std::holds_alternative<Shape*>(item)) {
                    Shape* s = std::get<Shape*>(item);
                    delete s;
                }
            }
        }
        shapes.clear();

        int maxId = -1;
        for (const auto& [id, vec] : snapshot) {
            maxId = std::max(maxId, id);
            for (const auto& item : vec) {
                if (std::holds_alternative<Point>(item)) {
                    Point pt = std::get<Point>(item);
                    QBrush brush(QColor("#3DB9E7"));
                    scene->addEllipse(pt.x - 2, pt.y - 2, 4, 4,
                        QPen(Qt::transparent), brush);
                    shapes[id].push_back(pt);
                }
                else if (std::holds_alternative<ShapeSnapshot>(item)) {
                    ShapeSnapshot ss = std::get<ShapeSnapshot>(item);
                    Shape* recreated = nullptr;

                    switch (ss.kind) {
                        case ShapeSnapshot::LINE:
                            if (ss.params.size() >= 2) {
                                recreated = new Line(ss.params[0], ss.params[1]);
                                // draw as line
                                scene->addLine(ss.params[0].x, ss.params[0].y,
                                               ss.params[1].x, ss.params[1].y,
                                               QPen(Qt::black, 2));
                            }
                            break;

                        case ShapeSnapshot::TRIANGLE:
                            if (ss.params.size() >= 3) {
                                recreated = new Triangle(ss.params[0], ss.params[1], ss.params[2]);
                                QPolygonF poly;
                                for (auto &q : ss.params) poly << QPointF(q.x, q.y);
                                scene->addPolygon(poly, QPen(Qt::black, 2));
                            }
                            break;

                        case ShapeSnapshot::RECTANGLE:
                            if (ss.params.size() >= 2) {
                                recreated = new Rectangles(ss.params[0], ss.params[1]);
                                QPolygonF poly;
                                // try to recreate rectangle polygon for drawing
                                auto rectPts = recreated->getCoordinates();
                                for (auto &q : rectPts) poly << QPointF(q.x, q.y);
                                scene->addPolygon(poly, QPen(Qt::black, 2));
                            }
                            break;

                        case ShapeSnapshot::CIRCLE:
                            if (ss.params.size() >= 2) {
                                // ss.params[0] == center, ss.params[1] == a point on circumference
                                recreated = new Circle(ss.params[0], ss.params[1]);
                                auto circlePts = recreated->getCoordinates();
                                QPolygonF poly;
                                for (auto &q : circlePts) poly << QPointF(q.x, q.y);
                                scene->addPolygon(poly, QPen(Qt::black, 2));
                            }
                            break;

                        case ShapeSnapshot::POLYGON:
                        case ShapeSnapshot::POLYLINE:
                        default:
                            // fallback: we have a raw list of points — draw them as a polygon/polyline
                            if (!ss.params.empty()) {
                                QPolygonF poly;
                                for (auto &q : ss.params) poly << QPointF(q.x, q.y);
                                scene->addPolygon(poly, QPen(Qt::black, 2));
                                // we don't have a concrete Shape subclass for polygon yet,
                                // so we push nullptr for now (user said they'll implement polygon later).
                                recreated = nullptr;
                            }
                            break;
                    }

                    shapes[id].push_back(recreated);
                }
            }
        }

        // Note: mShapeId lives in Sketcher. Caller should recompute mShapeId after undo/redo by
        // inspecting shapes map (e.g. max key + 1). UndoRedoManager can't access mShapeId directly.
    }

    void trimUndo() {
        while (undoStack.size() > MAX_LIMIT) undoStack.pop_front();
    }

    void trimRedo() {
        while (redoStack.size() > MAX_LIMIT) redoStack.pop_front();
    }
};
