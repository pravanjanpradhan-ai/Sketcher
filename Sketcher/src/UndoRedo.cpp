#include "stdafx.h"
#include "UndoRedo.h"

void UndoRedoManager::trimIfNeeded(std::vector<Action>& stack) {
    if (stack.size() > MAX_LIMIT) {
        stack.erase(stack.begin(), stack.begin() + (stack.size() - MAX_LIMIT));
    }
}

// Record a single add (point/shape)
void UndoRedoManager::recordAdd(QGraphicsItem* item, const SketchData& data) {
    trimIfNeeded(undoStack);
    undoStack.push_back(Action{ ActionType::AddItem, item, data, {} });
    redoStack.clear();
}

// Record a ClearAll snapshot.
// QUICK FIX: drop previous per-item actions because scene->clear() will delete those items.
void UndoRedoManager::recordClear(std::vector<Action> snapshot) {
    // Drop previous per-item history to avoid dangling pointers
    undoStack.clear();
    // store the ClearAll snapshot as the only undo action
    trimIfNeeded(undoStack);
    undoStack.push_back(Action{ ActionType::ClearAll, nullptr, {}, std::move(snapshot) });
    redoStack.clear();
}

void UndoRedoManager::undo(QGraphicsScene* scene) {
    if (undoStack.empty()) return;
    Action last = std::move(undoStack.back());
    undoStack.pop_back();

    if (last.type == ActionType::AddItem) {
        // In AddItem case the pointer should be valid
        if (last.item && last.item->scene()) scene->removeItem(last.item);
        redoStack.push_back(std::move(last));
    }
    else { // ClearAll: restore all snapshot items
        for (auto& a : last.snapshot) {
            if (a.item) scene->addItem(a.item);
        }
        redoStack.push_back(std::move(last));
    }
}

void UndoRedoManager::redo(QGraphicsScene* scene) {
    if (redoStack.empty()) return;
    Action last = std::move(redoStack.back());
    redoStack.pop_back();

    if (last.type == ActionType::AddItem) {
        if (last.item) scene->addItem(last.item);
        undoStack.push_back(std::move(last));
    }
    else { // ClearAll: remove all snapshot items again
        for (auto& a : last.snapshot) {
            if (a.item && a.item->scene()) scene->removeItem(a.item);
        }
        undoStack.push_back(std::move(last));
    }
}

bool UndoRedoManager::canUndo() const { return !undoStack.empty(); }
bool UndoRedoManager::canRedo() const { return !redoStack.empty(); }

// free all kept QGraphicsItem* / Shape* when destroying the manager
void UndoRedoManager::clearAndDeleteAll() {
    auto freeStack = [](std::vector<Action>& stack) {
        for (auto& a : stack) {
            if (a.type == ActionType::ClearAll) {
                for (auto& s : a.snapshot) {
                    if (s.item) delete s.item;
                    if (std::holds_alternative<Shape*>(s.data)) {
                        // only delete if snapshot used a heap-allocated Shape copy
                        delete std::get<Shape*>(s.data);
                    }
                }
            }
            else {
                if (a.item) delete a.item;
                if (std::holds_alternative<Shape*>(a.data)) {
                    delete std::get<Shape*>(a.data);
                }
            }
        }
        stack.clear();
        };
    freeStack(undoStack);
    freeStack(redoStack);
}

UndoRedoManager::~UndoRedoManager() {
    clearAndDeleteAll();
}