//
// Created by David on 5/20/2026.
//

#ifndef WORKSPACEEDITOR_NEWLINECOMMAND_H
#define WORKSPACEEDITOR_NEWLINECOMMAND_H
#include "Buffer.h"
#include "Command.h"

class NewLineCommand : public Command{
    Buffer& buffer;
    int line;
public:
    NewLineCommand(Buffer& buffer, int line): buffer(buffer), line(line), Command(){};
    ~NewLineCommand() override = default;
    void execute() override;
    void undo() override;
};
#endif //WORKSPACEEDITOR_NEWLINECOMMAND_H