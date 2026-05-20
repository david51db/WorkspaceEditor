//
// Created by David on 5/20/2026.
//

#include "InsertCommand.h"
#include <string>

#include "EditorException.h"
using namespace std;

InsertCommand::InsertCommand(Buffer& buffer, const std::string& text, int line, int column) :Command(), buffer(buffer),text(text), line(line), column(column){};


void InsertCommand::execute() {
    auto currentLine = buffer.getLine(line);
    currentLine.insert(column, text);
    buffer.deleteLine(line);
    buffer.insertLine(line, currentLine);

}

void InsertCommand::undo() {
    auto currentLine=buffer.getLine(line);
    currentLine.erase(column,text.length());
    buffer.deleteLine(line);
    buffer.insertLine(line, currentLine);
}


// auto line=currentDocument->getText()->getLine(cursor.first);
// line.insert(cursor.second,text);
// currentDocument->getText()->deleteLine(cursor.first);
// currentDocument->getText()->insertLine(cursor.first, line);