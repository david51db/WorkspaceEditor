//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_DOCUMENTFACTORY_H
#define WORKSPACEEDITOR_DOCUMENTFACTORY_H
#include <memory>
#include "Document.h"

class DocumentFactory {
public:
    static std::unique_ptr<Document> create(DocumentType type);
};


#endif //WORKSPACEEDITOR_DOCUMENTFACTORY_H