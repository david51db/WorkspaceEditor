//
// Created by David on 5/20/2026.
//

#include "EditorSession.h"
#include <sstream>
#include <vector>

#include "DeleteCommand.h"
#include "DocumentFactory.h"
#include "EditorException.h"
#include "InsertCommand.h"
#include "NewLineCommand.h"
#include "ToDoDocument.h"
#include "ToggleCheckboxCommand.h"
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
    checkDocument();
    if (currentDocument->getPath().empty()) throw EditorException("No path set.");
    currentDocument->save();
}

void EditorSession::undo() {
    checkDocument();
    history->undo();
}

void EditorSession::redo() {
    checkDocument();
    if (history->canRedo())history->redo();
    else throw EditorException("Cannot redo.");
}

void EditorSession::toggleCheckbox(int line) {
    checkDocument();
    auto* todo = dynamic_cast<ToDoDocument*>(currentDocument.get());
    if (!todo) throw EditorException("Not a ToDo Document");
    auto cmd = make_unique<ToggleCheckboxCommand>(*todo, line);
    cmd->execute();
    history->push(std::move(cmd));
}

int EditorSession::getWordCount() const {
    checkDocument();
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
    // auto line=currentDocument->getText()->getLine(cursor.first);
    // line.insert(cursor.second,text);
    // currentDocument->getText()->deleteLine(cursor.first);
    // currentDocument->getText()->insertLine(cursor.first, line);
    checkDocument();
    auto cmd=make_unique<InsertCommand>( *currentDocument->getText(), text, getCursor().first, getCursor().second );
    cmd->execute();
    history->push(std::move(cmd));

}

void EditorSession::deleteLine() {
    checkDocument();
    auto cmd=make_unique<DeleteCommand>(*currentDocument->getText(), "", getCursor().first, getCursor().second, DeleteMode::Line);
    cmd->execute();
    history->push(std::move(cmd));
}

std::pair<int, int> EditorSession::getCursor() const {
    return cursor;
}

void EditorSession::moveCursor(std::pair<int, int> newCursor) {
    this->cursor=newCursor;
}

void EditorSession::checkDocument() const {
    if (!currentDocument) throw EditorException("No document open");
}

void EditorSession::newLine() {
    checkDocument();
    auto cmd=make_unique<NewLineCommand>(*currentDocument->getText(), cursor.first);
    cmd->execute();
    history->push(std::move(cmd));
}
