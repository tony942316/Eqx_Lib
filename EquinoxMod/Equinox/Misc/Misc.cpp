module;

#include <Equinox/Macros.hpp>

export module Equinox.Misc;

import Eqx.Stdm;

export namespace eqx
{
    using ssize_t = stdm::make_signed_t<stdm::size_t>;

    template <typename T>
    constexpr auto nullp = static_cast<T*>(nullptr);

    template <typename T>
    concept StringConvertable =
        requires(const T& val) { stdm::to_string(val); };

    template <typename T>
    concept StringConstructable =
        requires(const T& val) { stdm::string{ val }; };

    template <typename T>
    concept Streamable =
        requires(const T& val, stdm::ostream& out) { out << val; };

    template <typename T, typename F>
        requires requires(const F& f) { static_cast<T>(f); }
    [[nodiscard]] constexpr T staticCast(const F& f) noexcept;

    template <typename T>
    [[nodiscard]] constexpr stdm::string toString(const T& val) noexcept;

    [[nodiscard]] constexpr char toLower(char val) noexcept;

    [[nodiscard]] constexpr stdm::string
        toLower(const stdm::string_view str) noexcept;

    [[nodiscard]] constexpr stdm::vector<stdm::string> parseString(
        const stdm::string_view str, const stdm::string_view pat) noexcept;

    template <typename T>
        requires eqx::Streamable<T>
    void print(const T& msg, stdm::ostream& out) noexcept;

    template <typename T>
        requires (!eqx::Streamable<T>) &&
            requires(const T& val) { eqx::toString(val); }
    void print(const T& msg, stdm::ostream& out) noexcept;

    template <typename T>
    void print(const T& msg) noexcept;

    template <typename T>
    void println(const T& msg, stdm::ostream& out) noexcept;

    template <typename T>
    void println(const T& msg) noexcept;

    constexpr void ensure(const bool expr,
        const stdm::string_view msg = stdm::string_view{},
        const stdm::source_location& loc = stdm::source_location::current())
        noexcept;

    consteval void noOp() noexcept;
}

export namespace eqx::stream
{
    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
    stdm::ostream& operator<< (stdm::ostream& outStream, const T& val);
}

export namespace eqx::literals
{
    consteval stdm::size_t operator""_size (unsigned long long val) noexcept;

    consteval stdm::size_t operator""_uz (unsigned long long val) noexcept;

    consteval eqx::ssize_t operator""_z (unsigned long long val) noexcept;

    consteval short operator""_short (unsigned long long val) noexcept;

    consteval unsigned short operator""_ushort (unsigned long long val)
        noexcept;

    consteval stdm::int8_t operator""_i8 (unsigned long long val) noexcept;

    consteval stdm::int16_t operator""_i16 (unsigned long long val) noexcept;

    consteval stdm::int32_t operator""_i32 (unsigned long long val) noexcept;

    consteval stdm::int64_t operator""_i64 (unsigned long long val) noexcept;

    consteval stdm::uint8_t operator""_u8 (unsigned long long val) noexcept;

    consteval stdm::uint16_t operator""_u16 (unsigned long long val) noexcept;

    consteval stdm::uint32_t operator""_u32 (unsigned long long val) noexcept;

    consteval stdm::uint64_t operator""_u64 (unsigned long long val) noexcept;

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
   [[nodiscard]] constexpr stdm::string toString(const T& val) noexcept
   {
        if constexpr (StringConstructable<T>)
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
            return stdm::string{ val };
            // NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
        }
        else if constexpr (StringConvertable<T>)
        {
            return stdm::to_string(val);
        }
        else if constexpr (requires(const T& x) { x.first; x.second; })
        {
            return "("s + eqx::toString(val.first) + ", "s +
                eqx::toString(val.second) + ")"s;
        }
        else if constexpr (stdm::ranges::range<T>)
        {
            return stdm::ranges::empty(val) ? "{ }"s
                : stdm::transform_reduce(
                stdm::ranges::cbegin(val) + 1, stdm::ranges::cend(val),
                "{ "s + eqx::toString(val.front()),
                [](const stdm::string& left, const stdm::string& right)
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
            return stdm::string{};
        }
   }

    [[nodiscard]] constexpr char toLower(char val) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            constexpr auto c_Offset = static_cast<char>(32);
            return val < 'A' || val > 'Z' ?
                val : static_cast<char>(val + c_Offset);
        }
        else
        {
            return stdm::tolower(val, stdm::locale{});
        }
    }

    [[nodiscard]] constexpr stdm::string
        toLower(const stdm::string_view str) noexcept
    {
        auto result = str
            | stdm::views::transform([](const char ele)
                {
                    return eqx::toLower(ele);
                });
        return stdm::string{ stdm::ranges::cbegin(result),
            stdm::ranges::cend(result) };
    }

    [[nodiscard]] constexpr stdm::vector<stdm::string> parseString(
        const stdm::string_view str, const stdm::string_view pat) noexcept
    {
        auto result = str
            | stdm::views::split(pat)
            | stdm::views::transform([](const auto& ele)
                {
                    return stdm::string_view{ stdm::ranges::cbegin(ele),
                        stdm::ranges::cend(ele) };
                })
            | stdm::views::filter([](const auto& ele)
                {
                    return !stdm::ranges::empty(ele);
                });


        return stdm::vector<stdm::string>{ stdm::ranges::begin(result),
            stdm::ranges::end(result) };
    }

    template <typename T>
        requires eqx::Streamable<T>
    void print(const T& msg, stdm::ostream& out) noexcept
    {
        out << msg;
    }

    template <typename T>
        requires (!eqx::Streamable<T>) &&
            requires(const T& val) { eqx::toString(val); }
    void print(const T& msg, stdm::ostream& out) noexcept
    {
        out << eqx::toString(msg);
    }

    template <typename T>
    void print(const T& msg) noexcept
    {
        eqx::print(msg, stdm::cout);
    }

    template <typename T>
    void println(const T& msg, stdm::ostream& out) noexcept
    {
        eqx::print(msg, out);
        eqx::print("\n"sv, out);
    }

    template <typename T>
    void println(const T& msg) noexcept
    {
        eqx::println(msg, stdm::cout);
    }

    constexpr void ensure(const bool expr, const stdm::string_view msg,
        const stdm::source_location& loc) noexcept
    {
        if constexpr (EQX_NO_ASSERTS)
        {
            // No-Op
        }
        else
        {
            if (!expr)
            {
                stdm::cerr << "Runtime Assertion Failed!\n"sv
                    << "File: "sv << loc.file_name() << '\n'
                    << "Function: "sv << loc.function_name() << '\n'
                    << "Line: "sv << loc.line() << '\n';

                if (!stdm::ranges::empty(msg))
                {
                    stdm::cerr << "Msg: "sv << msg << '\n';
                }

                stdm::terminate();
            }
        }
    }

    consteval void noOp() noexcept {};
}

export namespace eqx::stream
{
    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
    stdm::ostream& operator<< (stdm::ostream& outStream, const T& val)
    {
        const auto str = eqx::toString(val);
        return outStream.write(str.c_str(),
            static_cast<stdm::streamsize>(stdm::ranges::size(str)));
    }
}

export namespace eqx::literals
{
    consteval stdm::size_t operator""_size (unsigned long long val) noexcept
    {
        return static_cast<stdm::size_t>(val);
    }

    consteval stdm::size_t operator""_uz (unsigned long long val) noexcept
    {
        return static_cast<stdm::size_t>(val);
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

    consteval stdm::int8_t operator""_i8 (unsigned long long val) noexcept
    {
        return static_cast<stdm::int8_t>(val);
    }

    consteval stdm::int16_t operator""_i16 (unsigned long long val) noexcept
    {
        return static_cast<stdm::int16_t>(val);
    }

    consteval stdm::int32_t operator""_i32 (unsigned long long val) noexcept
    {
        return static_cast<stdm::int32_t>(val);
    }

    consteval stdm::int64_t operator""_i64 (unsigned long long val) noexcept
    {
        return static_cast<stdm::int64_t>(val);
    }

    consteval stdm::uint8_t operator""_u8 (unsigned long long val) noexcept
    {
        return static_cast<stdm::uint8_t>(val);
    }

    consteval stdm::uint16_t operator""_u16 (unsigned long long val) noexcept
    {
        return static_cast<stdm::uint16_t>(val);
    }

    consteval stdm::uint32_t operator""_u32 (unsigned long long val) noexcept
    {
        return static_cast<stdm::uint32_t>(val);
    }

    consteval stdm::uint64_t operator""_u64 (unsigned long long val) noexcept
    {
        return static_cast<stdm::uint64_t>(val);
    }

    consteval unsigned long long operator""_KB (unsigned long long val)
        noexcept
    {
        constexpr auto bytes = 1024ULL;
        return val * bytes;
    }
}
