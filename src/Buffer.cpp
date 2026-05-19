//
// Created by David on 5/18/2026.
//

#include "Buffer.h"
#include "EditorException.h"
using namespace std;

Buffer::Buffer() =default;

Buffer::Buffer(std::vector<std::string> &text): text(text){}

void Buffer::insertLine(int pos, const std::string &line) {
    if (pos < 0 || pos > text.size()) {
        throw EditorException("Invalid line position");
    }
    text.insert(pos+text.begin(), line);
    notify();
}

void Buffer::deleteLine(int pos) {
    if (pos < 0 || pos >= text.size()) {
        throw EditorException("Invalid line position");
    }
    text.erase(pos+text.begin());
    notify();
}

const std::string &Buffer::getLine(int pos) const {
    if (pos < 0 || pos >= text.size()) {
        throw EditorException("Invalid line position");
    }
    return text[pos];
}

void Buffer::clear() {
    text.clear();
}

int Buffer::getLineCount() const {
    return text.size();
}

const std::vector<std::string> &Buffer::getLines() const {
    return text;
}
