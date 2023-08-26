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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_MATHEMATICSTESTERDECL_HPP
#define PROVINGGROUNDS_TESTS_DETAILS_MATHEMATICSTESTERDECL_HPP

#include "Dependencies.hpp"

class MathematicsTester
{
public:
    MathematicsTester() = delete;
    MathematicsTester(const MathematicsTester&) = delete;
    MathematicsTester(MathematicsTester&&) = delete;
    MathematicsTester& operator= (const MathematicsTester&) = delete;
    MathematicsTester& operator= (MathematicsTester&&) = delete;
    ~MathematicsTester() = delete;

    static inline void test();

private:
    static inline void testArccos();
    static inline void testArcsin();
    static constexpr void testEquals() noexcept;
    static constexpr void testAbs() noexcept;
    static constexpr void testDistance() noexcept;
    static constexpr void testGetSign() noexcept;
    static constexpr void testIsPositive() noexcept;
    static constexpr void testIsNegative() noexcept;
    static constexpr void testWillOverflow() noexcept;
    static constexpr void testDegreesToRadians() noexcept;
    static constexpr void testRadiansToDegrees() noexcept;
};

#endif // PROVINGGROUNDS_TESTS_DETAILS_MATHEMATICSTESTERDECL_HPP
