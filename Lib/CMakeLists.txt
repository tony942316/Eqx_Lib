cmake_minimum_required(VERSION 3.28)

add_library(Eqx_Lib STATIC)
target_sources(Eqx_Lib PUBLIC
    FILE_SET CXX_MODULES FILES
        Eqx_Lib.cpp
        Math/CT_Math.cpp
        Math/Math.cpp
        Point/Point.cpp
        Poly/Poly.cpp)
target_compile_features(Eqx_Lib PUBLIC cxx_std_20)
set_target_properties(Eqx_Lib PROPERTIES
    CXX_STANDARD_REQUIRED On
    EXPORT_COMPILE_COMMANDS On
    CXX_EXTENSIONS Off)
target_link_libraries(Eqx_Lib PUBLIC Eqx_Std)
