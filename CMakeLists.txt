cmake_minimum_required(VERSION 3.10)
project(X-O)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(C:/libs/raylib-6.0 raylib_build)

add_executable(X-O main.cpp
    dto/table.cpp
    function/functions.cpp)
target_link_libraries(X-O raylib)