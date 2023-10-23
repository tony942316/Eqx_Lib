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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_UNIQUERESOURCETESTERIMPL_IPP
#define PROVINGGROUNDS_TESTS_DETAILS_UNIQUERESOURCETESTERIMPL_IPP

#include "UniqueResourceTesterDecl.hpp"

inline void UniqueResourceTester::test()
{
    std::cout << "Testing Unique Resource..." << std::endl;
    testUniquePointer();
    UnitTester::printStatus();
    UnitTester::clear();
}

constexpr int UniqueResourceTester::newResource(int x) noexcept
{
    return x;
}

constexpr void UniqueResourceTester::deleteResource(int& x) noexcept
{
    x = 0;
}

inline void UniqueResourceTester::testUniquePointer() noexcept
{
    using namespace std::literals;

    auto res1 = eqx::UniquePointer<std::string>();
    auto res2 = eqx::UniquePointer<std::string>("Hello");

    UnitTester::test(res1.get(), nullptr);
    UnitTester::test(res2.get(), nullptr, UnitTesterFunctions::NE);
    UnitTester::test(*res2.get(), "Hello"s);
    UnitTester::test(*res2, "Hello"s);

    res2.free();

    UnitTester::test(res2.get(), nullptr);
}

constexpr void UniqueResourceTester::testConstruction() noexcept
{
    constexpr auto res1 = SomeResource();
    constexpr auto res2 =
        SomeResource(deleteResource, newResource, 1);

    static_assert(res1.get() == 0);
    static_assert(res2.get() == 1);
    static_assert(*res1 == 0);
    static_assert(*res2 == 1);

    constexpr auto moveConstruct = []()
    {
        auto res1 = SomeResource(deleteResource, newResource, 2);
        auto res2 = std::move(res1);
        return res1.get() == 0 && res2.get() == 2 &&
            *res1 == 0 && *res2 == 2;
    };

    static_assert(moveConstruct());

    constexpr auto moveAssign = []()
    {
        auto res1 = SomeResource(deleteResource, newResource, 3);
        auto res2 = SomeResource();
        res2 = std::move(res1);
        return res1.get() == 0 && res2.get() == 3 &&
            *res1 == 0 && *res2 == 3;
    };

    static_assert(moveAssign());

    constexpr auto uniquePointer = eqx::UniquePointer<std::string>();

    static_assert(uniquePointer.get() == nullptr);
}

constexpr void UniqueResourceTester::testFreeSwap() noexcept
{
    constexpr auto free = []()
    {
        auto res = SomeResource(deleteResource, newResource, 1);
        res.free();
        return res.get() == 0 && *res == 0;
    };

    constexpr auto swap = []()
    {
        auto res1 = SomeResource(deleteResource, newResource, 1);
        auto res2 = SomeResource(deleteResource, newResource, 2);
        res1.swap(res2);
        return res1.get() == 2 && res2.get() == 1 &&
            *res1 == 2 && *res2 == 1;
    };

    static_assert(free() && swap());
}

#endif // PROVINGGROUNDS_TESTS_DETAILS_UNIQUERESOURCETESTERIMPL_IPP
