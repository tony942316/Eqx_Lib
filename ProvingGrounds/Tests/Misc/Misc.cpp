export module Eqx.Tests.Misc;

#include <Eqx/std.hpp>

import :Core;

import Eqx.Lib.Misc;
import Eqx.UnitTester;

using namespace std::literals;

namespace test::misc
{
    export inline UnitTester all() noexcept;
    inline void toString(UnitTester& tester) noexcept;
    inline void println(UnitTester& tester) noexcept;
    inline void ensure() noexcept;
    inline void stream(UnitTester& tester) noexcept;
}

// Implementations

namespace test::misc
{
    export inline UnitTester all() noexcept
    {
        auto tester = UnitTester{};
        toString(tester);
        println(tester);
        ensure();
        stream(tester);
        return tester;
    }

    inline void toString(UnitTester& tester) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto expected_actual =
            std::vector<std::pair<std::string, std::string>>{
                { "5"s, eqx::toString(5) },
                { "5"s, eqx::toString(5L) },
                { "5"s, eqx::toString(5LL) },
                { "5"s, eqx::toString(5U) },
                { "5"s, eqx::toString(5UL) },
                { "5"s, eqx::toString(5ULL) },
                { "5.123456"s, eqx::toString(5.1234567F) },
                { "5.123457"s, eqx::toString(5.1234567) },
                { "5.123457"s, eqx::toString(5.1234567L) },
                { "(5, 5)"s, eqx::toString(std::make_pair(5, 5)) },
                { "(Yes, 5)"s, eqx::toString(std::make_pair("Yes", 5)) },
                { "(5, 5.123000)"s, eqx::toString(std::make_pair(5, 5.123)) },
                { "(Hello, 6)"s,
                    eqx::toString(std::make_pair("Hello"sv, 6UL)) },
                { "{ 1, 2, 3 }"s, eqx::toString(std::vector<int>{ 1, 2, 3 }) },
                { "{ (1, One), (2, Two), (3, Three), (4, Four) }"s,
                    eqx::toString(
                        std::vector<std::pair<int, std::string_view>>{
                            { 1, "One" },
                            { 2, "Two" },
                            { 3, "Three" },
                            { 4, "Four" }
                        }) },
                { "{ }", eqx::toString(std::vector<int>{}) }
            };

        tester.addTests(expected_actual);

        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    inline void println(UnitTester& tester) noexcept
    {
        auto ss1 = std::stringstream{};
        eqx::println("Hello", ss1);

        auto ss2 = std::stringstream{};
        eqx::println("Welcome To The Test!", ss2);
        eqx::println("How Are You Today?", ss2);

        auto expected_actual =
            std::vector<std::pair<std::string, std::string>>{
                { "Hello\n"s, ss1.str() },
                { "Welcome To The Test!\nHow Are You Today?\n"s, ss2.str() }
            };
        tester.addTests(expected_actual);
    }

    inline void ensure() noexcept
    {
        eqx::ensure(true);
        eqx::noOp();
    }

    inline void stream(UnitTester& tester) noexcept
    {
        using namespace eqx::stream;

        auto ss1 = std::stringstream{};
        ss1 << std::vector<int>{ 1, 2, 3 };

        auto ss2 = std::stringstream{};
        ss2 << std::pair<int, int>{ 1, 2 };

        auto ss3 = std::stringstream{};
        ss3 << std::vector<std::pair<int, int>>{ { 1, 2 }, { 3, 4 } };

        auto expected_actual =
            std::vector<std::pair<std::string, std::string>>{
                { "{ 1, 2, 3 }"s, ss1.str() },
                { "(1, 2)"s, ss2.str() },
                { "{ (1, 2), (3, 4) }"s, ss3.str() }
            };
        tester.addTests(expected_actual);
    }
}
