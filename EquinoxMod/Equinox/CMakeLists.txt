#
# Copyright (C) 2024 Anthony H. Grasso
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.28)

function (eqx_add_warnings TARGET SCOPE)

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${TARGET} ${SCOPE}
            /W4)
    else ()
        target_compile_options(${TARGET} ${SCOPE}
            -Wall -Wextra -Wpedantic -Wconversion)
    endif()

endfunction()

function (eqx_add_debug_info TARGET SCOPE)

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${TARGET} ${SCOPE}
            /Zi)
    else ()
        target_compile_options(${TARGET} ${SCOPE}
            -g3)
    endif()

endfunction()

function (eqx_export_compile_commands TARGET)

    set_target_properties(${TARGET} PROPERTIES
        EXPORT_COMPILE_COMMANDS On)

endfunction()

function (eqx_no_extensions TARGET)

    set_target_properties(${TARGET} PROPERTIES
        CXX_EXTENSIONS Off)

endfunction()

function (eqx_set_cxx_20 TARGET SCOPE)

    target_compile_features(${TARGET} ${SCOPE} cxx_std_20)
    set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD_REQUIRED On)

endfunction()

function (eqx_set_optimizations TARGET SCOPE)

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${TARGET} ${SCOPE}
            /O2t)
    else ()
        target_compile_options(${TARGET} ${SCOPE}
            -O3)
    endif()

    target_compile_definitions(${TARGET} ${SCOPE} NDEBUG)

endfunction()

add_library(EquinoxMod STATIC)
target_sources(EquinoxMod
    PUBLIC FILE_SET CXX_MODULES FILES
        Equinox.cpp
        Math.cpp
        Misc.cpp)

eqx_add_warnings(Stdm)
eqx_add_debug_info(Stdm)

eqx_set_cxx_20(EquinoxMod PUBLIC)
eqx_no_extensions(EquinoxMod)
eqx_export_compile_commands(EquinoxMod)
eqx_add_warnings(EquinoxMod PRIVATE)
eqx_add_debug_info(EquinoxMod PRIVATE)

target_link_libraries(EquinoxMod PUBLIC Stdm)
target_include_directories(EquinoxMod PUBLIC include)
