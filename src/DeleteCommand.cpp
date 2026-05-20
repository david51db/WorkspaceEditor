//
// Created by David on 5/20/2026.
//

#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(Buffer &buffer, const std::string &text, int line, int column,
                             DeleteMode mode) : Command(), buffer(buffer), text(text), line(line), column(column),
                                                mode(mode) {
};

void DeleteCommand::execute() {
    if (mode==DeleteMode::Char) {
        auto currentLine = buffer.getLine(line);
        text = buffer.getLine(line);
        currentLine.erase(column);
        buffer.deleteLine(line);
        buffer.insertLine(line, currentLine);
    }
    else if (mode==DeleteMode::Line) {
        text = buffer.getLine(line);
        buffer.deleteLine(line);
    }
}

void DeleteCommand::undo() {
    if (mode == DeleteMode::Char) {
        auto currentLine = buffer.getLine(line);
        currentLine.insert(column, text);
        buffer.deleteLine(line);
        buffer.insertLine(line, currentLine);
    } else if (mode == DeleteMode::Line) {
        buffer.insertLine(line, text);
    }
}