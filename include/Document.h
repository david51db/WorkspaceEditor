

#ifndef WORKSPACEEDITOR_DOCUMENT_H
#define WORKSPACEEDITOR_DOCUMENT_H

#include <string>

#include "Buffer.h"

enum class DocumentType {
    Text,
    ToDo
};

class Document {
protected:
    std::shared_ptr<Buffer> text;
    std::string name;
    std::string path;
    DocumentType type;

public:
    Document() : text(std::make_shared<Buffer>()), type(DocumentType::Text) {}
    Document(const std::string& name, const std::string& path, DocumentType type, std::shared_ptr<Buffer> text);
    Document(const Document& obj)=default;
    Document& operator=(const Document& obj)=default;
    Document(Document&& obj)=default;
    Document& operator=(Document&& obj)=default;
    virtual ~Document()=default;

    virtual void load()=0;
    virtual void save() const=0;
    virtual DocumentType getType() const = 0;
    virtual const std::shared_ptr<Buffer>& getText() const;


    const std::string& getName() const;
    const std::string& getPath() const;
    void setPath(const std::string& p);

};

#endif //WORKSPACEEDITOR_DOCUMENT_H