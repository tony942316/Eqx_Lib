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

add_library(EquinoxMod STATIC)
target_sources(EquinoxMod
    PUBLIC FILE_SET CXX_MODULES FILES
        Equinox.cpp
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

target_include_directories(EquinoxMod PUBLIC include)
target_compile_features(EquinoxMod PUBLIC cxx_std_20)
target_link_libraries(EquinoxMod PUBLIC GMF Stdm)

set_target_properties(EquinoxMod PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
