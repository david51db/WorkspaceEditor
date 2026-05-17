cmake_minimum_required(VERSION 4.1)
project(WorkspaceEditor)

set(CMAKE_CXX_STANDARD 20)

add_executable(WorkspaceEditor main.cpp
        include/Buffer.h)
