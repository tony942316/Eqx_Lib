# Equinox

## Contents

1. [Introduction](#intro)
2. [Adding Equinox To Your Project](#adding)
3. [Using Equinox](#using)

## Introduction <a name="intro"></a>

Equinox is an Open Source, Cross-platform, Header-only library for C++. It
provides many quality of life features to enhance the programming experience
such as, easy random number generation, logging, timing, reflective enums, and
more.

Equinox requires a C++20 compiler and is tested on both Windows and Linux.

Equinox is licensed under the [GPL-3.0 license](https://www.gnu.org/licenses/gpl-3.0.en.html).

You can get the latest header files from the main branch or relevent
release branch r-X.X.X


## Adding Equinox To Your Project <a name="adding"></a>

Please ensure that you are using a C++20 compiler, at the time of writing
gcc version 12+ and MSVC with the `/Zc:preprocessor` flag have the required
features for compilation.

### CMake

With CMake simply add Equinox as a subdirectory.
```cmake
add_subdirectory(Path/To/Equinox)
```

### Agnostic

For other build systems simply add Equinox/include/ to your include paths


## Using Equinox <a name="using"></a>

After adding Equinox to your build system you can begin using its features,
simply `#include <Equinox/Equinox.hpp>` to access the entire library or you
may access single parts with `#include <Equinox/Headers/{Feature}.hpp>`
