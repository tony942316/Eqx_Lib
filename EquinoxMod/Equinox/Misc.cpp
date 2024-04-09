module;

#include <Equinox/Macros.hpp>

export module Equinox.Misc;

import Stdm;

#ifndef EQX_NO_ASSERTS
static_assert(false);
#endif

export namespace eqx
{
    using ssize_t = stdm::make_signed_t<stdm::size_t>;

    template <typename T>
    inline constexpr auto nullp = static_cast<T*>(nullptr);

    template <typename T>
    concept StringConvertable =
        requires(const T& val) { stdm::to_string(val); };

    template <typename T>
    concept StringConstructable =
        requires(const T& val) { stdm::string{ val }; };

    template <typename T>
        requires StringConstructable<T>
    [[nodiscard]] stdm::string toString(const T& val) noexcept
    {
        return stdm::string{ val };
    }

    template <typename T>
        requires StringConvertable<T> && (!StringConstructable<T>)
    [[nodiscard]] stdm::string toString(const T& val) noexcept
    {
        return stdm::to_string(val);
    }

    template <typename T, typename U>
        requires requires(const stdm::pair<T, U>& val)
            { eqx::toString(val.first); eqx::toString(val.second); }
    [[nodiscard]] stdm::string toString(const stdm::pair<T, U>& val) noexcept
    {
        return "( "s + eqx::toString(val.first) + ", "s +
            eqx::toString(val.second) + " )"s;
    }

    template <typename T>
        requires stdm::ranges::range<T>
            && (!StringConstructable<T>)
            && (!StringConvertable<T>)
    [[nodiscard]] stdm::string toString(const T& val) noexcept
    {
        auto result = stdm::string{};

        result += "{ "sv;

        auto firstN = val
            | stdm::views::reverse
            | stdm::views::drop(1)
            | stdm::views::reverse
            | stdm::views::transform([](const auto& x)
                { return eqx::toString(x) + ", "s; });
        auto last = val
            | stdm::views::reverse
            | stdm::views::take(1)
            | stdm::views::transform([](const auto& x)
                { return eqx::toString(x); });

        stdm::ranges::for_each(firstN, [&result](const stdm::string& x)
            { result += x; });
        stdm::ranges::for_each(last, [&result](const stdm::string& x)
            { result += x; });


        result += " }"sv;

        return result;
    }

    [[nodiscard]] stdm::string toLower(const stdm::string_view str) noexcept
    {
        auto v = str
            | stdm::views::transform([](const char c)
                {
                    return stdm::tolower(c, stdm::locale{});
                });
        return stdm::string{ stdm::ranges::cbegin(v), stdm::ranges::cend(v) };
    }

    [[nodiscard]] stdm::vector<stdm::string> parseString(
        const stdm::string_view str, const stdm::string_view pat) noexcept
    {
        auto v = str
            | stdm::views::split(pat)
            | stdm::views::transform([](const auto& c)
                {
                    return stdm::string_view{ stdm::ranges::cbegin(c),
                        stdm::ranges::cend(c) };
                })
            | stdm::views::filter([](const stdm::string_view str)
                {
                    return !stdm::ranges::empty(str);
                });

        return stdm::vector<stdm::string>{ stdm::ranges::begin(v),
            stdm::ranges::end(v) };
    }

    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
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

    constexpr void ensure(const bool expr,
        const stdm::string_view msg = stdm::string_view{},
        const stdm::source_location& loc = stdm::source_location::current())
        noexcept
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

export namespace eqx::streamingOverloads
{
    template <typename T, typename U>
    stdm::ostream& operator<< (stdm::ostream& os, stdm::pair<T, U> p)
    {
        return os << eqx::toString(p);
    }
}

export namespace eqx::literals
{
    consteval stdm::size_t operator""_size (unsigned long long x) noexcept
    {
        return static_cast<stdm::size_t>(x);
    }

    consteval stdm::size_t operator""_uz (unsigned long long x) noexcept
    {
        return static_cast<stdm::size_t>(x);
    }

    consteval eqx::ssize_t operator""_z (unsigned long long x) noexcept
    {
        return static_cast<eqx::ssize_t>(x);
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

    consteval stdm::int8_t operator""_i8 (unsigned long long x) noexcept
    {
        return static_cast<stdm::int8_t>(x);
    }

    consteval stdm::int16_t operator""_i16 (unsigned long long x) noexcept
    {
        return static_cast<stdm::int16_t>(x);
    }

    consteval stdm::int32_t operator""_i32 (unsigned long long x) noexcept
    {
        return static_cast<stdm::int32_t>(x);
    }

    consteval stdm::int64_t operator""_i64 (unsigned long long x) noexcept
    {
        return static_cast<stdm::int64_t>(x);
    }

    consteval stdm::uint8_t operator""_u8 (unsigned long long x) noexcept
    {
        return static_cast<stdm::uint8_t>(x);
    }

    consteval stdm::uint16_t operator""_u16 (unsigned long long x) noexcept
    {
        return static_cast<stdm::uint16_t>(x);
    }

    consteval stdm::uint32_t operator""_u32 (unsigned long long x) noexcept
    {
        return static_cast<stdm::uint32_t>(x);
    }

    consteval stdm::uint64_t operator""_u64 (unsigned long long x) noexcept
    {
        return static_cast<stdm::uint64_t>(x);
    }

    consteval unsigned long long operator""_KB (unsigned long long x)
        noexcept
    {
        return x * 1024ULL;
    }
}
