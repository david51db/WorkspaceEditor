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
#include "Repository.h"
#include "Utils.h"
using namespace std;


EditorSession::EditorSession()
    : history(std::make_unique<CommandHistory>()) {}

void EditorSession::openFile(const std::string &path) {
    if (path.empty()) throw EditorException("Path cannot be empty");
    string extension=path.substr(path.find_last_of('.'));

    if (extension==".txt") currentDocument=DocumentFactory::create(DocumentType::Text);
    else if (extension==".todo") currentDocument=DocumentFactory::create(DocumentType::ToDo);
    else throw EditorException("Invalid path");

    currentDocument->setPath(path);
    currentDocument->load();
    cursor={0,0};

    history=make_unique<CommandHistory>();
    if (!contains(recentFiles, path))
        recentFiles.add(path);
}

void EditorSession::newFile(DocumentType type) {
    currentDocument = DocumentFactory::create(type);
    currentDocument->getText()->insertLine(0, "");
    cursor = {0, 0};
    history = make_unique<CommandHistory>();


    if (type == DocumentType::ToDo) {
        auto* todo = dynamic_cast<ToDoDocument*>(currentDocument.get());
        todo->insertCheckbox(0);
    }
}

void EditorSession::save() {
    checkDocument();
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
    checkDocument();
    auto cmd=make_unique<InsertCommand>( *currentDocument->getText(), text, getCursor().first, getCursor().second );
    cmd->execute();
    history->push(std::move(cmd));
    lineHistory.add(cursor.first);

}

void EditorSession::deleteLine() {
    checkDocument();
    auto cmd = make_unique<DeleteCommand>(*currentDocument->getText(), "",
        getCursor().first, getCursor().second, DeleteMode::Line);
    cmd->execute();
    history->push(std::move(cmd));

    if (currentDocument->getType() == DocumentType::ToDo) {
        auto* todo = dynamic_cast<ToDoDocument*>(currentDocument.get());
        todo->removeCheckbox(getCursor().first);
    }
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
    auto cmd = make_unique<NewLineCommand>(*currentDocument->getText(), cursor.first);
    cmd->execute();
    history->push(std::move(cmd));

    if (currentDocument->getType() == DocumentType::ToDo) {
        auto* todo = dynamic_cast<ToDoDocument*>(currentDocument.get());
        todo->insertCheckbox(cursor.first + 1);
    }
}

const Repository<std::string> &EditorSession::getRecentFiles() const {
    return recentFiles;
}

std::shared_ptr<Buffer> EditorSession::getBuffer() const {
    checkDocument();
    return currentDocument->getText();
}

void EditorSession::deleteChar() {
    checkDocument();
    auto cmd=make_unique<DeleteCommand>(*currentDocument->getText(),"", getCursor().first, getCursor().second, DeleteMode::Char);
    cmd->execute();
    history->push(std::move(cmd));
}

DocumentType EditorSession::getCurrentDocumentType() const {
    checkDocument();
    return currentDocument->getType();
}

const std::vector<bool>* EditorSession::getCheckboxes() const {
    checkDocument();
    auto* todo = dynamic_cast<ToDoDocument*>(currentDocument.get());
    return todo ? &todo->getCheckBoxes() : nullptr;
}

void EditorSession::setPath(const std::string &path) {
    checkDocument();
    currentDocument->setPath(path);
}

const Repository<int>& EditorSession::getLineHistory() const {
    return lineHistory;
}