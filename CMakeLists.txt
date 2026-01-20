#«== FetchContent_Declare is a module for some stupid reason ==»#
include(FetchContent)

cmake_minimum_required(VERSION 3.15)
project(amorfati VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#«== add dependencies ==»#

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)

FetchContent_MakeAvailable(glfw glad)

#«== define engine ==»#

add_library(amorfatiEngine
    src/amorfati/core/Window.cpp
    src/amorfati/core/Window.h
)

add_executable(Sandbox src/main.cpp)
target_link_libraries(Sandbox amorfatiEngine)
