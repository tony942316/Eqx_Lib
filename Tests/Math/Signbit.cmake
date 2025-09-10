# Signbit.cmake

add_executable(Math_Signbit)
target_sources(Math_Signbit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Signbit.cpp)
target_compile_features(Math_Signbit PRIVATE cxx_std_20)
target_compile_definitions(Math_Signbit PRIVATE
    CMAKE_TARGET_NAME=Math_Signbit)
target_link_libraries(Math_Signbit PRIVATE Eqx_Lib gtest_hu Eqx_Warnings_Error)
set_target_properties(Math_Signbit PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

add_executable(Math_Signbit_Typical)
target_sources(Math_Signbit_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Signbit.cpp)
target_compile_features(Math_Signbit_Typical PRIVATE cxx_std_20)
target_compile_definitions(Math_Signbit_Typical PRIVATE
    CMAKE_TARGET_NAME=Math_Signbit_Typical)
target_link_libraries(Math_Signbit_Typical PRIVATE
    Eqx_Lib_Typical gtest_hu_typical Eqx_Warnings_Error)
set_target_properties(Math_Signbit_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

gtest_discover_tests(Math_Signbit)
gtest_discover_tests(Math_Signbit_Typical)
