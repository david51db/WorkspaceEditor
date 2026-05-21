//
// Created by David on 5/21/2026.
//

#ifndef WORKSPACEEDITOR_UTILS_H
#define WORKSPACEEDITOR_UTILS_H

#include <iostream>
#include <algorithm>
#include "Repository.h"

template<typename T>
concept Printable = requires(std::ostream& os, T t) {
    { os << t } -> std::same_as<std::ostream&>;
};

template<Printable T>
void printAll(const Repository<T>& repo) {
    for (const auto& item : repo.getAll())
        std::cout << item << "\n";
}

template<typename T>
bool contains(const Repository<T>& repo, const T& item) {
    const auto& all = repo.getAll();
    return std::find(all.begin(), all.end(), item) != all.end();
}


#endif //WORKSPACEEDITOR_UTILS_H