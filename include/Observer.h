//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_OBSERVER_H
#define WORKSPACEEDITOR_OBSERVER_H
#include <memory>
#include <vector>

class Observer {
public:
    virtual void onUpdate()=0;
    virtual ~Observer()=default;
};

class Subject {
    std::vector<std::weak_ptr<Observer>> observers;
public:
    void addObserver(std::weak_ptr<Observer> observer);
    void notify();
};


#endif //WORKSPACEEDITOR_OBSERVER_H