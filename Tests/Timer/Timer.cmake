# Timer.cmake

add_executable(Timer)
target_sources(Timer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp)
target_compile_features(Timer PRIVATE cxx_std_20)
target_compile_definitions(Timer PRIVATE
    CMAKE_TARGET_NAME=Timer)
target_link_libraries(Timer PRIVATE Eqx_Lib gtest_hu Eqx_Warnings_Error)
set_target_properties(Timer PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

add_executable(Timer_Typical)
target_sources(Timer_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp)
target_compile_features(Timer_Typical PRIVATE cxx_std_20)
target_compile_definitions(Timer_Typical PRIVATE
    CMAKE_TARGET_NAME=Timer_Typical)
target_link_libraries(Timer_Typical PRIVATE
    Eqx_Lib_Typical gtest_hu_typical Eqx_Warnings_Error)
set_target_properties(Timer_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

gtest_discover_tests(Timer)
gtest_discover_tests(Timer_Typical)
