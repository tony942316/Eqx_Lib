#ifndef EQX_STD_HPP
#define EQX_STD_HPP

#if __cplusplus >= 202002L
    #define CPP_STD 20
#elif __cplusplus >= 201703L
    #define CPP_STD 17
#elif __cplusplus >= 201402L
    #define CPP_STD 14
#elif __cplusplus >= 201103L
    #define CPP_STD 11
#else
    #define CPP_STD 98
#endif // __cplusplus >= 202002L

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

// C Wrappers
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#if CPP_STD >= 11
    #include <array>
    #include <atomic>
    #include <chrono>
    #include <condition_variable>
    #include <forward_list>
    #include <future>
    #include <initializer_list>
    #include <mutex>
    #include <random>
    #include <ratio>
    #include <regex>
    #include <scoped_allocator>
    #include <system_error>
    #include <thread>
    #include <tuple>
    #include <type_traits>
    #include <typeindex>
    #include <unordered_map>
    #include <unordered_set>

    // C Wrappers
    #include <cfenv>
    #include <cinttypes>
    #include <cstdint>
    #include <cstdbool>
    #include <cuchar>
    #include <cstdalign>
    #include <ccomplex>
    #include <ctgmath>

    #ifdef INCLUDE_CODECVT
        #include <codecvt>
    #endif // INCLUDE_CODECVT
#endif // CPP_STD >= 11

#if CPP_STD >= 14
    #include <shared_mutex>
#endif // CPP_STD >= 14

#if CPP_STD >= 17
    #include <any>
    #include <charconv>
    #include <execution>
    #include <filesystem>
    #include <memory_resource>
    #include <optional>
    #include <string_view>
    #include <variant>
    #include <shared_mutex>
#endif // CPP_STD >= 17

#if CPP_STD >= 20
    #include <barrier>
    #include <bit>
    #include <compare>
    #include <concepts>
    #include <coroutine>
    #include <format>
    #include <latch>
    #include <numbers>
    #include <ranges>
    #include <semaphore>
    #include <source_location>
    #include <span>
    #include <stop_token>
    #include <syncstream>
    #include <version>
#endif // CPP_STD >= 20

#undef CPP_STD

#endif // EQX_STD_HPP
