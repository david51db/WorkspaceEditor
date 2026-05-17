//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_COMMANDHISTORY_H
#define WORKSPACEEDITOR_COMMANDHISTORY_H

#include <memory>
#include <vector>
#include "Command.h"

class CommandHistory {
    std::vector<std::unique_ptr<Command>> history;

public:
    void push(std::unique_ptr<Command>);
    void undo();
    void redo();
    bool canUndo() const;
    bool canRedo() const;
};

#endif //WORKSPACEEDITOR_COMMANDHISTORY_H