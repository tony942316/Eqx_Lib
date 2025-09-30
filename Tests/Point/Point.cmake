# Point.cmake

add_executable(Point)
target_sources(Point PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Point.cpp)
target_compile_features(Point PRIVATE cxx_std_20)
target_compile_definitions(Point PRIVATE
    CMAKE_TARGET_NAME=Point)
target_link_libraries(Point PRIVATE Eqx_Lib gtest_hu Eqx_Warnings_Error)
set_target_properties(Point PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

add_executable(Point_Typical)
target_sources(Point_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Point.cpp)
target_compile_features(Point_Typical PRIVATE cxx_std_20)
target_compile_definitions(Point_Typical PRIVATE
    CMAKE_TARGET_NAME=Point_Typical)
target_link_libraries(Point_Typical PRIVATE
    Eqx_Lib_Typical gtest_hu_typical Eqx_Warnings_Error)
set_target_properties(Point_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

gtest_discover_tests(Point)
gtest_discover_tests(Point_Typical)
