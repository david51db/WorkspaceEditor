//
// Created by David on 5/18/2026.
//

#include "TextDocument.h"
#include <memory>
#include <utility>
using namespace std;

TextDocument::TextDocument():Document(){};

TextDocument::TextDocument(std::unique_ptr<Buffer> text, const std::string &name, const std::string &path,
                           DocumentType type) : Document(name, path, type), text(std::move(text)) {}

void TextDocument::load() {
    //to do
}

void TextDocument::save() const {
    /// to do
}

DocumentType TextDocument::getType() const {
    return DocumentType::Text;
}

const std::unique_ptr<Buffer> &TextDocument::getText() const {
    return this->text;
}
