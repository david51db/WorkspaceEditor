//
// Created by David on 5/18/2026.
//
#include "Document.h"
using namespace std;

Document::Document(const std::string& name, const std::string& path, DocumentType type)
    : name(name), path(path), type(type) {}

const std::string &Document::getName() const {
    return this->name;
}

const std::string &Document::getPath() const {
    return this->path;
}

DocumentType Document::getType() const {
    return this->type;
}

