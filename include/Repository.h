//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_REPOSITORY_H
#define WORKSPACEEDITOR_REPOSITORY_H
#include <algorithm>
#include <vector>

template<typename T>
concept Storable = !std::is_pointer_v<T>;

template<Storable T>
class Repository {
    std::vector<T> items;

public:
    void add(const T& item){items.push_back(item);}
    void remove(const T& item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) items.erase(it);
    }
    const std::vector<T>& getAll() const{return items;};
    const T findByIndex(int index) const{return items[index];};
    int size() const{return items.size();};


};




#endif //WORKSPACEEDITOR_REPOSITORY_H