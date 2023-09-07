#
# Copyright (C) 2023 Anthony H. Grasso
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

cmake_minimum_required(VERSION 3.20)

add_executable(ProvingGrounds Main.cpp)

set_target_properties(ProvingGrounds PROPERTIES
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

target_link_libraries(ProvingGrounds PRIVATE Equinox)
target_link_libraries(ProvingGrounds PRIVATE UnitTester)

if (MSVC)
    target_compile_options(ProvingGrounds PRIVATE /W4 /GR-)
else ()
    target_compile_options(ProvingGrounds PRIVATE -Wall -Wextra -Wpedantic
        -Wconversion -fno-rtti -fno-exceptions)
endif()
