cmake_minimum_required(VERSION 3.28)

function(eqx_lib_add_test NAME)
    add_executable(${NAME})
    target_sources(${NAME} PRIVATE ${NAME}.cpp)
    target_compile_features(${NAME} PRIVATE cxx_std_20)
    set_target_properties(${NAME} PROPERTIES
        CXX_STANDARD_REQUIRED On
        EXPORT_COMPILE_COMMANDS On
        CXX_EXTENSINOS Off)
    target_link_libraries(${NAME} PRIVATE Eqx_Lib Eqx_Std)

    add_test(NAME ${NAME}
        COMMAND $<TARGET_FILE:${NAME}>)
endfunction()

eqx_lib_add_test(Test_Point)
