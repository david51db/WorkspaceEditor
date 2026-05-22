//
// Created by David on 5/22/2026.
//
#include <catch2/catch_test_macros.hpp>
#include "InsertCommand.h"
#include "DeleteCommand.h"
#include "NewLineCommand.h"
#include "EditorException.h"
#include <memory>

#include "EditorSession.h"
using namespace std;



TEST_CASE("Insert command with execute and undo", "[InsertCommand]") {
    Buffer buf;
    buf.insertLine(0, "Hello");
    buf.insertLine(1, "World");
    auto cmd1= make_unique<InsertCommand>(buf,"something",0,0);
    auto cmd2= make_unique<InsertCommand>(buf, "something else", 1,0);

    cmd1->execute();
    REQUIRE(buf.getLine(0)=="somethingHello");
    cmd1->undo();
    REQUIRE(buf.getLineCount()==2);
    cmd1->execute();
    cmd2->execute();
    REQUIRE(buf.getLine(1)=="something elseWorld");
    REQUIRE(buf.getLineCount()==2);
    cmd2->undo();
    REQUIRE(buf.getLine(0)=="somethingHello");
    REQUIRE(buf.getLineCount()==2);
    cmd1->undo();
    REQUIRE(buf.getLineCount()==2);
}

TEST_CASE("Delete command with execute and undo", "[DeleteCommand]") {
    Buffer buf;
    buf.insertLine(0, "Hello");
    buf.insertLine(1, "World");
    auto cmd1 = make_unique<DeleteCommand>(buf, "", 0, 0, DeleteMode::Char);
    auto cmd2 = make_unique<DeleteCommand>(buf, "", 1, 0, DeleteMode::Line);

    cmd1->execute();
    REQUIRE(buf.getLine(0) == "ello");
    cmd1->undo();
    REQUIRE(buf.getLine(0) == "Hello");

    cmd2->execute();
    REQUIRE(buf.getLineCount() == 1);
    cmd2->undo();
    REQUIRE(buf.getLineCount() == 2);
    REQUIRE(buf.getLine(1) == "World");
}

TEST_CASE("NewLine command with execute and undo", "[NewLineCommand]") {
    Buffer buf;
    buf.insertLine(0, "Hello");
    auto cmd = make_unique<NewLineCommand>(buf, 0);

    cmd->execute();
    REQUIRE(buf.getLineCount() == 2);
    REQUIRE(buf.getLine(1) == "");

    cmd->undo();
    REQUIRE(buf.getLineCount() == 1);
    REQUIRE(buf.getLine(0) == "Hello");
}
