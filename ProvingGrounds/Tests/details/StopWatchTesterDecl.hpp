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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_STOPWATCHTESTERDECL_HPP
#define PROVINGGROUNDS_TESTS_DETAILS_STOPWATCHTESTERDECL_HPP

#include "Dependencies.hpp"

class StopWatchTester
{
public:
    StopWatchTester() = delete;
    StopWatchTester(const StopWatchTester&) = delete;
    StopWatchTester(StopWatchTester&&) = delete;
    StopWatchTester& operator= (const StopWatchTester&) = delete;
    StopWatchTester& operator= (StopWatchTester&&) = delete;
    ~StopWatchTester() = delete;

    static inline void test();

private:
    static inline void testGetTime();
    static inline void testReadTime();
    static inline void testGetSeconds();
    static inline void testReadSeconds();
    static inline void testToString();
    static inline void wasteTime(std::chrono::microseconds ms);
};

#endif // PROVINGGROUNDS_TESTS_DETAILS_STOPWATCHTESTERDECL_HPP
