//
// Created by David on 5/19/2026.
//

#include "Observer.h"
#include <memory>

void Subject::notify() {
    auto it = observers.begin();
    while (it != observers.end()) {
        if (auto locked = it->lock()) {
            locked->onUpdate();
            ++it;
        } else {
            it = observers.erase(it);
        }
    }
}

void Subject::addObserver(std::weak_ptr<Observer> observer) {
    this->observers.push_back(observer);
}
