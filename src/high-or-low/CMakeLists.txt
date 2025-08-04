cmake_minimum_required(VERSION 3.31)
project(high_or_low)

set(CMAKE_CXX_STANDARD 20)

add_executable(high_or_low main.cpp
        stdstrhelper.cpp
        sdtstrhelper.h
        stringconstants.h
        roll_game.cpp
        roll_game.h)
