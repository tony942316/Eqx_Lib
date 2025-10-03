# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

include(FetchContent)

FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

target_compile_definitions(gtest_main PRIVATE
    _DISABLE_STRING_ANNOTATION _DISABLE_VECTOR_ANNOTATION)
target_compile_definitions(gtest PRIVATE
    _DISABLE_STRING_ANNOTATION _DISABLE_VECTOR_ANNOTATION)

eqx_add_headerunit(gtest_hu)
target_sources(gtest_hu INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest.hpp)
target_include_directories(gtest_hu INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/)
target_include_directories(gtest_hu_PRIVATE INTERFACE
    $<TARGET_PROPERTY:Eqx_Std,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(gtest_hu_PRIVATE INTERFACE GTest::gtest_main)
target_link_libraries(gtest_hu INTERFACE GTest::gtest_main)

eqx_add_headerunit(gtest_hu_typical)
target_sources(gtest_hu_typical INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest.hpp)
target_include_directories(gtest_hu_typical INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/)
target_include_directories(gtest_hu_typical_PRIVATE INTERFACE
    $<TARGET_PROPERTY:Eqx_Std_Typical,INTERFACE_INCLUDE_DIRECTORIES>)
target_compile_definitions(gtest_hu_typical INTERFACE _DISABLE_STRING_ANNOTATION
    _DISABLE_VECTOR_ANNOTATION)
target_link_libraries(gtest_hu_typical_PRIVATE INTERFACE
    GTest::gtest_main Eqx_Typical)
target_link_libraries(gtest_hu_typical INTERFACE GTest::gtest_main Eqx_Typical)

if (Eqx_Clang OR Eqx_GNU)
    target_compile_options(gtest_hu_PRIVATE INTERFACE -w)
    target_compile_options(gtest_hu_typical_PRIVATE INTERFACE -w)
elseif (Eqx_MSVC)
else()
    message(FATAL_ERROR "Invalid Configuration!")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Math/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Point/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Polygon/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Timer/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Manual/)
