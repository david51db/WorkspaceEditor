//
// Created by David on 5/18/2026.
//

#include "CommandHistory.h"
#include <vector>

#include "EditorException.h"
using namespace std;

void CommandHistory::push(std::unique_ptr<Command> command) {
    redoStack.clear();
    history.push_back(std::move(command));
}

bool CommandHistory::canUndo() const {
    if (!history.empty()) return true;
    return false;
}

void CommandHistory::undo() {
    if (!canUndo()) throw EditorException("Cannot undo");
    history.back()->undo();
    redoStack.push_back(std::move(history.back()));
    history.pop_back();
}

bool CommandHistory::canRedo() const {
    return !redoStack.empty();
}

void CommandHistory::redo() {
    if (!canRedo()) throw EditorException("Cannot redo");
    redoStack.back()->execute();
    history.push_back(std::move(redoStack.back()));
    redoStack.pop_back();
}
