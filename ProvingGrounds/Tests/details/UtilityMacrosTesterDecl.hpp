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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_UTILITYMACROSTESTERDECL_HPP
#define PROVINGGROUNDS_TESTS_DETAILS_UTILITYMACROSTESTERDECL_HPP

#include "../Dependencies.hpp"

class UtilityMacrosTester
{
public:
    UtilityMacrosTester() = delete;
    UtilityMacrosTester(const UtilityMacrosTester&) = delete;
    UtilityMacrosTester(UtilityMacrosTester&&) = delete;
    UtilityMacrosTester& operator= (const UtilityMacrosTester&) = delete;
    UtilityMacrosTester& operator= (UtilityMacrosTester&&) = delete;
    ~UtilityMacrosTester() = delete;

    static inline void test();

private:
    static constexpr void testCountArgs() noexcept;
    static constexpr void testStringArgs() noexcept;
    static constexpr void testForEach() noexcept;
    static constexpr void testForEachList() noexcept;
};

#endif // PROVINGGROUNDS_TESTS_DETAILS_UTILITYMACROSTESTERDECL_HPP
