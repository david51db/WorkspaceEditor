//
// Created by David on 5/17/2026.
//

#ifndef WORKSPACEEDITOR_FILEMANAGER_H
#define WORKSPACEEDITOR_FILEMANAGER_H

#include <memory>
#include <string>
#include "Buffer.h"

class FileManager {
public:
    static std::unique_ptr<Buffer> openFile(const std::string& path);
    static void saveFile(const std::string& path, const Buffer& buffer);
};


#endif //WORKSPACEEDITOR_FILEMANAGER_H