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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_SUPERENUMTESTERDECL_HPP
#define PROVINGGROUNDS_TESTS_DETAILS_SUPERENUMTESTERDECL_HPP

#include "Dependencies.hpp"

class SuperEnumTester
{
public:
    SuperEnumTester() = delete;
    SuperEnumTester(const SuperEnumTester&) = delete;
    SuperEnumTester(SuperEnumTester&&) = delete;
    SuperEnumTester& operator= (const SuperEnumTester&) = delete;
    SuperEnumTester& operator= (SuperEnumTester&&) = delete;
    ~SuperEnumTester() = delete;

    static inline void test();

private:
    class SuperEnumShell
    {
    public:
        EQX_SUPER_ENUM(Pub3,
            v1,
            v2,
            v3)
            EQX_SUPER_ENUM(Pub5, v1, v2, v3, v4, v5)
            EQX_SUPER_ENUM(Pub7, v1, v2, v3, v4, v5,
                v6, v7)
    };

    static inline void testStreaming();
    static constexpr void testEnumCollection() noexcept;
    static constexpr void testGetEnums() noexcept;
    static constexpr void testGetString() noexcept;
};

#endif // PROVINGGROUNDS_TESTS_DETAILS_SUPERENUMTESTERDECL_HPP
