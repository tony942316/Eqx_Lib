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

add_executable(ProvingGrounds_Debug Main.cpp)

set_target_properties(ProvingGrounds_Debug PROPERTIES
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

target_link_libraries(ProvingGrounds_Debug PRIVATE Equinox)
target_link_libraries(ProvingGrounds_Debug PRIVATE UnitTester)

if (MSVC)
    target_compile_options(ProvingGrounds_Debug PRIVATE /W4 /GR- /EHsc)
else ()
    target_compile_options(ProvingGrounds_Debug PRIVATE -Wall -Wextra -Wpedantic
        -Wconversion -fno-rtti -fno-exceptions)
endif()

add_executable(ProvingGrounds_Release Main.cpp)

set_target_properties(ProvingGrounds_Release PROPERTIES
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)

target_link_libraries(ProvingGrounds_Release PRIVATE Equinox)
target_link_libraries(ProvingGrounds_Release PRIVATE UnitTester)

if (MSVC)
    target_compile_options(ProvingGrounds_Release PRIVATE /W4 /GR- /EHsc /O2t)
else ()
    target_compile_options(ProvingGrounds_Release PRIVATE -Wall -Wextra
        -Wpedantic -Wconversion -fno-rtti -fno-exceptions -O3)
endif()
