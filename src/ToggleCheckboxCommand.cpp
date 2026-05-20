//
// Created by David on 5/20/2026.
//

#include "ToggleCheckboxCommand.h"

void ToggleCheckboxCommand::execute() {
    document.toggleCheckbox(line);
}

void ToggleCheckboxCommand::undo() {
    document.toggleCheckbox(line);
}