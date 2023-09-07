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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_UNIQUERESOURCETESTERDECL_HPP
#define PROVINGGROUNDS_TESTS_DETAILS_UNIQUERESOURCETESTERDECL_HPP

#include "Dependencies.hpp"

class UniqueResourceTester
{
public:
    UniqueResourceTester() = delete;
    UniqueResourceTester(const UniqueResourceTester&) = delete;
    UniqueResourceTester(UniqueResourceTester&&) = delete;
    UniqueResourceTester& operator= (const UniqueResourceTester&) = delete;
    UniqueResourceTester& operator= (UniqueResourceTester&&) = delete;
    ~UniqueResourceTester() = delete;

    static inline void test();

private:
    static constexpr int newResource(int x) noexcept;
    static constexpr void deleteResource(int& x) noexcept;

    using SomeResource = eqx::UniqueResource<int, decltype(&deleteResource)>;

    static inline void testUniquePointer() noexcept;
    static constexpr void testConstruction() noexcept;
    static constexpr void testFreeSwap() noexcept;
};

#endif // PROVINGGROUNDS_TESTS_DETAILS_UNIQUERESOURCETESTERDECL_HPP
