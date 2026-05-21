//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_EDITORSESSION_H
#define WORKSPACEEDITOR_EDITORSESSION_H
#include "Document.h"
#include "CommandHistory.h"
#include <memory>
#include "Repository.h"

class EditorSession {
    std::unique_ptr<Document> currentDocument;
    std::pair<int, int> cursor;
    std::unique_ptr<CommandHistory> history;
    Repository<std::string> recentFiles;
    EditorSession();
    void checkDocument() const;
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
    void redo();
    void toggleCheckbox(int line);
    void moveCursor(std::pair<int,int> newCursor);
    int getWordCount() const;
    std::pair<int,int> getCursor() const;
    void newLine();
    const Repository<std::string>& getRecentFiles() const;
};

#endif //WORKSPACEEDITOR_EDITORSESSION_H