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

#ifndef EQUINOX_DETAILS_MISCIMPL_IPP
#define EQUINOX_DETAILS_MISCIMPL_IPP

#include "MiscDecl.hpp"

namespace eqx
{
    [[nodiscard]] inline std::string toString(const char* cstring)
    {
        return std::string(cstring);
    }

    template <typename T>
        requires Stringable<T>
    [[nodiscard]] std::string toString(const T& val)
    {
        return std::to_string(val);
    }

    template <typename T>
        requires StringType<T>
    [[nodiscard]] std::string toString(const T& val)
    {
        return std::string(val);
    }

    template <typename T, typename U>
    [[nodiscard]] std::string toString(const std::pair<T, U>& val)
    {
        return std::string("(") + toString(val.first) + std::string(", ") +
            toString(val.second) + std::string(")");
    }

    template <typename T>
        requires ConstCollection<T>
    [[nodiscard]] std::string toString(const T& val)
    {
        auto result = std::string("");
        result += "{ ";
        std::ranges::for_each(val,
            [&result](const auto& x)
            {
                result += toString(x);
                result += ", ";
            });
        result.pop_back();
        result.pop_back();
        result += " }";
        return result;
    }

    [[nodiscard]] std::string toLower(std::string_view str) noexcept
    {
        auto result = std::string(str);
        std::ranges::transform(result, std::ranges::begin(result),
            [](unsigned char c)
            {
                return std::tolower(c);
            });
        return result;
    }

    namespace pairPrint
    {
        template <typename T, typename U>
        std::ostream& operator<< (std::ostream& os, std::pair<T, U> p)
        {
            return os << toString(p);
        }
    }

    namespace literals
    {
        consteval std::size_t operator""_size (unsigned long long x) noexcept
        {
            return static_cast<std::size_t>(x);
        }

        consteval short operator""_short (unsigned long long x) noexcept
        {
            return static_cast<short>(x);
        }

        consteval unsigned short operator""_ushort (unsigned long long x)
            noexcept
        {
            return static_cast<unsigned short>(x);
        }

        consteval std::int8_t operator""_i8 (unsigned long long x) noexcept
        {
            return static_cast<std::int8_t>(x);
        }

        consteval std::int16_t operator""_i16 (unsigned long long x) noexcept
        {
            return static_cast<std::int16_t>(x);
        }

        consteval std::int32_t operator""_i32 (unsigned long long x) noexcept
        {
            return static_cast<std::int32_t>(x);
        }

        consteval std::int64_t operator""_i64 (unsigned long long x) noexcept
        {
            return static_cast<std::int64_t>(x);
        }

        consteval std::uint8_t operator""_u8 (unsigned long long x) noexcept
        {
            return static_cast<std::uint8_t>(x);
        }

        consteval std::uint16_t operator""_u16 (unsigned long long x) noexcept
        {
            return static_cast<std::uint16_t>(x);
        }

        consteval std::uint32_t operator""_u32 (unsigned long long x) noexcept
        {
            return static_cast<std::uint32_t>(x);
        }

        consteval std::uint64_t operator""_u64 (unsigned long long x) noexcept
        {
            return static_cast<std::uint64_t>(x);
        }

        consteval unsigned long long operator""_KB (unsigned long long x)
            noexcept
        {
            return x * 1024ULL;
        }
    }

    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
    inline void print(const T& msg, std::ostream& out) noexcept
    {
        out.write(eqx::toString(msg).c_str(),
            static_cast<std::streamsize>(
            std::ranges::size(eqx::toString(msg))));
    }

    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
    inline void println(const T& msg, std::ostream& out) noexcept
    {
        print(msg, out);
        print("\n", out);
    }

    constexpr void runtimeAssert(bool expr, std::string_view msg,
        const std::source_location& loc) noexcept
    {
#ifndef EQX_NO_ASSERTS
        if (!expr)
        {
            // If you got here because of a constexpr evaluation
            // go up the call stack to where this assert was called
            // and ideally there is a message in the msg parameter

            (void)std::fprintf(stderr, "%s", "Runtime Assertion Failed!\n");

            (void)std::fprintf(stderr, "%s", "File: ");
            (void)std::fprintf(stderr, "%s", loc.file_name());
            (void)std::fprintf(stderr, "%s", "\n");

            (void)std::fprintf(stderr, "%s", "Function: ");
            (void)std::fprintf(stderr, "%s", loc.function_name());
            (void)std::fprintf(stderr, "%s", "\n");

            (void)std::fprintf(stderr, "%s", "Line: ");
            (void)std::fprintf(stderr, "%i", loc.line());
            (void)std::fprintf(stderr, "%s", "\n");

            (void)std::fprintf(stderr, "%s", "Errno: ");
            (void)std::fprintf(stderr, "%i", errno);
            (void)std::fprintf(stderr, "%s", "\n");

            if (msg.data() != std::string_view(""))
            {
                (void)std::fprintf(stderr, "%s", "Msg: ");
                (void)std::fprintf(stderr, "%s", msg.data());
                (void)std::fprintf(stderr, "%s", "\n");
            }

            std::abort();
        }
#endif // EQX_NO_ASSERTS
    }

    template <typename C1, typename C2>
        requires ConstCollection<C1> && ConstCollection<C2>
    [[nodiscard]] auto zip(const C1& x, const C2& y)
    {
        runtimeAssert(std::ranges::size(x) == std::ranges::size(y),
            "eqx::zip std::ranges::size(x) != std::ranges::size(y)!");

        using C1HeldValue =
            std::remove_cvref_t<decltype(*std::ranges::cbegin(x))>;
        using C2HeldValue =
            std::remove_cvref_t<decltype(*std::ranges::cbegin(y))>;

        auto zippedRange =
            std::vector<std::pair<C1HeldValue, C2HeldValue>>();
        zippedRange.reserve(std::ranges::size(x));

        auto xIter = std::ranges::cbegin(x);
        auto yIter = std::ranges::cbegin(y);
        for (; xIter != std::ranges::cend(x); xIter++, yIter++)
        {
            zippedRange.emplace_back(*xIter, *yIter);
        }

        return zippedRange;
    }

    template <typename T, typename... Args>
        requires requires(Args&&... args)
            {  new T(std::forward<Args>(args)...); }
    [[nodiscard]] inline T* newAlloc(Args&&... args) noexcept
    {
        return new T(std::forward<Args>(args)...);
    }

    template <typename T>
        requires requires(T* ptr) { delete ptr; }
    inline void deleteDealloc(T* ptr) noexcept
    {
        delete ptr;
    }
}


#endif // EQUINOX_DETAILS_MISCIMPL_IPP
