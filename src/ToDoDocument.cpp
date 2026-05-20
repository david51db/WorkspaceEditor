//
// Created by David on 5/18/2026.
//

#include "ToDoDocument.h"
#include "Document.h"
#include "FileManager.h"
using namespace std;

ToDoDocument::ToDoDocument() :Document(){}

ToDoDocument::ToDoDocument(std::vector<bool> checkBox, const std::string& name, const std::string& path, DocumentType type)
    : Document(name, path, type, std::make_unique<Buffer>()), checkBox(std::move(checkBox)) {}

void ToDoDocument::save() const {
    FileManager::saveFile(getPath(), *getText());
}

void ToDoDocument::load() {
    text=FileManager::openFile(getPath());
}

const std::unique_ptr<Buffer> &ToDoDocument::getText() const {
    return this->text;
}

DocumentType ToDoDocument::getType() const {
    return DocumentType::ToDo;
}

const std::vector<bool> &ToDoDocument::getCheckBoxes() const {
    return this->checkBox;
}

void ToDoDocument::toggleCheckbox(int line) {
    checkBox[line] = !checkBox[line];
}
