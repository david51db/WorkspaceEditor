//
// Created by David on 5/18/2026.
//

#include "ToDoDocument.h"
#include "Document.h"
using namespace std;

ToDoDocument::ToDoDocument() :Document(){}

ToDoDocument::ToDoDocument(std::unique_ptr<Buffer> text, std::vector<bool> checkBox,const std::string& name, const std::string& path, DocumentType type):Document(name, path, type),text(std::move(text)),checkBox(std::move(checkBox)) {}

void ToDoDocument::save() const {
    //to do
}

void ToDoDocument::load() {
    //to do
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
