
#ifndef WORKSPACEEDITOR_BUFFER_H
#define WORKSPACEEDITOR_BUFFER_H
#include <string>
#include <vector>

class Buffer {
    std::vector<std::string> text;

public:
    Buffer();
    Buffer(std::vector<std::string>& text);
    Buffer(const Buffer& obj)=default;
    Buffer& operator=(const Buffer& obj)=default;
    Buffer(Buffer&&)=default;
    Buffer& operator=(Buffer&&)=default;
    ~Buffer()=default;

    void insertLine(int pos, const std::string& line);
    void deleteLine(int pos);
    const std::string& getLine(int pos) const;
    int getLineCount() const;
    const std::vector<std::string>& getLines() const;
    void clear();
};



#endif //WORKSPACEEDITOR_BUFFER_H