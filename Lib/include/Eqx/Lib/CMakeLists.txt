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

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
    add_custom_target(P_EQX_CT_MACROS
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Macros.pcm")

    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/Macros.pcm"
        COMMENT "Build Macros Header Unit"
        COMMAND clang++ -std=c++20
        $<TARGET_PROPERTY:Eqx_GMF,INTERFACE_COMPILE_OPTIONS>
            -Wno-user-defined-literals
            -Wno-implicit-int-conversion
            -Wno-shorten-64-to-32
            -Wno-sign-conversion
            -Wno-unknown-warning-option
            -Wno-inline-namespace-reopened-noninline
            -Wno-deprecated-builtins
            -Wno-implicit-float-conversion
            -Wno-keyword-compat
            -Wno-gnu-include-next
            -Wno-ambiguous-ellipsis
            -Wno-pragma-system-header-outside-header

            -I${CMAKE_CURRENT_SOURCE_DIR}/include/
            -xc++-system-header --precompile Eqx/Lib/Macros.hpp
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/Eqx/Lib/Macros.hpp"
        COMMAND_EXPAND_LISTS)

    add_library(P_EQX_HU_MACROS INTERFACE)
    add_dependencies(P_EQX_HU_MACROS P_EQX_CT_MACROS)
    target_compile_options(P_EQX_HU_MACROS INTERFACE
        -Wno-experimental-header-units
        -fmodule-file=${CMAKE_CURRENT_BINARY_DIR}/Macros.pcm)
endif()

add_library(Eqx_Lib STATIC)
target_sources(Eqx_Lib
    PUBLIC FILE_SET CXX_MODULES FILES
        Eqx_Lib.cpp
        Client/Client.cpp
        Math/Math.cpp
            Math/Core.cpp
            Math/Modulator.cpp
            Math/Range.cpp
            Math/Trig.cpp
        Misc/Misc.cpp
        Point/Point.cpp
        Random/Random.cpp
        Rectangle/Rectangle.cpp
        Server/Server.cpp
        Socket/Socket.cpp
        StopWatch/StopWatch.cpp)

target_include_directories(Eqx_Lib PUBLIC include)
target_compile_features(Eqx_Lib PUBLIC cxx_std_20)
target_link_libraries(Eqx_Lib PUBLIC Eqx_Std)

set_target_properties(Eqx_Lib PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
    target_link_libraries(Eqx_Lib PUBLIC P_EQX_HU_MACROS)
endif()
