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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_UTILITYMACROSTESTERIMPL_IPP
#define PROVINGGROUNDS_TESTS_DETAILS_UTILITYMACROSTESTERIMPL_IPP

#include "UtilityMacrosTesterDecl.hpp"

inline void UtilityMacrosTester::test()
{
    std::cout << "Testing UtilityMacros..." << std::endl;
    UnitTester::printStatus();
    UnitTester::clear();
}

constexpr void UtilityMacrosTester::testCountArgs() noexcept
{
    constexpr auto actual = std::array<unsigned int, 3ULL>({
            EQX_COUNT_ARGS(1), EQX_COUNT_ARGS(1, 2),
            EQX_COUNT_ARGS(1, 2, 3, 4, 5) });
    constexpr auto expected = std::array<unsigned int, 3ULL>({ 1U, 2U, 5U });
    static_assert(std::ranges::equal(actual, expected));
}

constexpr void UtilityMacrosTester::testStringArgs() noexcept
{
    constexpr auto actual = std::array<std::string_view, 5ULL>({
        EQX_STRING_ARGS(1, 2, 3, 4, 5) });
    constexpr auto expected = std::array<std::string_view, 5ULL>({
        "1", "2", "3", "4", "5" });
    static_assert(std::ranges::equal(actual, expected));
}

constexpr void UtilityMacrosTester::testForEach() noexcept
{
    constexpr auto someFunc = [](int val) constexpr
    {
        return val + 1;
    };
    static_assert(EQX_FOR_EACH(someFunc, 1) == 2);
}

constexpr void UtilityMacrosTester::testForEachList() noexcept
{
    constexpr auto someFunc = [](int val) constexpr
    {
        return val + 1;
    };
    constexpr auto actual = std::array<int, 3>({
        EQX_FOR_EACH_LIST(someFunc, 0, 1, 2) });
    constexpr auto expected = std::array<int, 3>({
        1, 2, 3 });
    static_assert(std::ranges::equal(actual, expected));
}

#endif // PROVINGGROUNDS_TESTS_DETAILS_UTILITYMACROSTESTERIMPL_IPP
