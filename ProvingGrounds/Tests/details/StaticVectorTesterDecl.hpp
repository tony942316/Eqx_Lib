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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_STATICVECTORTESTERDECL_HPP
#define PROVINGGROUNDS_TESTS_DETAILS_STATICVECTORTESTERDECL_HPP

#include "Dependencies.hpp"

class StaticVectorTester
{
public:
    StaticVectorTester() = delete;
    StaticVectorTester(const StaticVectorTester&) = delete;
    StaticVectorTester(StaticVectorTester&&) = delete;
    StaticVectorTester& operator= (const StaticVectorTester&) = delete;
    StaticVectorTester& operator= (StaticVectorTester&&) = delete;
    ~StaticVectorTester() = delete;

    static inline void test();

private:
    static constexpr void testConstruction() noexcept;
    static constexpr void testBraceOp() noexcept;
    static constexpr void testFrontBack() noexcept;
    static constexpr void testIter() noexcept;
    static constexpr void testEmptyClearCapacity() noexcept;
    static constexpr void testPushEmplaceBack() noexcept;
    static constexpr void testPopResize() noexcept;

    class SomeType
    {
    public:
        explicit constexpr SomeType() noexcept
            :
            val(1)
        {
        }

        explicit constexpr SomeType(int x) noexcept
            :
            val(x)
        {
        }

        constexpr SomeType(const SomeType& other) noexcept
            :
            val(other.val)
        {
        }

        constexpr SomeType& operator= (const SomeType& other) noexcept
        {
            val = other.val;
            return *this;
        }

        constexpr ~SomeType() noexcept
        {
            val = 0;
        }

        SomeType(SomeType&&) = default;
        SomeType& operator= (SomeType&&) = default;

        constexpr int get() const noexcept
        {
            return val;
        }

    private:
        int val;
    };
};

#endif // PROVINGGROUNDS_TESTS_DETAILS_STATICVECTORTESTERDECL_HPP
