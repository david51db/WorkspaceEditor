//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_EDITORSESSION_H
#define WORKSPACEEDITOR_EDITORSESSION_H
#include "Document.h"
#include "CommandHistory.h"
#include <memory>

class EditorSession {
    std::unique_ptr<Document> currentDocument;
    std::pair<int, int> cursor;
    std::unique_ptr<CommandHistory> history;
    EditorSession();


public:
    static EditorSession& getInstance() {
        static EditorSession instance;
        return instance;
    }
    EditorSession(const EditorSession&) = delete;
    EditorSession& operator=(const EditorSession&) = delete;

    void openFile(const std::string& path);
    void newFile(DocumentType type);
    void save();
    void insertText(const std::string& text);
    void deleteLine();
    void undo();
    int getWordCount() const;
    std::pair<int,int> getCursor() const;
};

#endif //WORKSPACEEDITOR_EDITORSESSION_H