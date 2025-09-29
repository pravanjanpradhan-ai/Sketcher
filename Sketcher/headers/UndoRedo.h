#pragma once
#include <vector>
#include <variant>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include "Point.h"
#include "Shape.h"

using SketchData = std::variant<Shape*, Point>;

enum class ActionType { AddItem, ClearAll };

struct Action {
    ActionType type;
    QGraphicsItem* item = nullptr;     // used for AddItem
    SketchData data;                   // used for AddItem (keeps logical data)
    std::vector<Action> snapshot;      // used for ClearAll (stores items + data)
};

class UndoRedoManager {
private:
    std::vector<Action> undoStack;
    std::vector<Action> redoStack;
    const size_t MAX_LIMIT = 10;

    void trimIfNeeded(std::vector<Action>& stack);

public:
    // Record a single add (point/shape)
    void recordAdd(QGraphicsItem* item, const SketchData& data);

    void recordClear(std::vector<Action> snapshot);

    void undo(QGraphicsScene* scene);
    void redo(QGraphicsScene* scene);

    bool canUndo() const;
    bool canRedo() const;

    // free all kept QGraphicsItem* / Shape* when destroying the manager
    void clearAndDeleteAll();

    ~UndoRedoManager();
};
