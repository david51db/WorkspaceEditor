//
// Created by David on 5/18/2026.
//
#include "Document.h"
#include <memory>
using namespace std;

Document::Document(const std::string& name, const std::string& path, DocumentType type, std::shared_ptr<Buffer> text)
    : name(name), path(path), type(type),text(std::move(text)) {}

const std::string &Document::getName() const {
    return this->name;
}

const std::string &Document::getPath() const {
    return this->path;
}

void Document::setPath(const std::string &p) {
    this->path=p;
}
const std::shared_ptr<Buffer>& Document::getText() const {
    return text;
}
