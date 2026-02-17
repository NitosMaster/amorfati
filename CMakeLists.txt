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
FetchContent_MakeAvailable(glfw)

add_library(glad dependencies/glad/src/gl.c)
target_include_directories(glad PUBLIC dependencies/glad/include)

#«== define engine ==»#

add_library(amorfatiEngine
    src/amorfati/core/Window.cpp
    src/amorfati/core/Window.h
    src/amorfati/core/Shader.h
    src/amorfati/core/Shader.cpp
    src/amorfati/factories/CreateVertFrag.h
    src/amorfati/factories/CreateVertFrag.cpp
    src/amorfati/factories/CreateVAO.h
    src/amorfati/factories/CreateVAO.cpp
    src/amorfati/math/Matrix.cpp
    src/amorfati/math/Matrix.h
    src/amorfati/math/Vector.cpp
    src/amorfati/math/Vector.h
    src/amorfati/math/Quaternion.cpp
    src/amorfati/math/Quaternion.h
)

if(MSVC)
    target_compile_options(amorfatiEngine PRIVATE /arch:SSE2)
else()
    target_compile_options(amorfatiEngine PRIVATE -msse2 -mms-bitfields)
endif()

target_link_libraries(amorfatiEngine PUBLIC glfw glad)
target_include_directories(amorfatiEngine PUBLIC src)

add_executable(Sandbox src/main.cpp)
target_link_libraries(Sandbox amorfatiEngine)
