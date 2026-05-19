//
// Created by David on 5/19/2026.
//

#include "Observer.h"
#include <memory>

void Subject::notify() {
    for (auto& obs : observers)
        if (auto locked=obs.lock())
            locked->onUpdate();
}

void Subject::addObserver(std::weak_ptr<Observer> observer) {
    this->observers.push_back(observer);
}
