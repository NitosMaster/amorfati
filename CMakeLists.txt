cmake_minimum_required(VERSION 3.15)
project(amorfati VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(amorfatiEngine
    src/amorfati/core/Window.cpp
    src/amorfati/core/Window.h
)

add_executable(Sandbox src/main.cpp)
target_link_libraries(Sandbox amorfatiEngine)
