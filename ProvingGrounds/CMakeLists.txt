cmake_minimum_required(VERSION 3.28)

add_subdirectory(UnitTester)
add_subdirectory(Tests)

add_executable(ProvingGroundsMod)
target_sources(ProvingGroundsMod PRIVATE Main.cpp)

set_target_properties(ProvingGroundsMod PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

target_link_libraries(ProvingGroundsMod PRIVATE EquinoxModTests)
#target_link_libraries(GMF INTERFACE EQX-Typical)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(GMF INTERFACE
        /constexpr:steps100000000)
else ()
    target_compile_options(GMF INTERFACE
        -fconstexpr-steps=100000000 -Wno-deprecated-declarations)
endif()
