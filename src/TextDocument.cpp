//
// Created by David on 5/18/2026.
//

#include "TextDocument.h"

#include <filesystem>

#include "FileManager.h"
#include <memory>
#include <string>
#include <utility>
using namespace std;

TextDocument::TextDocument():Document(){};

TextDocument::TextDocument(const std::string& name, const std::string& path, DocumentType type)
    : Document(name, path, type, std::make_shared<Buffer>()) {}

void TextDocument::load() {
    text=FileManager::openFile(getPath());
}

void TextDocument::save() {
    if (path.empty()) {
        auto docs = std::filesystem::path(getenv("USERPROFILE")) / "Documents";
        path = (docs / (text->getLine(0).substr(0, 25) + ".txt")).string();
    }
    FileManager::saveFile(getPath(), *getText());
}

DocumentType TextDocument::getType() const {
    return DocumentType::Text;
}

