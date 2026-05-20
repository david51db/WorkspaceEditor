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
        include/Repository.h
        src/Buffer.cpp
        src/Document.cpp
        src/TextDocument.cpp
        src/ToDoDocument.cpp
        src/FileManager.cpp
        src/DocumentFactory.cpp
        src/CommandHistory.cpp
        src/Observer.cpp
        src/EditorSession.cpp
        include/InsertCommand.h
        src/InsertCommand.cpp)

include_directories(include)
