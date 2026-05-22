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
        src/InsertCommand.cpp
        include/DeleteCommand.h
        src/DeleteCommand.cpp
        include/NewLineCommand.h
        src/NewLineCommand.cpp
        include/ToggleCheckboxCommand.h
        src/ToggleCheckboxCommand.cpp
        include/Utils.h
        include/UI.h
        src/UI.cpp
        include/UIObserver.h
        )

include_directories(include)

include(FetchContent)
FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
        GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

FetchContent_Declare(
   Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.4
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(WorkspaceEditor
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
)

enable_testing()

add_executable(WorkspaceEditorTests
        tests/testCommand.cpp
        tests/testBuffer.cpp
        tests/testRepository.cpp
        src/Buffer.cpp
        src/Observer.cpp
        src/InsertCommand.cpp
        src/DeleteCommand.cpp
        src/NewLineCommand.cpp
)

target_include_directories(WorkspaceEditorTests PRIVATE include)
target_link_libraries(WorkspaceEditorTests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(WorkspaceEditorTests)