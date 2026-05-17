//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_REPOSITORY_H
#define WORKSPACEEDITOR_REPOSITORY_H
#include <vector>

template<typename T>
class Repository {
    std::vector<T> items;

public:
    void add(const T& item);
    void remove(const T& item);
    const std::vector<T>& getAll() const;
    const T findByIndex(int index) const;
    int size() const;


};



#endif //WORKSPACEEDITOR_REPOSITORY_H