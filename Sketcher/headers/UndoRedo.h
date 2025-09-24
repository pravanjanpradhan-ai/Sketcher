#pragma once
#include <unordered_map>
#include <vector>
#include <variant>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include "Point.h"
#include "Shape.h"

using SketchData = std::variant<Shape*, Point>;
using Snapshot = std::unordered_map<int, std::vector<SketchData>>;

class UndoRedoManager {
private:
    std::vector<Snapshot> undoStack;
    std::vector<Snapshot> redoStack;
    const int MAX_LIMIT = 10;

public:
    // Save current state into undo stack
    void recordData(const Snapshot& currentShapes) {
        if (undoStack.size() == MAX_LIMIT) {
            undoStack.erase(undoStack.begin());
        }
        undoStack.push_back(currentShapes);
        redoStack.clear();
    }

    // Undo operation
    void undo(QGraphicsScene* scene, Snapshot& shapes) {
        if (undoStack.empty()) return;

        redoStack.push_back(shapes);
        shapes = undoStack.back();
        undoStack.pop_back();

        deldraw(scene, shapes);
    }

    // Redo operation
    void redo(QGraphicsScene* scene, Snapshot& shapes) {
        if (redoStack.empty()) return;

        undoStack.push_back(shapes);
        shapes = redoStack.back();
        redoStack.pop_back();

        redraw(scene, shapes);
    }

    // Helper: check if undo available
    bool canUndo() const { return !undoStack.empty(); }

    // Helper: check if redo available
    bool canRedo() const { return !redoStack.empty(); }

private:
    void deldraw(QGraphicsScene* scene, Snapshot& shapes) {
        scene->clear();
        if (!shapes.empty()) {
            shapes.erase(shapes.begin());
        }
    }
    void redraw(QGraphicsScene* scene, const Snapshot& shapes) {
        for (const auto& [id, vec] : shapes) {
            for (const auto& data : vec) {
                if (std::holds_alternative<Point>(data)) {
                    Point p = std::get<Point>(data);
                    QBrush brush(QColor("#3DB9E7"));
                    scene->addEllipse(p.x - 2, p.y - 2, 4, 4, QPen(Qt::transparent), brush);
                }
                else if (std::holds_alternative<Shape*>(data)) {
                    Shape* s = std::get<Shape*>(data);
                    if (s) {
                        std::vector<Point> p = s->getCoordinates();
                        if (p.size() > 36)
                        {
                            p.erase(p.begin());
                            p.erase(p.begin());
                        }
                        QPolygonF shape;
                        for (int i = 0; i < p.size(); i++) {
                            shape << QPointF(p[i].x, p[i].y);
                        }
                        scene->addPolygon(shape, QPen(Qt::black, 2));
                    }
                }
            }
        }
    }
};
