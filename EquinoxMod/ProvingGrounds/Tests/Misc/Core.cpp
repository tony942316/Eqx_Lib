module Eqx.Tests.Misc:Core;

import Eqx.Stdm;
import Equinox.Misc;

constexpr auto testStaticCast =
    []<typename T>() consteval noexcept -> bool
    {
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        static_assert(
            stdm::numeric_limits<stdm::int_least8_t>::max() <= 100'000
            && stdm::numeric_limits<stdm::uint_least8_t>::max() <= 100'000);
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

        constexpr auto aux =
            []<typename To, typename From>
            (From val) consteval noexcept -> bool
        {
            static_assert(stdm::same_as<
                To, decltype(eqx::staticCast<To, From>(val))>);
            return static_cast<To>(val) == eqx::staticCast<To, From>(val);

        };

        auto test = true;
        for (auto i = stdm::numeric_limits<stdm::int_least8_t>::lowest();
            i < stdm::numeric_limits<stdm::int_least8_t>::max(); ++i)
        {
            test = test && aux.template operator()<T>(i);
        }
        for (auto i = stdm::numeric_limits<stdm::uint_least8_t>::lowest();
            i < stdm::numeric_limits<stdm::uint_least8_t>::max(); ++i)
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
static_assert("(v, X)"s == eqx::toString(stdm::make_pair("v"s, "X"s)));
static_assert("((A, B), (C, D))"s == eqx::toString(stdm::make_pair(
    stdm::make_pair("A", "B"), stdm::make_pair("C", "D"))));

static_assert("{ }"s == eqx::toString(stdm::vector<char>{}));
static_assert("{ }"s == eqx::toString(stdm::vector<const char*>{}));
static_assert("{ }"s == eqx::toString(stdm::vector<stdm::string_view>{}));
static_assert("{ }"s == eqx::toString(stdm::vector<stdm::string>{}));
static_assert("{ c, h, a, r, s }"s
    == eqx::toString(stdm::vector<char>{ 'c', 'h', 'a', 'r', 's' }));
static_assert("{ Hello }"s
    == eqx::toString(stdm::vector<const char*>{ "Hello" }));
static_assert("{ Hello }"s
    == eqx::toString(stdm::vector<stdm::string_view>{ "Hello"sv }));
static_assert("{ Hello, There }"s == eqx::toString(
    stdm::vector<stdm::string_view>{ "Hello"sv, "There"sv }));
static_assert("{ Hello }"s
    == eqx::toString(stdm::vector<stdm::string>{ "Hello"s }));
static_assert("{ (1, One), (2, Two), (3, Three), (4, Four) }"s
    == eqx::toString(
        stdm::vector<stdm::pair<stdm::string_view, stdm::string_view>>{
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

static_assert(stdm::vector<stdm::string>{ { "Hello Server"s, "Exit"s } }
    == eqx::parseString("Hello Server;Exit;"sv, ";"sv));
static_assert(stdm::vector<stdm::string>{ { "Hello"s, "World!"s } }
    == eqx::parseString("Hello World!"sv, " "sv));
static_assert(stdm::vector<stdm::string>{ { "Hello"s, "World!"s } }
    == eqx::parseString("Hello<=>World!"sv, "<=>"sv));
static_assert(stdm::vector<stdm::string>{ { "Hello"s, "World"s } }
    == eqx::parseString(";Hello;World;"sv, ";"sv));
static_assert(stdm::vector<stdm::string>{ { " "s, "Hello"s, "World"s, " "s } }
    == eqx::parseString(" ;Hello;World; "sv, ";"sv));
static_assert(stdm::vector<stdm::string>{ { " "s, "Hello"s, "World"s, " "s } }
    == eqx::parseString(" ;Hello;World; ;"sv, ";"sv));
static_assert(stdm::vector<stdm::string>{ { " "s, "Hello"s, "World"s, " "s } }
    == eqx::parseString("; ;Hello;World; "sv, ";"sv));
static_assert(stdm::vector<stdm::string>{ { " "s, "Hello"s, "World"s, " "s } }
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
static_assert(stdm::same_as<decltype(5_size), stdm::size_t>);
static_assert(stdm::same_as<decltype(5_uz), stdm::size_t>);
static_assert(stdm::same_as<decltype(5_z), stdm::make_signed_t<stdm::size_t>>);
static_assert(stdm::same_as<decltype(5_short), short>);
static_assert(stdm::same_as<decltype(5_ushort), unsigned short>);
static_assert(stdm::same_as<decltype(5_i8), stdm::int8_t>);
static_assert(stdm::same_as<decltype(5_i16), stdm::int16_t>);
static_assert(stdm::same_as<decltype(5_i32), stdm::int32_t>);
static_assert(stdm::same_as<decltype(5_i64), stdm::int64_t>);
static_assert(stdm::same_as<decltype(5_u8), stdm::uint8_t>);
static_assert(stdm::same_as<decltype(5_u16), stdm::uint16_t>);
static_assert(stdm::same_as<decltype(5_u32), stdm::uint32_t>);
static_assert(stdm::same_as<decltype(5_u64), stdm::uint64_t>);
static_assert(5_KB == 5120ULL);
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
