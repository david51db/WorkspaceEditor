//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_COMMAND_H
#define WORKSPACEEDITOR_COMMAND_H

class Command {
public:
    virtual void execute()=0;
    virtual void undo()=0;
    virtual ~Command() = default;
};


#endif //WORKSPACEEDITOR_COMMAND_H