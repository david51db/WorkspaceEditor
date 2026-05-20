//
// Created by David on 5/20/2026.
//

#ifndef WORKSPACEEDITOR_TOGGLECHECKBOXCOMMAND_H
#define WORKSPACEEDITOR_TOGGLECHECKBOXCOMMAND_H
#include "Command.h"
#include "ToDoDocument.h"

class ToggleCheckboxCommand :public Command{
    ToDoDocument& document;
    int line;

public:
    ToggleCheckboxCommand(ToDoDocument& document, int line): document(document), line(line), Command(){};
    ~ToggleCheckboxCommand() override=default;
    void execute() override;
    void undo() override;
};


#endif //WORKSPACEEDITOR_TOGGLECHECKBOXCOMMAND_H