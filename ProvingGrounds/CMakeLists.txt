cmake_minimum_required(VERSION 3.28)

add_subdirectory(UnitTester)
add_subdirectory(Tests)

add_executable(ProvingGrounds)
target_sources(ProvingGrounds PRIVATE Main.cpp)

set_target_properties(ProvingGrounds PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

target_link_libraries(ProvingGrounds PRIVATE Tests)
target_link_libraries(Eqx_GMF INTERFACE EQX-Typical)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Eqx_GMF INTERFACE
        /constexpr:steps100000000)
else ()
    target_compile_options(Eqx_GMF INTERFACE
        -fconstexpr-steps=100000000 -Wno-deprecated-declarations)
endif()
