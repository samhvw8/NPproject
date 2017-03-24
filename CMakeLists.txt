cmake_minimum_required(VERSION 3.6)
project(projectNP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-rdynamic")

set(SOURCE_FILES
        main.c
        chess.h protocol.h ui.h handle.c)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0 gmodule-2.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})



add_executable(projectNP ${SOURCE_FILES})


target_link_libraries(projectNP ${GTK3_LIBRARIES})