//
// Created by David on 5/20/2026.
//

#ifndef WORKSPACEEDITOR_DELETECOMMAND_H
#define WORKSPACEEDITOR_DELETECOMMAND_H
#include "Buffer.h"
#include "Command.h"

enum class DeleteMode {
    Char, Line
};

class DeleteCommand: public Command {
    Buffer& buffer;
    std::string text;
    DeleteMode mode;
    int line;
    int column;

public:
    DeleteCommand(Buffer& buffer, const std::string& text, int line, int column, DeleteMode mode);
    ~DeleteCommand() override=default;

    void execute() override;
    void undo() override;
};


#endif //WORKSPACEEDITOR_DELETECOMMAND_H