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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_MISCTESTERIMPL_IPP
#define PROVINGGROUNDS_TESTS_DETAILS_MISCTESTERIMPL_IPP

#include "MiscTesterDecl.hpp"

inline void MiscTester::test()
{
    std::cout << "Testing Misc..." << std::endl;
    testToString();
    testToLower();
    testParseString();
    testPairPrint();
    testAlloc();
    UnitTester::printStatus();
    UnitTester::clear();
}

inline void MiscTester::testToString()
{
    using namespace std::literals;

    UnitTester::test(eqx::toString("cstring"), "cstring"s);
    UnitTester::test(eqx::toString("stdstring"s), "stdstring"s);
    UnitTester::test(eqx::toString("string_view"sv), "string_view"sv);
    UnitTester::test(eqx::toString(5), "5"s);
    UnitTester::test(eqx::toString(5L), "5"s);
    UnitTester::test(eqx::toString(5LL), "5"s);
    UnitTester::test(eqx::toString(5U), "5"s);
    UnitTester::test(eqx::toString(5UL), "5"s);
    UnitTester::test(eqx::toString(5ULL), "5"s);
    UnitTester::test(eqx::toString(5.1234567F), "5.123456"s);
    UnitTester::test(eqx::toString(5.1234567), "5.123457"s);
    UnitTester::test(eqx::toString(5.1234567L), "5.123457"s);

    UnitTester::test(eqx::toString(std::make_pair(5, 5)), "(5, 5)"s);
    UnitTester::test(eqx::toString(std::make_pair("Yes", 5)), "(Yes, 5)"s);
    UnitTester::test(
        eqx::toString(std::make_pair(5, 5.123)), "(5, 5.123000)"s);
    UnitTester::test(
        eqx::toString(std::make_pair("Hello"sv, 6UL)), "(Hello, 6)"s);
    UnitTester::test(
        eqx::toString(std::make_pair("v"s, "X"sv)), "(v, X)"s);

    auto p1 = std::make_pair("A", "B");
    auto p2 = std::make_pair("C", "D");
    UnitTester::test(
        eqx::toString(std::make_pair(p1, p2)), "((A, B), (C, D))"s);

    auto vec = std::vector<int>({ 1, 2, 3 });
    UnitTester::test(eqx::toString(vec), "{ 1, 2, 3 }"s);

    auto vecWPairs = std::vector<std::pair<int, std::string_view>>({
        { 1, "One" },
        { 2, "Two" },
        { 3, "Three" },
        { 4, "Four" } });

    UnitTester::test(eqx::toString(vecWPairs),
        "{ (1, One), (2, Two), (3, Three), (4, Four) }"s);

    UnitTester::test(eqx::toString(std::vector<int>()),
        "{ }"s);
}

inline void MiscTester::testToLower() noexcept
{
    using namespace std::literals;

    constexpr auto expected = "alllowercase"sv;
    UnitTester::test(eqx::toLower("ALLLOWERCASE"sv), expected);
    UnitTester::test(eqx::toLower("AllLowerCase"sv), expected);
    UnitTester::test(eqx::toLower("AlllowercasE"sv), expected);
    UnitTester::test(eqx::toLower("alllowercasE"sv), expected);
    UnitTester::test(eqx::toLower("Alllowercase"sv), expected);
    UnitTester::test(eqx::toLower("alllowercase"sv), expected);
}

inline void MiscTester::testParseString() noexcept
{
    using namespace std::literals;

    auto expected = std::vector<std::string>({ "Hello Server"s, "Exit"s });
    auto produced = eqx::parseString("Hello Server;Exit;"sv, ";"sv);
    UnitTester::test(produced, expected);

    expected = std::vector<std::string>({ "Hello"s, "World!"s });
    produced = eqx::parseString("Hello World!"sv, " "sv);
    UnitTester::test(produced, expected);
}

inline void MiscTester::testPairPrint()
{
    using namespace eqx::pairPrint;
    using namespace std::literals;

    auto ss = std::stringstream();
    auto temp = std::string("");

    ss << std::make_pair(1, 1) << "\n";
    std::getline(ss, temp);
    UnitTester::test(temp, "(1, 1)"s);

    ss << std::make_pair("Yes", "No") << "\n";
    std::getline(ss, temp);
    UnitTester::test(temp, "(Yes, No)"s);

    ss << std::make_pair(1.5, "Double") << "\n";
    std::getline(ss, temp);
    UnitTester::test(temp, "(1.500000, Double)"s);
}

inline void MiscTester::testAlloc() noexcept
{
    using namespace std::literals;

    auto res = eqx::newAlloc<std::string>("Hello");

    UnitTester::test(res, nullptr, UnitTesterFunctions::NE);
    UnitTester::test(*res, "Hello"s);

    eqx::deleteDealloc(res);
}

constexpr void MiscTester::testLiterals() noexcept
{
    using namespace eqx::literals;

    static_assert(std::same_as<decltype(1_size), std::size_t>);
    static_assert(std::same_as<decltype(1_short), short>);
    static_assert(std::same_as<decltype(1_ushort), unsigned short>);
    static_assert(std::same_as<decltype(1_i8), std::int8_t>);
    static_assert(std::same_as<decltype(1_i16), std::int16_t>);
    static_assert(std::same_as<decltype(1_i32), std::int32_t>);
    static_assert(std::same_as<decltype(1_i64), std::int64_t>);
    static_assert(std::same_as<decltype(1_u8), std::uint8_t>);
    static_assert(std::same_as<decltype(1_u16), std::uint16_t>);
    static_assert(std::same_as<decltype(1_u32), std::uint32_t>);
    static_assert(std::same_as<decltype(1_u64), std::uint64_t>);
}

constexpr void MiscTester::testConstexprAssert() noexcept
{
    constexpr auto value = std::invoke([]()
        {
            eqx::runtimeAssert(true, "Some Msg");
            return 1;
        });
    static_assert(value == 1);
}

#endif // PROVINGGROUNDS_TESTS_DETAILS_MISCTESTERIMPL_IPP
