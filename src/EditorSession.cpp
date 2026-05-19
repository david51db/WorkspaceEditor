//
// Created by David on 5/20/2026.
//

#include "EditorSession.h"
#include <cstring>

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

}
