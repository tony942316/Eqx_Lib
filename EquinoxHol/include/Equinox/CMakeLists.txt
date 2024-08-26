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

add_library(EquinoxHol INTERFACE)
target_sources(EquinoxHol INTERFACE
        Equinox.hpp
        Client/Client.hpp
        Math/Math.hpp
            Math/Core.hpp
            Math/Modulator.hpp
            Math/Range.hpp
            Math/Trig.hpp
        Misc/Misc.hpp
        Point/Point.hpp
        Random/Random.hpp
        Rectangle/Rectangle.hpp
        Server/Server.hpp
        StopWatch/StopWatch.hpp)

target_include_directories(EquinoxHol INTERFACE ..)
target_compile_features(EquinoxHol INTERFACE cxx_std_20)

target_link_libraries(EquinoxHol INTERFACE Stdh)

set_target_properties(EquinoxHol PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
