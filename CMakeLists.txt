cmake_minimum_required(VERSION 3.26)
project(MoveChar)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

add_executable(MoveChar main.cpp
        game/PushBlocks.cpp
        game/PushBlocks.h
)
