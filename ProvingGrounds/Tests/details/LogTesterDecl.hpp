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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_LOGTESTERDECL_HPP
#define PROVINGGROUNDS_TESTS_DETAILS_LOGTESTERDECL_HPP

#include "Dependencies.hpp"

class LogTester
{
public:
    LogTester() = delete;
    LogTester(const LogTester&) = delete;
    LogTester(LogTester&&) = delete;
    LogTester& operator= (const LogTester&) = delete;
    LogTester& operator= (LogTester&&) = delete;
    ~LogTester() = delete;

    static void inline test();

private:
    static inline void testLog();
    static inline void testSetLevel();
    static inline void testSetOutputStream();
    static inline void testSetOutputFile();
    static inline void testClear();
    static inline void testGetFormattedString();
    static constexpr void testGetLoggableLevels() noexcept;
};

#endif // PROVINGGROUNDS_TESTS_DETAILS_LOGTESTERDECL_HPP
