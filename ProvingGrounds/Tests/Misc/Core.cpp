module Eqx.Tests.Misc:Core;

import Eqx.Stdm;
import Equinox.Misc;

constexpr auto testStaticCast =
    []<typename T>() consteval noexcept -> bool
    {
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        static_assert(
            std::numeric_limits<std::int_least8_t>::max() <= 100'000
            && std::numeric_limits<std::uint_least8_t>::max() <= 100'000);
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

        constexpr auto aux =
            []<typename To, typename From>
            (From val) consteval noexcept -> bool
        {
            static_assert(std::same_as<
                To, decltype(eqx::staticCast<To, From>(val))>);
            return static_cast<To>(val) == eqx::staticCast<To, From>(val);

        };

        auto test = true;
        for (auto i = std::numeric_limits<std::int_least8_t>::lowest();
            i < std::numeric_limits<std::int_least8_t>::max(); ++i)
        {
            test = test && aux.template operator()<T>(i);
        }
        for (auto i = std::numeric_limits<std::uint_least8_t>::lowest();
            i < std::numeric_limits<std::uint_least8_t>::max(); ++i)
        {
            test = test && aux.template operator()<T>(i);
        }
        return test;
    };

static_assert(testStaticCast.template operator()<long double>());
static_assert(testStaticCast.template operator()<double>());
static_assert(testStaticCast.template operator()<float>());
static_assert(testStaticCast.template operator()<long long>());
static_assert(testStaticCast.template operator()<long>());
static_assert(testStaticCast.template operator()<int>());
static_assert(testStaticCast.template operator()<short>());
static_assert(testStaticCast.template operator()<char>());
static_assert(testStaticCast.template operator()<unsigned long long>());
static_assert(testStaticCast.template operator()<unsigned long>());
static_assert(testStaticCast.template operator()<unsigned int>());
static_assert(testStaticCast.template operator()<unsigned short>());
static_assert(testStaticCast.template operator()<unsigned char>());


static_assert("c"s == eqx::toString('c'));
static_assert("cstring"s == eqx::toString("cstring"));
static_assert("std::string"s == eqx::toString("std::string"s));
static_assert("std::string_view"s == eqx::toString("std::string_view"sv));
static_assert("(v, X)"s == eqx::toString(std::make_pair("v"s, "X"s)));
static_assert("((A, B), (C, D))"s == eqx::toString(std::make_pair(
    std::make_pair("A", "B"), std::make_pair("C", "D"))));

static_assert("{ }"s == eqx::toString(std::vector<char>{}));
static_assert("{ }"s == eqx::toString(std::vector<const char*>{}));
static_assert("{ }"s == eqx::toString(std::vector<std::string_view>{}));
static_assert("{ }"s == eqx::toString(std::vector<std::string>{}));
static_assert("{ c, h, a, r, s }"s
    == eqx::toString(std::vector<char>{ 'c', 'h', 'a', 'r', 's' }));
static_assert("{ Hello }"s
    == eqx::toString(std::vector<const char*>{ "Hello" }));
static_assert("{ Hello }"s
    == eqx::toString(std::vector<std::string_view>{ "Hello"sv }));
static_assert("{ Hello, There }"s == eqx::toString(
    std::vector<std::string_view>{ "Hello"sv, "There"sv }));
static_assert("{ Hello }"s
    == eqx::toString(std::vector<std::string>{ "Hello"s }));
static_assert("{ (1, One), (2, Two), (3, Three), (4, Four) }"s
    == eqx::toString(
        std::vector<std::pair<std::string_view, std::string_view>>{
            { "1"sv, "One"sv },
            { "2"sv, "Two"sv },
            { "3"sv, "Three"sv },
            { "4"sv, "Four"sv } }));

static_assert('a' == eqx::toLower('a'));
static_assert('a' == eqx::toLower('A'));
static_assert('c' == eqx::toLower('c'));
static_assert('c' == eqx::toLower('C'));
static_assert('o' == eqx::toLower('o'));
static_assert('o' == eqx::toLower('O'));
static_assert('z' == eqx::toLower('z'));
static_assert('z' == eqx::toLower('Z'));
static_assert('*' == eqx::toLower('*'));
static_assert('%' == eqx::toLower('%'));
static_assert('!' == eqx::toLower('!'));

static_assert("hello"s == eqx::toLower("HELLO"));
static_assert("hello"s == eqx::toLower("HELLO"sv));
static_assert("hello"s == eqx::toLower("HELLO"s));
static_assert("hello"s == eqx::toLower("HeLlO"sv));
static_assert("alllowercase"s == eqx::toLower("ALLLOWERCASE"sv));
static_assert("alllowercase"s == eqx::toLower("AllLowerCase"sv));
static_assert("alllowercase"s == eqx::toLower("AlllowercasE"sv));
static_assert("alllowercase"s == eqx::toLower("alllowercasE"sv));
static_assert("alllowercase"s == eqx::toLower("Alllowercase"sv));
static_assert("alllowercase"s == eqx::toLower("alllowercase"sv));

static_assert(std::vector<std::string>{ { "Hello Server"s, "Exit"s } }
    == eqx::parseString("Hello Server;Exit;"sv, ";"sv));
static_assert(std::vector<std::string>{ { "Hello"s, "World!"s } }
    == eqx::parseString("Hello World!"sv, " "sv));
static_assert(std::vector<std::string>{ { "Hello"s, "World!"s } }
    == eqx::parseString("Hello<=>World!"sv, "<=>"sv));
static_assert(std::vector<std::string>{ { "Hello"s, "World"s } }
    == eqx::parseString(";Hello;World;"sv, ";"sv));
static_assert(std::vector<std::string>{ { " "s, "Hello"s, "World"s, " "s } }
    == eqx::parseString(" ;Hello;World; "sv, ";"sv));
static_assert(std::vector<std::string>{ { " "s, "Hello"s, "World"s, " "s } }
    == eqx::parseString(" ;Hello;World; ;"sv, ";"sv));
static_assert(std::vector<std::string>{ { " "s, "Hello"s, "World"s, " "s } }
    == eqx::parseString("; ;Hello;World; "sv, ";"sv));
static_assert(std::vector<std::string>{ { " "s, "Hello"s, "World"s, " "s } }
    == eqx::parseString("; ;Hello;World; ;"sv, ";"sv));

constexpr auto testEnsure =
    []() constexpr noexcept -> bool
    {
        eqx::ensure(true);
        eqx::noOp();
        return true;
    };

static_assert(testEnsure());

using namespace eqx::literals;
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
static_assert(std::same_as<decltype(5_size), std::size_t>);
static_assert(std::same_as<decltype(5_uz), std::size_t>);
static_assert(std::same_as<decltype(5_z), std::make_signed_t<std::size_t>>);
static_assert(std::same_as<decltype(5_short), short>);
static_assert(std::same_as<decltype(5_ushort), unsigned short>);
static_assert(std::same_as<decltype(5_i8), std::int8_t>);
static_assert(std::same_as<decltype(5_i16), std::int16_t>);
static_assert(std::same_as<decltype(5_i32), std::int32_t>);
static_assert(std::same_as<decltype(5_i64), std::int64_t>);
static_assert(std::same_as<decltype(5_u8), std::uint8_t>);
static_assert(std::same_as<decltype(5_u16), std::uint16_t>);
static_assert(std::same_as<decltype(5_u32), std::uint32_t>);
static_assert(std::same_as<decltype(5_u64), std::uint64_t>);
static_assert(5_KB == 5120ULL);
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
