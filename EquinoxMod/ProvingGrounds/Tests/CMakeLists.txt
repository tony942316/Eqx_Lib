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

add_library(EquinoxModTests STATIC)
target_sources(EquinoxModTests
    PUBLIC FILE_SET CXX_MODULES FILES
        ClientServer/ClientServer.cpp
        Math/Math.cpp
            Math/Core.cpp
            Math/Modulator.cpp
            Math/Range.cpp
            Math/Trig.cpp
        Misc/Misc.cpp
            Misc/Core.cpp
        Point/Point.cpp
            Point/Core.cpp
        Random/Random.cpp
        Rectangle/Rectangle.cpp
            Rectangle/Core.cpp
        StopWatch/StopWatch.cpp
        Tests.cpp)
target_compile_features(EquinoxModTests PUBLIC cxx_std_20)
target_link_libraries(EquinoxModTests PUBLIC EquinoxMod UnitTester)

set_target_properties(EquinoxModTests PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
