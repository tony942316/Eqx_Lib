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

add_executable(ProvingGroundsMod_Debug)
target_sources(ProvingGroundsMod_Debug PRIVATE Main.cpp)

set_target_properties(ProvingGroundsMod_Debug PROPERTIES
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

target_link_libraries(ProvingGroundsMod_Debug PRIVATE EquinoxMod)
target_compile_definitions(ProvingGroundsMod_Debug PRIVATE EQX_NO_ASSERTS)
eqx_add_warnings(ProvingGroundsMod_Debug)

if (MSVC)
    target_compile_options(ProvingGroundsMod_Debug PRIVATE /W4 /GR- /EHsc)
else ()
    target_compile_options(ProvingGroundsMod_Debug PRIVATE
        -g3
        -fno-rtti -ffast-math -fno-exceptions)
        #-Wall -Wextra -Wpedantic -Wconversion)
endif()

################################################################################

#add_executable(ProvingGroundsMod_Release)
#target_sources(ProvingGroundsMod_Release PRIVATE Main.cpp)

#set_target_properties(ProvingGroundsMod_Debug PROPERTIES
#    CXX_EXTENSIONS Off
#    EXPORT_COMPILE_COMMANDS On)

#target_link_libraries(ProvingGroundsMod_Release PRIVATE EquinoxMod)
#target_compile_definitions(ProvingGroundsMod_Release PRIVATE EQX_NO_ASSERTS)

#if (MSVC)
#    target_compile_options(ProvingGroundsMod_Release PRIVATE /W4 /GR- /EHsc)
#else ()
#    target_compile_options(ProvingGroundsMod_Release PRIVATE -Wall -Wextra
#        -Wpedantic -Wconversion)
#endif()
