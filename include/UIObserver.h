//
// Created by David on 5/21/2026.
//

#ifndef WORKSPACEEDITOR_UIOBSERVER_H
#define WORKSPACEEDITOR_UIOBSERVER_H
#include "Observer.h"

class UIObserver:public Observer {
    std::string& statusMessage;
public:
    UIObserver(std::string& statusMessage): statusMessage(statusMessage), Observer(){};
    ~UIObserver() override=default;

    void onUpdate() override {
        statusMessage="Modified";
    };
};



#endif //WORKSPACEEDITOR_UIOBSERVER_H