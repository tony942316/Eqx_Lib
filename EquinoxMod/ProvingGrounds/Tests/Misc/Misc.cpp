export module Eqx.Tests.Misc;

import :Core;

import Eqx.Stdm;
import Equinox.Misc;
import Eqx.UnitTester;

namespace test::misc
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    constinit inline auto tester = UnitTester{};
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

    export inline void all() noexcept;
    inline void toString() noexcept;
    inline void println() noexcept;
    inline void ensure() noexcept;
    inline void stream() noexcept;
}

// Implementations

namespace test::misc
{
    export inline void all() noexcept
    {
        stdm::cout << "Testing Misc...\n";
        toString();
        println();
        ensure();
        stream();
        tester.print();
    }

    inline void toString() noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto expected_actual =
            stdm::vector<stdm::pair<stdm::string, stdm::string>>{
                { "5"s, eqx::toString(5) },
                { "5"s, eqx::toString(5L) },
                { "5"s, eqx::toString(5LL) },
                { "5"s, eqx::toString(5U) },
                { "5"s, eqx::toString(5UL) },
                { "5"s, eqx::toString(5ULL) },
                { "5.123456"s, eqx::toString(5.1234567F) },
                { "5.123457"s, eqx::toString(5.1234567) },
                { "5.123457"s, eqx::toString(5.1234567L) },
                { "(5, 5)"s, eqx::toString(stdm::make_pair(5, 5)) },
                { "(Yes, 5)"s, eqx::toString(stdm::make_pair("Yes", 5)) },
                { "(5, 5.123000)"s, eqx::toString(stdm::make_pair(5, 5.123)) },
                { "(Hello, 6)"s,
                    eqx::toString(stdm::make_pair("Hello"sv, 6UL)) },
                { "{ 1, 2, 3 }"s, eqx::toString(stdm::vector<int>{ 1, 2, 3 }) },
                { "{ (1, One), (2, Two), (3, Three), (4, Four) }"s,
                    eqx::toString(
                        stdm::vector<stdm::pair<int, stdm::string_view>>{
                            { 1, "One" },
                            { 2, "Two" },
                            { 3, "Three" },
                            { 4, "Four" }
                        }) },
                { "{ }", eqx::toString(stdm::vector<int>{}) }
            };

        tester.addTests(expected_actual);

        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    inline void println() noexcept
    {
        auto ss1 = stdm::stringstream{};
        eqx::println("Hello", ss1);

        auto ss2 = stdm::stringstream{};
        eqx::println("Welcome To The Test!", ss2);
        eqx::println("How Are You Today?", ss2);

        auto expected_actual =
            stdm::vector<stdm::pair<stdm::string, stdm::string>>{
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

    inline void stream() noexcept
    {
        using namespace eqx::stream;

        auto ss1 = stdm::stringstream{};
        ss1 << stdm::vector<int>{ 1, 2, 3 };

        auto ss2 = stdm::stringstream{};
        ss2 << stdm::pair<int, int>{ 1, 2 };

        auto ss3 = stdm::stringstream{};
        ss3 << stdm::vector<stdm::pair<int, int>>{ { 1, 2 }, { 3, 4 } };

        auto expected_actual =
            stdm::vector<stdm::pair<stdm::string, stdm::string>>{
                { "{ 1, 2, 3 }"s, ss1.str() },
                { "(1, 2)"s, ss2.str() },
                { "{ (1, 2), (3, 4) }"s, ss3.str() }
            };
        tester.addTests(expected_actual);
    }
}
