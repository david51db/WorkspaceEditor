//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_TODODOCUMENT_H
#define WORKSPACEEDITOR_TODODOCUMENT_H

#include <memory>
#include <vector>
#include "Buffer.h"
#include "Document.h"

class ToDoDocument: public Document {
    std::vector<bool> checkBox;

public:
    ToDoDocument();
    ToDoDocument(std::vector<bool> checkBox,const std::string& name, const std::string& path, DocumentType type);
    ToDoDocument(const ToDoDocument& obj)=delete;
    ToDoDocument& operator=(const ToDoDocument& obj)=delete;
    ToDoDocument(ToDoDocument&& obj) =default;
    ToDoDocument& operator=(ToDoDocument&& obj) =default;
    ~ToDoDocument() override=default;

    void load() override;
    void save() override ;
    DocumentType getType() const override;


    const std::vector<bool>& getCheckBoxes() const;
    void toggleCheckbox(int line);

    void insertCheckbox(int pos);
    void removeCheckbox(int pos);
};


#endif //WORKSPACEEDITOR_TODODOCUMENT_H