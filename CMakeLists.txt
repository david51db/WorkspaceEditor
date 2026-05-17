cmake_minimum_required(VERSION 4.1)
project(WorkspaceEditor)

set(CMAKE_CXX_STANDARD 20)

add_executable(WorkspaceEditor main.cpp
        include/Buffer.h
        include/Document.h
        include/TextDocument.h
        include/ToDoDocument.h
        include/FileManager.h
        include/EditorSession.h
        include/Command.h
        include/CommandHistory.h
        include/DocumentFactory.h
        include/EditorException.h
        include/Observer.h
        include/Repository.h)
