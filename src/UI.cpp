//
// Created by David on 5/21/2026.
//

#include "UI.h"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include "EditorException.h"
#include "EditorSession.h"
#include "UIObserver.h"
using namespace std;
using namespace ftxui;

void UI::run() {

    string statusMessage;
    auto& session = EditorSession::getInstance();
    session.newFile(DocumentType::Text);
    auto observer=make_shared<UIObserver>(statusMessage);
    session.getBuffer()->addObserver(observer);

    auto btnSave=Button("Save", [&] {
        try {
            session.save();
            statusMessage="Saved succesfully";
        }catch (const EditorException& e) {
            statusMessage=e.what();
        }
    });
    auto btnUndo=Button("Undo", [&] {
        try {
            session.undo();
            statusMessage="Undo applied";
        }catch (const EditorException& e) {
            statusMessage=e.what();
        }
    });
    auto btnRedo=Button("Redo", [&] {
        try {
            session.redo();
            statusMessage="Redo applied";
        }catch (const EditorException& e) {
            statusMessage=e.what();
        }
    });

    auto buttons = Container::Horizontal({btnSave, btnUndo, btnRedo});

    auto renderer=Renderer(buttons,[&] {
        Elements editorLines;
        int currentLineIdx = 0;
        auto cursorLine=session.getCursor().first;
        auto cursorCol=session.getCursor().second;

        for (const auto& line : session.getBuffer()->getLines()) {
            if (currentLineIdx == cursorLine) {
                std::string beforeCursor = line.substr(0, cursorCol);
                std::string cursorChar = (cursorCol < line.size()) ? line.substr(cursorCol, 1) : " ";
                std::string afterCursor = (cursorCol < line.size()) ? line.substr(cursorCol + 1) : "";
                editorLines.push_back(hbox({
                    text(beforeCursor),
                    text(cursorChar) | inverted,
                    text(afterCursor)
                }));
            } else {
                if (line.empty()) {
                    editorLines.push_back(paragraph(" "));
                } else {
                    editorLines.push_back(paragraph(line));
                }
            }
            currentLineIdx++;
        }
        return hbox({
            vbox({text("Recent Files")|bold}) | border| size(WIDTH, EQUAL, 20),
            vbox({
                hbox({buttons->Render(), text("   "), text(statusMessage)|bold}),
                vbox(editorLines) |flex,
                hbox({text("Words: "+to_string(session.getWordCount()))})}) | border|flex
            });
    });


    auto component=CatchEvent(renderer, [&](Event event) {
        if (event==Event::Return) {
            session.newLine();
            auto [line, col]=session.getCursor();
            session.moveCursor({line+1,0});
            return true;
        }
        if (event == Event::Backspace) {
         auto [line, col] = session.getCursor();
            if (col > 0) {
                session.moveCursor({line, col - 1});
                session.deleteChar();
            }
            else if (line>0) {
                int prevLineLen = session.getBuffer()->getLine(line - 1).size();
                session.deleteLine();
                session.moveCursor({line - 1, prevLineLen});
            }
        return true;
        }
        if (event == Event::ArrowDown) {
            auto [line, col] = session.getCursor();
            if (line + 1 < session.getBuffer()->getLineCount()) {
                line++;
                size_t currentLineLength = session.getBuffer()->getLine(line).size();
                if (col > currentLineLength) {
                    col = currentLineLength;
                }
                session.moveCursor({line, col});
            } else {
                session.newLine();
                session.moveCursor({line + 1, 0});
            }
            return true;
        }
        if (event==Event::ArrowUp) {
            auto [line, col]=session.getCursor();
            if (line>0)line--;
            size_t currentLineLength = session.getBuffer()->getLine(line).size();
            if (col > currentLineLength) {
                col = currentLineLength;
            }
            session.moveCursor({line,col});
            return true;
        }
        if (event == Event::ArrowRight) {
            auto [line, col] = session.getCursor();
            size_t currentLineLength = session.getBuffer()->getLine(line).size();

            if (col < currentLineLength) {
                col++;
                session.moveCursor({line, col});
            } else if (line + 1 < session.getBuffer()->getLineCount()) {
                session.moveCursor({line + 1, 0});
            } else {
                session.newLine();
                session.moveCursor({line + 1, 0});
            }
            return true;
        }
        if (event == Event::ArrowLeft) {
            auto [line, col] = session.getCursor();
            if (col > 0) {
                col--;
                session.moveCursor({line, col});
            } else if (line > 0) {
                line--;
                col = session.getBuffer()->getLine(line).size();
                session.moveCursor({line, col});
            }
            return true;
        }



        if (event.is_character()) {
            session.insertText(event.character());
            session.moveCursor({session.getCursor().first, session.getCursor().second + 1});
            return true;
        }
        return false;
    });


    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(component);

}