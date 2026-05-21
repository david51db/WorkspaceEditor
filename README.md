# WorkspaceEditor

A terminal-based text editor built in C++20 using FTXUI, supporting plain text and ToDo documents with undo/redo functionality in the user's device.

## Features

- Create and edit plain text files (`txt`)
- Create and edit ToDo files (`todo`) with toggable checkboxes (F1)
- Undo/Redo buttons
- Save as with custom *universal* path
- Autosave files to Documents folder based on the first line typed
- Recent files tracking
- Word count, line and column indicator

## Controls

| Key          | Action                                  |
|--------------|-----------------------------------------|
| `Esc`        | Toggle sidebar / editor focus           |
| `F1`         | Toggle checkbox (ToDo mode only)        |
| `Enter`      | New line                                |
| `Backspace`  | Delete character or merge lines         |
| `Arrow keys` | Move cursor                             |
| `Save`       | Save current file                       |
| `Undo`       | Undo last change                        |
| `Redo`       | Redo last change modified               |
| `Save As`    | Save with custom path (type in sidebar) |

## Design Patterns
| Pattern | Location |
|---------|----------|
| Singleton | `EditorSession`, `UI` |
| Factory | `DocumentFactory` |
| Command | `InsertCommand`, `DeleteCommand`, `NewLineCommand`, `ToggleCheckboxCommand`, `CommandHistory` |
| Observer | `Buffer` (Subject), `UIObserver` (Observer) |

## Class Structure
- `Buffer` — stores lines of text, notifies observers on change
- `Document` (abstract) -> `TextDocument`, `ToDoDocument`
- `EditorSession` — Singleton, manages current document, cursor, command history
- `DocumentFactory` — creates documents polymorphically by type
- `CommandHistory` — undo/redo stack using Command pattern
- `Repository<T>` — generic container used with `std::string` (recent files) and `int` (keystroke history)
- `Observer` / `Subject` — notification system between Buffer and UI
- `FileManager` — static file I/O
- `EditorException` — custom exception hierarchy

## C++ Features
- C++20 concepts (`Storable`, `Printable`)
- Smart pointers (`unique_ptr`, `shared_ptr`, `weak_ptr`)
- `std::filesystem` for cross-platform path management
- Template class `Repository<T>` with concept constraints
- Template functions `printAll<T>`, `contains<T>`
- Structured bindings, range-based loops, lambdas, `enum class`

## Compilation
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
Requires: CMake 3.14+, C++20 compiler (GCC 10+ or Clang 12+)
FTXUI is fetched automatically via CMake FetchContent.

## Repository
https://github.com/david51db/WorkspaceEditor

## Author
david51db