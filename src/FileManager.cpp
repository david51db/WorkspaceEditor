//
// Created by David on 5/18/2026.
//

#include "FileManager.h"
#include "Buffer.h"
#include <fstream>
#include "EditorException.h"
using namespace std;


unique_ptr<Buffer> FileManager::openFile(const std::string &path) {
    ifstream file(path);
    if (!file.is_open())throw EditorException("Cannot open file: "+path);
    string line;
    auto buffer=make_unique<Buffer>();
    int pos=0;

    while (getline(file, line))buffer->insertLine(pos++,line) ;

    return buffer;
}


void FileManager::saveFile(const std::string &path, const Buffer &buffer) {
    ofstream file(path);

    for (const auto& line: buffer.getLines()) file<<line<<"\n";
}
