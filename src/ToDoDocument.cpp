//
// Created by David on 5/18/2026.
//

#include "ToDoDocument.h"

#include <filesystem>

#include "Document.h"
#include "EditorException.h"
#include "FileManager.h"
using namespace std;

ToDoDocument::ToDoDocument() :Document(){}

ToDoDocument::ToDoDocument(std::vector<bool> checkBox, const std::string& name, const std::string& path, DocumentType type)
    : Document(name, path, type, std::make_shared<Buffer>()), checkBox(std::move(checkBox)) {}

void ToDoDocument::save()  {
    const auto& lines=getText()->getLines();
    vector<string> modifiedLines;
    for (int i=0;i<lines.size();i++)
        modifiedLines.push_back((checkBox[i] ? "[x] " : "[ ] ") + lines[i]);
    Buffer newText(modifiedLines);
    if (path.empty()) {
        auto docs = std::filesystem::path(getenv("USERPROFILE")) / "Documents";
        path = (docs / (text->getLine(0).substr(0, 25) + ".todo")).string();
    }
    FileManager::saveFile(getPath(), newText);
}

void ToDoDocument::load() {
    checkBox.clear();
    text->clear();
    auto rawBuffer = FileManager::openFile(getPath());
    const auto& lines = rawBuffer->getLines();
    for (int i = 0; i < lines.size(); i++) {
        checkBox.push_back(lines[i][1] == 'x');
        text->insertLine(i, lines[i].substr(4));
    }
}

DocumentType ToDoDocument::getType() const {
    return DocumentType::ToDo;
}

const std::vector<bool> &ToDoDocument::getCheckBoxes() const {
    return this->checkBox;
}

void ToDoDocument::toggleCheckbox(int line) {
    if (line < 0 || line >= static_cast<int>(checkBox.size()))
        throw EditorException("Invalid checkbox line");
    checkBox[line] = !checkBox[line];
}

void ToDoDocument::insertCheckbox(int pos) {
    if (pos >= 0 && pos <= (int)checkBox.size())
        checkBox.insert(checkBox.begin() + pos, false);
}
void ToDoDocument::removeCheckbox(int pos) {
    if (pos >= 0 && pos < (int)checkBox.size())
        checkBox.erase(checkBox.begin() + pos);
}
