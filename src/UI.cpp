
#include "UI.h"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "EditorException.h"
#include "EditorSession.h"

using namespace std;
using namespace ftxui;

Component UI::setupButtons(EditorSession& session) {
    auto btnSave = Button("Save", [&] {
        try { session.save(); statusMessage = "Saved successfully"; }
        catch (const EditorException& e) { statusMessage = e.what(); }
    });
    auto btnUndo = Button("Undo", [&] {
        try { session.undo(); statusMessage = "Undo applied"; }
        catch (const EditorException& e) { statusMessage = e.what(); }
    });
    auto btnRedo = Button("Redo", [&] {
        try { session.redo(); statusMessage = "Redo applied"; }
        catch (const EditorException& e) { statusMessage = e.what(); }
    });
    return Container::Horizontal({btnSave, btnUndo, btnRedo});
}

Component UI::buildSidebar(EditorSession& session) {
    InputOption opt;
    opt.placeholder = "path...";
    auto input = Input(&openPath, opt);

    InputOption saveOpt;
    saveOpt.placeholder = "save path...";
    auto saveInput = Input(&savePath, saveOpt);

    auto btnOpen = Button("Open File", [&] {
        try {
            session.openFile(openPath);
            observer = make_shared<UIObserver>(statusMessage);
            session.getBuffer()->addObserver(observer);
            statusMessage = "Opened: " + openPath;
            openPath = "";
        } catch (const EditorException& e) { statusMessage = e.what(); }
    });

    auto btnSaveAs = Button("Save As", [&] {
        if (savePath.empty()) {
            statusMessage = "Enter a save path first";
            return;
        }
        try {
            session.setPath(savePath);
            session.save();
            statusMessage = "Saved: " + savePath;
        } catch (const EditorException &e) { statusMessage = e.what(); }
    });

    auto btnNewText = Button("New Text File", [&] {
        session.newFile(DocumentType::Text);
        observer = make_shared<UIObserver>(statusMessage);
        session.getBuffer()->addObserver(observer);
        statusMessage = "New text file";
    });

    auto btnNewToDo = Button("New ToDo File", [&] {
        session.newFile(DocumentType::ToDo);
        observer = make_shared<UIObserver>(statusMessage);
        session.getBuffer()->addObserver(observer);
        statusMessage = "New ToDo file";
    });

    auto stats = Renderer([&] {
        return vbox({
            separator(),
            text("Recent files:") | bold,

            [&] {
                Elements items;
                for (const auto& f : session.getRecentFiles().getAll())
                    items.push_back(text(f));
                return vbox(items);
            }(),
            separator(),
            text("Changes: " + std::to_string(session.getLineHistory().size())) | dim,
        });
    });


    Components children ={input, btnOpen, saveInput, btnSaveAs, btnNewText, btnNewToDo, stats};
    return Container::Vertical(children);
}

Component UI::buildRenderer(EditorSession& session, Component buttons, Component sidebar) {
    return Renderer(buttons, [&, buttons] {


        std::shared_ptr<Buffer> buffer;
        try { buffer = session.getBuffer(); }
        catch (...) {
            return vbox({
                buttons->Render(),
                text("No document open. Use the sidebar to create or open a file.") | center | flex
            }) | border | flex;
        }

        auto [cursorLine, cursorCol] = session.getCursor();
        int lineCount = buffer->getLineCount();


        if (lineCount == 0 || cursorLine >= lineCount)
            cursorLine = std::max(0, lineCount - 1);

        int lineLen = (lineCount > 0)
            ? static_cast<int>(buffer->getLine(cursorLine).size())
            : 0;
        int safeCursorCol = std::min(cursorCol, lineLen);


        bool isToDo = session.getCurrentDocumentType() == DocumentType::ToDo;
        const std::vector<bool>* boxes = session.getCheckboxes();

        Elements editorLines;
        for (int i = 0; i < lineCount; i++) {
            const std::string& line = buffer->getLine(i);


            std::string prefix = "";
            if (isToDo && boxes && i < (int)boxes->size())
                prefix = (*boxes)[i] ? "[x] " : "[ ] ";

            if (i == cursorLine) {
                std::string fullLine = prefix + line;
                int adjustedCol = safeCursorCol + (int)prefix.size();
                std::string before = fullLine.substr(0, adjustedCol);
                std::string cur    = (adjustedCol < (int)fullLine.size())
                                        ? fullLine.substr(adjustedCol, 1)
                                        : " ";
                std::string after  = (adjustedCol < (int)fullLine.size())
                                        ? fullLine.substr(adjustedCol + 1)
                                        : "";
                editorLines.push_back(hbox({
                    text(before),
                    text(cur) | inverted,
                    text(after) | flex
                }));
            } else {
                std::string display = prefix + line;
                editorLines.push_back(
                    display.empty() ? text(" ") : text(display)
                );
            }
        }


        return vbox({
            hbox({ buttons->Render(), text("   "), text(statusMessage) | bold }),
            vbox(editorLines) | flex,
            hbox({
                text(sidebarFocused ? " SIDEBAR " : " EDITOR ") | inverted,
                text("  "),
                text("Ln " + std::to_string(cursorLine + 1) +
                     "  Col " + std::to_string(safeCursorCol + 1) +
                     "  Words: " + std::to_string(session.getWordCount()))
            })
        }) | border | flex;
    });
}

Component UI::buildInputHandler(EditorSession& session, Component renderer, Component sidebar) {
    return CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) return false;


        if (event == Event::Escape) {
            sidebarFocused = !sidebarFocused;
            return true;
        }


        if (sidebarFocused) return false;


        try { session.getBuffer(); } catch (...) { return false; }

        auto [cursorLine, cursorCol] = session.getCursor();
        auto buffer = session.getBuffer();


        if (event == Event::F1) {
            if (session.getCurrentDocumentType() == DocumentType::ToDo) {
                try { session.toggleCheckbox(cursorLine); } catch (const EditorException &e) {
                    statusMessage = e.what();
                }
                return true;
            }

            session.insertText(" ");
            session.moveCursor({cursorLine, cursorCol + 1});
            return true;
        }



        if (event == Event::Return) {
            session.newLine();
            session.moveCursor({cursorLine + 1, 0});
            return true;
        }

        if (event == Event::Backspace) {
            if (cursorCol > 0) {
                session.moveCursor({cursorLine, cursorCol - 1});
                session.deleteChar();
            } else if (cursorLine > 0) {
                int prevLen = static_cast<int>(buffer->getLine(cursorLine - 1).size());
                session.deleteLine();
                session.moveCursor({cursorLine - 1, prevLen});
            }
            return true;
        }

        if (event == Event::ArrowUp) {
            if (cursorLine > 0) {
                int newCol = std::min(cursorCol,
                    static_cast<int>(buffer->getLine(cursorLine - 1).size()));
                session.moveCursor({cursorLine - 1, newCol});
            }
            return true;
        }

        if (event == Event::ArrowDown) {
            if (cursorLine + 1 < buffer->getLineCount()) {
                int newCol = std::min(cursorCol,
                    static_cast<int>(buffer->getLine(cursorLine + 1).size()));
                session.moveCursor({cursorLine + 1, newCol});
            }
            return true;
        }

        if (event == Event::ArrowRight) {
            int lineLen = static_cast<int>(buffer->getLine(cursorLine).size());
            if (cursorCol < lineLen) {
                session.moveCursor({cursorLine, cursorCol + 1});
            } else if (cursorLine + 1 < buffer->getLineCount()) {
                session.moveCursor({cursorLine + 1, 0});
            }
            return true;
        }

        if (event == Event::ArrowLeft) {
            if (cursorCol > 0) {
                session.moveCursor({cursorLine, cursorCol - 1});
            } else if (cursorLine > 0) {
                int prevLen = static_cast<int>(buffer->getLine(cursorLine - 1).size());
                session.moveCursor({cursorLine - 1, prevLen});
            }
            return true;
        }

        if (event.is_character()) {
            session.insertText(event.character());
            session.moveCursor({cursorLine, cursorCol + 1});
            return true;
        }

        return false;
    });
}

void UI::run() {
    auto& session = EditorSession::getInstance();
    session.newFile(DocumentType::Text);

    observer = make_shared<UIObserver>(statusMessage);
    session.getBuffer()->addObserver(observer);

    auto sidebar  = buildSidebar(session);
    auto buttons  = setupButtons(session);
    auto renderer = buildRenderer(session, buttons, sidebar);
    auto root     = ResizableSplitLeft(sidebar, renderer, &sidebarWidth);
    auto component = buildInputHandler(session, root, sidebar);

    auto screen = ScreenInteractive::Fullscreen();
    screen.TrackMouse(true);
    screen.Loop(component);
}
