# CMakeLists.txt

cmake_minimum_required(VERSION 3.28)

add_executable(CT_Math_Signbit)
target_sources(CT_Math_Signbit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Signbit.cpp)
target_compile_features(CT_Math_Signbit PRIVATE cxx_std_20)
target_compile_definitions(CT_Math_Signbit PRIVATE
    CMAKE_TARGET_NAME=CT_Math_Signbit)
target_link_libraries(CT_Math_Signbit PRIVATE Eqx_Lib gtest_hu)
set_target_properties(CT_Math_Signbit PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

add_executable(CT_Math_Signbit_Typical)
target_sources(CT_Math_Signbit_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Signbit.cpp)
target_compile_features(CT_Math_Signbit_Typical PRIVATE cxx_std_20)
target_compile_definitions(CT_Math_Signbit_Typical PRIVATE
    CMAKE_TARGET_NAME=CT_Math_Signbit_Typical)
target_link_libraries(CT_Math_Signbit_Typical PRIVATE
    Eqx_Lib_Typical gtest_hu_typical)
set_target_properties(CT_Math_Signbit_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

include(GoogleTest)
gtest_discover_tests(CT_Math_Signbit)
gtest_discover_tests(CT_Math_Signbit_Typical)
