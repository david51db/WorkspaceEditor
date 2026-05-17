//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_EDITOREXCEPTION_H
#define WORKSPACEEDITOR_EDITOREXCEPTION_H

#include <exception>
#include <string>

class EditorException: public std::exception {
    std::string message;
public:
    EditorException(const std::string& msg): message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //WORKSPACEEDITOR_EDITOREXCEPTION_H