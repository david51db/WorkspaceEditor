//
// Created by David on 5/20/2026.
//

#include "EditorSession.h"
#include <sstream>
#include <vector>
#include "DocumentFactory.h"
#include "EditorException.h"
using namespace std;


EditorSession::EditorSession()
    : history(std::make_unique<CommandHistory>()) {}

void EditorSession::openFile(const std::string &path) {
    string extension=path.substr(path.find_last_of('.'));

    if (extension==".txt") currentDocument=DocumentFactory::create(DocumentType::Text);
    else if (extension==".todo") currentDocument=DocumentFactory::create(DocumentType::ToDo);
    else throw EditorException("Invalid path");

    currentDocument->setPath(path);
    currentDocument->load();
}

void EditorSession::newFile(DocumentType type) {
    currentDocument=DocumentFactory::create(type);
}

void EditorSession::save() {
    if (currentDocument->getPath().empty()) throw EditorException("No path set.");
    currentDocument->save();
}

void EditorSession::undo() {
    history->undo();
}

int EditorSession::getWordCount() const {
    const auto& currentText=currentDocument->getText()->getLines();
    int wordCount=0;
    for (const auto& line:currentText) {
        istringstream stream(line);
        string word;
        while(stream>>word)wordCount++;
    }
    return wordCount;
}

void EditorSession::insertText(const std::string &text) {
    auto line=currentDocument->getText()->getLine(cursor.first);
    line.insert(cursor.second,text);
    currentDocument->getText()->deleteLine(cursor.first);
    currentDocument->getText()->insertLine(cursor.first, line);
}

void EditorSession::deleteLine() {
    currentDocument->getText()->deleteLine(cursor.first);
}

std::pair<int, int> EditorSession::getCursor() const {
    return cursor;
}
