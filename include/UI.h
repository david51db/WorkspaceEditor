//
// Created by David on 5/21/2026.
//

#ifndef WORKSPACEEDITOR_UI_H
#define WORKSPACEEDITOR_UI_H
#include "UIObserver.h"
#include "ftxui/component/loop.hpp"
#include "EditorSession.h"

class UI {
    int sidebarWidth = 26;
    bool sidebarFocused = false;
    std::string statusMessage;
    std::shared_ptr<UIObserver> observer;
    std::string openPath;
    std::string savePath;

    UI()=default;
    ftxui::Component setupButtons( EditorSession& session);
    ftxui::Component buildRenderer( EditorSession& session, ftxui::Component buttons, ftxui::Component sidebar);
    ftxui::Component buildInputHandler( EditorSession& session, ftxui::Component renderer,ftxui::Component sidebar);
    ftxui::Component buildSidebar(EditorSession& session);

public:
    static UI& getInstance() {
        static UI instance;
        return instance;
    }
    UI(const UI&) = delete;
    UI& operator=(const UI&) = delete;

    void run();
};

#endif //WORKSPACEEDITOR_UI_H