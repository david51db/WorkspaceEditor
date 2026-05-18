//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_TEXTDOCUMENT_H
#define WORKSPACEEDITOR_TEXTDOCUMENT_H

#include <memory>
#include "Buffer.h"
#include "Document.h"

class TextDocument: public Document {
    std::unique_ptr<Buffer> text;

public:
    TextDocument();
    TextDocument(std::unique_ptr<Buffer> text, const std::string& name, const std::string& path, DocumentType type);
    TextDocument(const TextDocument& obj)=delete;
    TextDocument& operator=(const TextDocument& obj)=delete;
    TextDocument(TextDocument&& obj)=default;
    TextDocument& operator=(TextDocument&& obj)=default;
    ~TextDocument() override=default;

    void load() override;
    void save() const override;
    DocumentType getType() const override;

    const std::unique_ptr<Buffer>& getText() const;
};


#endif //WORKSPACEEDITOR_TEXTDOCUMENT_H