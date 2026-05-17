

#ifndef WORKSPACEEDITOR_DOCUMENT_H
#define WORKSPACEEDITOR_DOCUMENT_H

#include <string>

enum class DocumentType {
    Text,
    ToDo
};

class Document {
protected:
    std::string name;
    std::string path;
    DocumentType type;

public:
    Document(const std::string& name, const std::string& path, DocumentType type);
    Document(const Document& obj)=default;
    Document& operator=(const Document& obj)=default;
    Document(Document&& obj)=default;
    Document& operator=(Document&& obj)=default;
    virtual ~Document()=default;

    virtual void load()=0;
    virtual void save() const=0;
    virtual DocumentType getType() const=0;

    const std::string& getName() const;
    const std::string& getPath() const;

};

#endif //WORKSPACEEDITOR_DOCUMENT_H