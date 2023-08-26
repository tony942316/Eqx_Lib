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

#ifndef PROVINGGROUNDS_UNITTESTER_DETAILS_UNITTESTERIMPL_IPP
#define PROVINGGROUNDS_UNITTESTER_DETAILS_UNITTESTERIMPL_IPP

#include "UnitTesterDecl.hpp"

inline void UnitTester::init()
{
    if (!s_IsInit)
    {
        static auto storage = std::vector<std::string>();
        s_FailedTests = &storage;
        s_IsInit = true;
    }
}

template <typename T, typename U, typename Cmp>
void UnitTester::test(const T& val1, const U& val2,
    const Cmp& func, std::string_view info, const std::source_location& loc)
{
    if (!func.first(val1, val2))
    {
        s_FailedTests->emplace_back(makeErrorStr(val1, val2, info, func, loc));
    }
}

inline bool UnitTester::passing() noexcept
{
    return s_FailedTests->empty();
}

inline void UnitTester::printStatus(std::size_t num)
{
    if (passing())
    {
        std::cout << "Pass!" << std::endl;
    }
    else
    {
        std::cout << "Fail!\n" << std::endl;

        auto printLimit =
            std::ranges::min(num, std::ranges::size(*s_FailedTests));

        auto v = std::views::iota(0) |
            std::views::take(printLimit) |
            std::views::transform([](int val)
            {
                return (std::stringstream() << val + 1 << ")\n" <<
                    s_FailedTests->at(static_cast<std::size_t>(val)) <<
                    "\n").str();
            });

        std::ranges::for_each(v, [](const auto& val)
            {
                std::cout << val << std::endl;
            });

        if (printLimit < std::ranges::size(*s_FailedTests))
        {
            std::cout << printLimit + 1 << ")...\n" << std::endl;
        }
    }
}

inline void UnitTester::clear() noexcept
{
    s_FailedTests->clear();
}

template <typename T>
    requires requires(const T& x) { std::stringstream() << x; }
std::string UnitTester::toString(const T& x)
{
    return (std::stringstream() <<
        std::setprecision(100) << std::boolalpha << x).str();
}

template <typename T>
std::string UnitTester::toString(const std::vector<T>& v)
{
    auto ss = std::stringstream();
    ss << "{ ";
    std::ranges::for_each(v, [&ss](const auto& val)
        {
            ss << toString(val) << ", ";
        });
    ss.unget();
    ss.unget();
    ss << " }";
    return ss.str();
}

template <typename T, std::size_t S>
std::string UnitTester::toString(const std::array<T, S>& a)
{
    return toString(std::vector<T>(
        std::ranges::cbegin(a), std::ranges::cend(a)));
}

template <typename T, typename U>
std::string UnitTester::toString(const std::pair<T, U>& p)
{
    return (std::stringstream() << "(" << toString(p.first) << ", " <<
        toString(p.second) << ")").str();
}

template <typename T, typename U, typename Cmp>
std::string UnitTester::makeErrorStr(const T& val1, const U& val2,
    std::string_view info, const Cmp& func,
    const std::source_location& loc)
{
    auto ss = std::stringstream();
    auto fileName = std::string(loc.file_name());

    fileName.erase(0ULL, fileName.rfind('/') + 1);
    ss << "Evaluated To False: \n" <<
        toString(val1) << '\n' <<
        func.second << '\n' <<
        toString(val2) << '\n' <<
        "Location: " << fileName << "(" << loc.function_name() << "," <<
        loc.line() << ")";
    if (!std::ranges::empty(info))
    {
        ss << "\nInfo: " << info;
    }

    return ss.str();
}

#endif // PROVINGGROUNDS_UNITTESTER_DETAILS_UNITTESTERIMPL_IPP
