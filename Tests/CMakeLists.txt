cmake_minimum_required(VERSION 3.28)

add_executable(Main)
target_sources(Main PRIVATE Main.cpp)
target_compile_features(Main PRIVATE cxx_std_20)
set_target_properties(Main PROPERTIES
    CXX_STANDARD_REQUIRED On
    EXPORT_COMPILE_COMMANDS On
    CXX_EXTENSIONS Off)
target_link_libraries(Main PRIVATE Eqx_Lib)

add_test(NAME Main_Smoke
    COMMAND $<TARGET_FILE:Main>)
