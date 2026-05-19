//
// Created by David on 5/18/2026.
//

#include "TextDocument.h"
#include "FileManager.h"
#include <memory>
#include <utility>
using namespace std;

TextDocument::TextDocument():Document(){};

TextDocument::TextDocument(const std::string& name, const std::string& path, DocumentType type)
    : Document(name, path, type, std::make_unique<Buffer>()) {}

void TextDocument::load() {
    text=FileManager::openFile(getPath());
}

void TextDocument::save() const {
    FileManager::saveFile(getPath(), *getText());
}

DocumentType TextDocument::getType() const {
    return DocumentType::Text;
}

const std::unique_ptr<Buffer> &TextDocument::getText() const {
    return this->text;
}
