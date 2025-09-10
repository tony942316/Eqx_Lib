# Sqrt.cmake

add_executable(Math_Sqrt)
target_sources(Math_Sqrt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sqrt.cpp)
target_compile_features(Math_Sqrt PRIVATE cxx_std_20)
target_compile_definitions(Math_Sqrt PRIVATE
    CMAKE_TARGET_NAME=Math_Sqrt)
target_link_libraries(Math_Sqrt PRIVATE Eqx_Lib gtest_hu Eqx_Warnings_Error)
set_target_properties(Math_Sqrt PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

add_executable(Math_Sqrt_Typical)
target_sources(Math_Sqrt_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Sqrt.cpp)
target_compile_features(Math_Sqrt_Typical PRIVATE cxx_std_20)
target_compile_definitions(Math_Sqrt_Typical PRIVATE
    CMAKE_TARGET_NAME=Math_Sqrt_Typical)
target_link_libraries(Math_Sqrt_Typical PRIVATE
    Eqx_Lib_Typical gtest_hu_typical Eqx_Warnings_Error)
set_target_properties(Math_Sqrt_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

gtest_discover_tests(Math_Sqrt)
gtest_discover_tests(Math_Sqrt_Typical)
