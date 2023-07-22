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

#ifndef PROVINGGROUNDS_UNITTESTER_DETAILS_UNITTESTERDECL_HPP
#define PROVINGGROUNDS_UNITTESTER_DETAILS_UNITTESTERDECL_HPP

#include "../../../include/EquinoxCppStd.hpp"

template <typename T>
constexpr T abs(T val) noexcept
{
    return val < 0 ? val * -1 : val;
}

struct equalTo
{
    template <typename T, typename U>
        requires std::disjunction_v<
            std::is_floating_point<T>,
            std::is_floating_point<U>>
    constexpr bool operator() (const T& l, const U& r) const
    {
        return abs<decltype(l - r)>(l - r) < 0.001;
    }

    template <typename T, typename U, typename V, typename W>
    constexpr bool operator() (const std::pair<T, U>& p1,
        const std::pair<V, W>& p2) const
    {
        return equalTo()(p1.first, p2.first) && equalTo()(p1.second, p2.second);
    }

    template <typename T, typename U>
    constexpr bool operator() (const T& l, const U& r) const
    {
        return l == r;
    }
};

namespace UnitTesterFunctions
{
    inline constexpr auto E = std::make_pair(equalTo(), " == ");
    inline constexpr auto NE = std::make_pair(std::not_equal_to(), " != ");
    inline constexpr auto GT = std::make_pair(std::greater(), " > ");
    inline constexpr auto LT = std::make_pair(std::less(), " < ");
    inline constexpr auto GTE = std::make_pair(std::greater_equal(), " >= ");
    inline constexpr auto LTE = std::make_pair(std::less_equal(), " <= ");
}

class UnitTester
{
public:
    UnitTester() = delete;
    UnitTester(const UnitTester&) = delete;
    UnitTester(UnitTester&&) = delete;
    UnitTester& operator= (const UnitTester&) = delete;
    UnitTester& operator= (UnitTester&&) = delete;
    ~UnitTester() = delete;

    static inline void init();

    template <typename T, typename U, typename Cmp =
        decltype(UnitTesterFunctions::E)>
    static void test(const T& val1, const U& val2,
        const Cmp& func = UnitTesterFunctions::E,
        std::string_view info = "",
        const std::source_location& loc = std::source_location::current());

    static inline bool passing() noexcept;
    static inline void printStatus(std::size_t num = 3);
    static inline void clear() noexcept;

private:
    template <typename T, typename U, typename Cmp>
    static std::string makeErrorStr(const T& val1, const U& val2,
        std::string_view info, const Cmp& func,
        const std::source_location& loc);

    template <typename T>
        requires requires(const T& x) { std::stringstream() << x; }
    static std::string toString(const T& x);

    template <typename T>
    static std::string toString(const std::vector<T>& v);

    template <typename T, std::size_t S>
    static std::string toString(const std::array<T, S>& a);

    template <typename T, typename U>
    static std::string toString(const std::pair<T, U>& p);

    constinit static inline auto s_FailedTests =
        static_cast<std::vector<std::string>*>(nullptr);

    constinit static inline auto s_IsInit = false;
};

#endif // PROVINGGROUNDS_UNITTESTER_DETAILS_UNITTESTERDECL_HPP
