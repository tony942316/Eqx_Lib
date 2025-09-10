# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_executable(Manual)
target_sources(Manual PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp)
target_compile_features(Manual PRIVATE cxx_std_20)
target_compile_definitions(Manual PRIVATE
    CMAKE_TARGET_NAME=Manual)
target_link_libraries(Manual PRIVATE Eqx_Lib Eqx_Warnings_Error)
set_target_properties(Manual PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

add_executable(Manual_Typical)
target_sources(Manual_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp)
target_compile_features(Manual_Typical PRIVATE cxx_std_20)
target_compile_definitions(Manual_Typical PRIVATE
    CMAKE_TARGET_NAME=Manual_Typical)
target_link_libraries(Manual_Typical PRIVATE Eqx_Lib_Typical Eqx_Warnings_Error)
set_target_properties(Manual_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)
