//
// Created by David on 5/21/2026.
//

#ifndef WORKSPACEEDITOR_UI_H
#define WORKSPACEEDITOR_UI_H
#include "UIObserver.h"
#include "ftxui/component/loop.hpp"

class UI {
    std::string statusMessage;
    std::shared_ptr<UIObserver> observer;

    UI()=default;
    ftxui::Component setupButtons(class EditorSession& session);
    ftxui::Component buildRenderer(class EditorSession& session, ftxui::Component buttons);
    ftxui::Component buildInputHandler(class EditorSession& session, ftxui::Component renderer);
public:
    static UI& getInstace() {
        static UI instance;
        return instance;
    }
    UI(const UI&) = delete;
    UI& operator=(const UI&) = delete;

    void run();
};

#endif //WORKSPACEEDITOR_UI_H