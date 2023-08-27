/*
 * Copyright (C) 2023 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef EQUINOX_CPP_STD_HPP
#define EQUINOX_CPP_STD_HPP

//C Lib
#include <cstring>

//STL Concepts
#include <concepts>

//STL Diagnostics
#include <cerrno>
#include <source_location>

//STL Meta
#include <limits>
#include <type_traits>

//STL Utilities
#include <utility>
#include <optional>
#include <functional>

//STL Strings
#include <string>
#include <string_view>

//STL Containers
#include <array>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

//STL Ranges
#include <ranges>

//STL Algorithms
#include <algorithm>

//STL Numerics
#include <numeric>
#include <numbers>
#include <cmath>
#include <random>

//STL Time
#include <chrono>

//STL IO
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

//STL Concurrency
#include <thread>

//Windows Headers
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#define NOMINMAX

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")
#endif

//Mac Headers
#ifdef __APPLE__
#endif

//Linux Headers
#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#endif // EQUINOX_CPP_STD_HPP
