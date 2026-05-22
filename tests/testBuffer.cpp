//
// Created by David on 5/22/2026.
//

#include <catch2/catch_test_macros.hpp>
#include "Buffer.h"
#include "EditorException.h"

TEST_CASE("Buffer insert and get line", "[buffer]") {
    Buffer buf;
    buf.insertLine(0, "Hello");
    REQUIRE(buf.getLineCount()==1);
    REQUIRE(buf.getLine(0)=="Hello");
}

TEST_CASE("Buffer delete line", "[buffer]") {
    Buffer buf;
    buf.insertLine(0, "something");
    buf.insertLine(1, "something else");
    buf.deleteLine(0);
    REQUIRE(buf.getLine(0)=="something else");
    REQUIRE(buf.getLineCount()==1);
}

TEST_CASE("Buffer on invalid position" , "[buffer]") {
    Buffer buf;

    buf.insertLine(0, "something");
    REQUIRE_THROWS_AS(buf.getLine(3), EditorException);
    REQUIRE_THROWS_AS(buf.getLine(-3213), EditorException);
    REQUIRE_THROWS_AS(buf.insertLine(-34, "invalid"), EditorException);
}

TEST_CASE("Buffer clear", "[buffer]") {
    Buffer buf;
    buf.insertLine(0, "Hello");
    buf.insertLine(1, "World");

    buf.clear();
    REQUIRE(buf.getLineCount() == 0);
}