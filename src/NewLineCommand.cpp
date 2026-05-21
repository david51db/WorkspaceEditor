//
// Created by David on 5/20/2026.
//


#include "NewLineCommand.h"


void NewLineCommand::execute() {
    buffer.insertLine(line + 1, "");
}

void NewLineCommand::undo() {
    buffer.deleteLine(line+1);
}
