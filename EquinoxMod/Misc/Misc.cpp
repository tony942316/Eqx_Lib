/*
 * Copyright (C) 2024 Anthony H. Grasso
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

export module Eqx.Lib.Misc;

import <Eqx/std.hpp>;

import <Eqx/Lib/Macros.hpp>;

export namespace eqx
{
    using ssize_t = std::make_signed_t<std::size_t>;

    template <typename T>
    constexpr auto nullp = static_cast<T*>(nullptr);

    template <typename T>
    concept StringConvertable =
        requires(const T& val) { std::to_string(val); };

    template <typename T>
    concept StringConstructable =
        requires(const T& val) { std::string{ val }; };

    template <typename T>
    concept Streamable =
        requires(const T& val, std::ostream& out) { out << val; };

    template <typename T, typename F>
        requires requires(const F& f) { static_cast<T>(f); }
    [[nodiscard]] constexpr T staticCast(const F& f) noexcept;

    template <typename T>
    [[nodiscard]] constexpr std::string toString(const T& val) noexcept;

    [[nodiscard]] constexpr char toLower(char val) noexcept;

    [[nodiscard]] constexpr std::string
        toLower(const std::string_view str) noexcept;

    [[nodiscard]] constexpr std::vector<std::string> parseString(
        const std::string_view str, const std::string_view pat) noexcept;

    template <typename T>
        requires eqx::Streamable<T>
    void print(const T& msg, std::ostream& out) noexcept;

    template <typename T>
        requires (!eqx::Streamable<T>) &&
            requires(const T& val) { eqx::toString(val); }
    void print(const T& msg, std::ostream& out) noexcept;

    template <typename T>
    void print(const T& msg) noexcept;

    template <typename T>
    void println(const T& msg, std::ostream& out) noexcept;

    template <typename T>
    void println(const T& msg) noexcept;

    constexpr void ensure(const bool expr,
        const std::string_view msg = std::string_view{},
        const std::source_location& loc = std::source_location::current())
        noexcept;

    consteval void noOp() noexcept;
}

export namespace eqx::stream
{
    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
    std::ostream& operator<< (std::ostream& outStream, const T& val);
}

export namespace eqx::literals
{
    consteval std::size_t operator""_size (unsigned long long val) noexcept;

    consteval std::size_t operator""_uz (unsigned long long val) noexcept;

    consteval eqx::ssize_t operator""_z (unsigned long long val) noexcept;

    consteval short operator""_short (unsigned long long val) noexcept;

    consteval unsigned short operator""_ushort (unsigned long long val)
        noexcept;

    consteval std::int8_t operator""_i8 (unsigned long long val) noexcept;

    consteval std::int16_t operator""_i16 (unsigned long long val) noexcept;

    consteval std::int32_t operator""_i32 (unsigned long long val) noexcept;

    consteval std::int64_t operator""_i64 (unsigned long long val) noexcept;

    consteval std::uint8_t operator""_u8 (unsigned long long val) noexcept;

    consteval std::uint16_t operator""_u16 (unsigned long long val) noexcept;

    consteval std::uint32_t operator""_u32 (unsigned long long val) noexcept;

    consteval std::uint64_t operator""_u64 (unsigned long long val) noexcept;

    consteval unsigned long long operator""_KB (unsigned long long val)
        noexcept;
}

// Implementations

export namespace eqx
{
    template <typename T, typename F>
        requires requires(const F& f) { static_cast<T>(f); }
    [[nodiscard]] constexpr T staticCast(const F& f) noexcept
    {
        return static_cast<T>(f);
    }

    template <typename T>
   [[nodiscard]] constexpr std::string toString(const T& val) noexcept
   {
        if constexpr (StringConstructable<T>)
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
            return std::string{ val };
            // NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
        }
        else if constexpr (StringConvertable<T>)
        {
            return std::to_string(val);
        }
        else if constexpr (requires(const T& x) { x.first; x.second; })
        {
            return "("s + eqx::toString(val.first) + ", "s +
                eqx::toString(val.second) + ")"s;
        }
        else if constexpr (std::ranges::range<T>)
        {
            return std::ranges::empty(val) ? "{ }"s
                : std::transform_reduce(
                std::ranges::cbegin(val) + 1, std::ranges::cend(val),
                "{ "s + eqx::toString(val.front()),
                [](const std::string& left, const std::string& right)
                {
                    return left + ", "s + right;
                },
                [](const auto& ele)
                {
                    return eqx::toString(ele);
                }) + " }"s;
        }
        else if constexpr (requires(const T& x) { x.toString(); })
        {
            return val.toString();
        }
        else
        {
            eqx::ENSURE_HARD(false);
            return std::string{};
        }
   }

    [[nodiscard]] constexpr char toLower(char val) noexcept
    {
        if (std::is_constant_evaluated())
        {
            constexpr auto c_Offset = static_cast<char>(32);
            return val < 'A' || val > 'Z' ?
                val : static_cast<char>(val + c_Offset);
        }
        else
        {
            return std::tolower(val, std::locale{});
        }
    }

    [[nodiscard]] constexpr std::string
        toLower(const std::string_view str) noexcept
    {
        auto result = str
            | std::views::transform([](const char ele)
                {
                    return eqx::toLower(ele);
                });
        return std::string{ std::ranges::cbegin(result),
            std::ranges::cend(result) };
    }

    [[nodiscard]] constexpr std::vector<std::string> parseString(
        const std::string_view str, const std::string_view pat) noexcept
    {
        auto result = str
            | std::views::split(pat)
            | std::views::transform([](const auto& ele)
                {
                    return std::string_view{ std::ranges::cbegin(ele),
                        std::ranges::cend(ele) };
                })
            | std::views::filter([](const auto& ele)
                {
                    return !std::ranges::empty(ele);
                });


        return std::vector<std::string>{ std::ranges::begin(result),
            std::ranges::end(result) };
    }

    template <typename T>
        requires eqx::Streamable<T>
    void print(const T& msg, std::ostream& out) noexcept
    {
        out << msg;
    }

    template <typename T>
        requires (!eqx::Streamable<T>) &&
            requires(const T& val) { eqx::toString(val); }
    void print(const T& msg, std::ostream& out) noexcept
    {
        out << eqx::toString(msg);
    }

    template <typename T>
    void print(const T& msg) noexcept
    {
        eqx::print(msg, std::cout);
    }

    template <typename T>
    void println(const T& msg, std::ostream& out) noexcept
    {
        eqx::print(msg, out);
        eqx::print("\n"sv, out);
    }

    template <typename T>
    void println(const T& msg) noexcept
    {
        eqx::println(msg, std::cout);
    }

    constexpr void ensure(const bool expr, const std::string_view msg,
        const std::source_location& loc) noexcept
    {
        if constexpr (EQX_NO_ASSERTS)
        {
            // No-Op
        }
        else
        {
            if (!expr)
            {
                std::cerr << "Runtime Assertion Failed!\n"sv
                    << "File: "sv << loc.file_name() << '\n'
                    << "Function: "sv << loc.function_name() << '\n'
                    << "Line: "sv << loc.line() << '\n';

                if (!std::ranges::empty(msg))
                {
                    std::cerr << "Msg: "sv << msg << '\n';
                }

                std::terminate();
            }
        }
    }

    consteval void noOp() noexcept {};
}

export namespace eqx::stream
{
    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
    std::ostream& operator<< (std::ostream& outStream, const T& val)
    {
        const auto str = eqx::toString(val);
        return outStream.write(str.c_str(),
            static_cast<std::streamsize>(std::ranges::size(str)));
    }
}

export namespace eqx::literals
{
    consteval std::size_t operator""_size (unsigned long long val) noexcept
    {
        return static_cast<std::size_t>(val);
    }

    consteval std::size_t operator""_uz (unsigned long long val) noexcept
    {
        return static_cast<std::size_t>(val);
    }

    consteval eqx::ssize_t operator""_z (unsigned long long val) noexcept
    {
        return static_cast<eqx::ssize_t>(val);
    }

    consteval short operator""_short (unsigned long long val) noexcept
    {
        return static_cast<short>(val);
    }

    consteval unsigned short operator""_ushort (unsigned long long val)
        noexcept
    {
        return static_cast<unsigned short>(val);
    }

    consteval std::int8_t operator""_i8 (unsigned long long val) noexcept
    {
        return static_cast<std::int8_t>(val);
    }

    consteval std::int16_t operator""_i16 (unsigned long long val) noexcept
    {
        return static_cast<std::int16_t>(val);
    }

    consteval std::int32_t operator""_i32 (unsigned long long val) noexcept
    {
        return static_cast<std::int32_t>(val);
    }

    consteval std::int64_t operator""_i64 (unsigned long long val) noexcept
    {
        return static_cast<std::int64_t>(val);
    }

    consteval std::uint8_t operator""_u8 (unsigned long long val) noexcept
    {
        return static_cast<std::uint8_t>(val);
    }

    consteval std::uint16_t operator""_u16 (unsigned long long val) noexcept
    {
        return static_cast<std::uint16_t>(val);
    }

    consteval std::uint32_t operator""_u32 (unsigned long long val) noexcept
    {
        return static_cast<std::uint32_t>(val);
    }

    consteval std::uint64_t operator""_u64 (unsigned long long val) noexcept
    {
        return static_cast<std::uint64_t>(val);
    }

    consteval unsigned long long operator""_KB (unsigned long long val)
        noexcept
    {
        constexpr auto bytes = 1024ULL;
        return val * bytes;
    }
}
