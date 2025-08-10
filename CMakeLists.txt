cmake_minimum_required(VERSION 3.28)

project(Eqx_Lib
    VERSION 2.0.0.0
    DESCRIPTION "Drop In C++ Extension"
    HOMEPAGE_URL "https://github.com/tony942316/Eqx_Lib"
    LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    Eqx_Std
    GIT_REPOSITORY https://github.com/tony942316/Eqx_Std.git
    GIT_TAG main)

FetchContent_MakeAvailable(Eqx_Std)

add_subdirectory(Lib/)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(Tests/)
endif()
