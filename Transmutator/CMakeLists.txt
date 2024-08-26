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

add_executable(Transmutator)
target_sources(Transmutator PRIVATE Main.cpp)

set_target_properties(Transmutator PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

target_link_libraries(Transmutator PRIVATE GMF EquinoxMod)
#target_link_libraries(GMF INTERFACE EQX-Typical)

add_executable(TestHol)
target_sources(TestHol PRIVATE TestHol.cpp)
target_link_libraries(TestHol PRIVATE GMF EquinoxHol)

set_target_properties(TestHol PROPERTIES
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else ()
    target_compile_options(GMF INTERFACE
        -Wno-deprecated-declarations)
endif()
