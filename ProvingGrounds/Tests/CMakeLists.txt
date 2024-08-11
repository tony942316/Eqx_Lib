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
