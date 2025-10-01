# Polygon.cmake

add_executable(Polygon)
target_sources(Polygon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Polygon.cpp)
target_compile_features(Polygon PRIVATE cxx_std_20)
target_compile_definitions(Polygon PRIVATE
    CMAKE_TARGET_NAME=Polygon)
target_link_libraries(Polygon PRIVATE Eqx_Lib gtest_hu Eqx_Warnings_Error)
set_target_properties(Polygon PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

add_executable(Polygon_Typical)
target_sources(Polygon_Typical PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Polygon.cpp)
target_compile_features(Polygon_Typical PRIVATE cxx_std_20)
target_compile_definitions(Polygon_Typical PRIVATE
    CMAKE_TARGET_NAME=Polygon_Typical)
target_link_libraries(Polygon_Typical PRIVATE
    Eqx_Lib_Typical gtest_hu_typical Eqx_Warnings_Error)
set_target_properties(Polygon_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS On)

gtest_discover_tests(Polygon)
gtest_discover_tests(Polygon_Typical)
