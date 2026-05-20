//
// Created by David on 5/20/2026.
//

#ifndef WORKSPACEEDITOR_INSERTCOMMAND_H
#define WORKSPACEEDITOR_INSERTCOMMAND_H
#include <string>

#include "Buffer.h"
#include "Command.h"

class InsertCommand: public Command {
    Buffer& buffer;
    std::string text;
    int line;
    int column;

public:
    InsertCommand(Buffer& buffer, const std::string& text, int line, int column);
    ~InsertCommand() override=default;

    void execute() override;
    void undo() override;
};


#endif //WORKSPACEEDITOR_INSERTCOMMAND_H