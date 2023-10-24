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

project(
    Equinox
    VERSION 1.1.3
    DESCRIPTION "Drop In C++ Extension"
    LANGUAGES CXX)

add_library(Equinox INTERFACE include/Equinox/Equinox.hpp)

set_target_properties(Equinox PROPERTIES
    CXX_STANDARD_REQUIRED On)

target_include_directories(Equinox INTERFACE include)

target_compile_features(Equinox INTERFACE cxx_std_20)
if (MSVC)
    target_compile_options(Equinox INTERFACE /Zc:preprocessor)
endif()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(UnitTester)
    add_subdirectory(ProvingGrounds)
endif()
