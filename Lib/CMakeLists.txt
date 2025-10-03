cmake_minimum_required(VERSION 3.28)

add_library(Eqx_Lib STATIC)
target_sources(Eqx_Lib PUBLIC
    FILE_SET CXX_MODULES FILES
        Eqx_Lib.cpp
        Math/CMath.cpp
        Math/Math.cpp
        Point/Point.cpp
        Polygon/Polygon.cpp
        Timer/Timer.cpp)
target_compile_features(Eqx_Lib PUBLIC cxx_std_20)
target_link_libraries(Eqx_Lib PUBLIC Eqx_Std)
set_target_properties(Eqx_Lib PROPERTIES
    CXX_STANDARD_REQUIRED On
    EXPORT_COMPILE_COMMANDS On
    CXX_EXTENSIONS Off)

add_library(Eqx_Lib_Typical STATIC)
target_sources(Eqx_Lib_Typical PUBLIC
    FILE_SET CXX_MODULES FILES
        Eqx_Lib.cpp
        Math/CMath.cpp
        Math/Math.cpp
        Point/Point.cpp
        Polygon/Polygon.cpp
        Timer/Timer.cpp)
target_compile_features(Eqx_Lib_Typical PUBLIC cxx_std_20)
target_link_libraries(Eqx_Lib_Typical PUBLIC Eqx_Std_Typical)
set_target_properties(Eqx_Lib_Typical PROPERTIES
    CXX_STANDARD_REQUIRED On
    EXPORT_COMPILE_COMMANDS On
    CXX_EXTENSIONS Off)
