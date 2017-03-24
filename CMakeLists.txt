cmake_minimum_required(VERSION 3.7)
project(projectNP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c
        chess.h protocol.h)

add_executable(projectNP ${SOURCE_FILES})