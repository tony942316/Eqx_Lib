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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_STATICVECTORTESTERIMPL_IPP
#define PROVINGGROUNDS_TESTS_DETAILS_STATICVECTORTESTERIMPL_IPP

#include "StaticVectorTesterDecl.hpp"

inline void StaticVectorTester::test()
{
    std::cout << "Testing Static Vector..." << std::endl;
    UnitTester::printStatus();
    UnitTester::clear();
}

constexpr void StaticVectorTester::testConstruction() noexcept
{
    constexpr auto Vec1 = eqx::StaticVector<int, 3>();
    constexpr auto Vec2 = eqx::StaticVector<int, 3>(1, 2, 3);

    static_assert(Vec1.size() == 0);
    static_assert(Vec1.capacity() == 3);
    static_assert(Vec2.size() == 3);
    static_assert(Vec2.capacity() == 3);
    static_assert(Vec2.at(0) == 1);
    static_assert(Vec2.at(1) == 2);
    static_assert(Vec2.at(2) == 3);

    constexpr auto Vec3 = eqx::StaticVector<SomeType, 2>();
    constexpr auto Vec4 = eqx::StaticVector<SomeType, 3>(1, 2);

    static_assert(Vec3.size() == 0);
    static_assert(Vec3.capacity() == 2);
    static_assert(Vec4.size() == 2);
    static_assert(Vec4.capacity() == 3);
    static_assert(Vec4.at(0).get() == 1);
    static_assert(Vec4.at(1).get() == 2);
}

constexpr void StaticVectorTester::testBraceOp() noexcept
{
    constexpr auto Vec1 = eqx::StaticVector<int, 3>();
    constexpr auto Vec2 = eqx::StaticVector<int, 3>(1, 2, 3);

    static_assert(Vec1.size() == 0);
    static_assert(Vec1.capacity() == 3);
    static_assert(Vec2.size() == 3);
    static_assert(Vec2.capacity() == 3);
    static_assert(Vec2[0] == 1);
    static_assert(Vec2[1] == 2);
    static_assert(Vec2[2] == 3);

    constexpr auto Vec3 = eqx::StaticVector<SomeType, 2>();
    constexpr auto Vec4 = eqx::StaticVector<SomeType, 3>(1, 2);

    static_assert(Vec3.size() == 0);
    static_assert(Vec3.capacity() == 2);
    static_assert(Vec4.size() == 2);
    static_assert(Vec4.capacity() == 3);
    static_assert(Vec4[0].get() == 1);
    static_assert(Vec4[1].get() == 2);
}

constexpr void StaticVectorTester::testFrontBack() noexcept
{
    constexpr auto Vec1 = eqx::StaticVector<int, 3>();
    constexpr auto Vec2 = eqx::StaticVector<int, 3>(1, 2, 3);

    static_assert(Vec1.size() == 0);
    static_assert(Vec1.capacity() == 3);
    static_assert(Vec2.size() == 3);
    static_assert(Vec2.capacity() == 3);
    static_assert(Vec2.front() == 1);
    static_assert(Vec2.back() == 3);

    constexpr auto Vec3 = eqx::StaticVector<SomeType, 2>();
    constexpr auto Vec4 = eqx::StaticVector<SomeType, 3>(1, 2);

    static_assert(Vec3.size() == 0);
    static_assert(Vec3.capacity() == 2);
    static_assert(Vec4.size() == 2);
    static_assert(Vec4.capacity() == 3);
    static_assert(Vec4.front().get() == 1);
    static_assert(Vec4.back().get() == 2);
}

constexpr void StaticVectorTester::testIter() noexcept
{
    constexpr auto testForEach = []() constexpr
    {
        auto Vec = eqx::StaticVector<int, 3>(1, 2, 3);
        auto Expected = std::array<int, 3>({ 1, 2, 3 });
        auto Result = true;

        std::ranges::for_each(std::views::iota(0, 3),
            [&Vec, &Expected, &Result](int val)
            {
                Result = Result && Vec.at(static_cast<std::uint8_t>(val) ==
                    Expected.at(static_cast<std::size_t>(val)));
            });

        return Result;
    };

    constexpr auto testTransform = []() constexpr
    {
        auto Vec = eqx::StaticVector<int, 3>(1, 2, 3);
        auto Expected = std::array<int, 3>({ 1, 2, 3 });

        std::ranges::transform(Vec, Expected, std::ranges::begin(Vec),
            [](int val1, int val2)
            {
                return val1 - val2;
            });

        return std::ranges::all_of(Vec, [](int val) { return val == 0; });
    };

    constexpr auto testBackInserter = []() constexpr
    {
        auto Vec = eqx::StaticVector<int, 10>();
        auto Expected = std::array<int, 3>({ 1, 2, 3 });
        std::ranges::copy(Expected | std::views::reverse,
            std::back_inserter(Vec));
        return std::ranges::equal(Vec | std::views::reverse, Expected);
    };

    static_assert(testForEach());
    static_assert(testTransform());
    static_assert(testBackInserter());
}

constexpr void StaticVectorTester::testEmptyClearCapacity() noexcept
{
    constexpr auto Vec1 = eqx::StaticVector<SomeType, 10>();
    constexpr auto Vec2 = eqx::StaticVector<SomeType, 10>(1, 2, 3);

    constexpr auto testClear = []() constexpr
    {
        auto Vec = eqx::StaticVector<SomeType, 10>(1, 2, 3);
        auto Result = true;
        Result = Result && !Vec.empty();
        Vec.clear();
        Result = Result && Vec.empty();
        Result = Result && Vec.capacity() == 10;

        return Result;
    };

    static_assert(Vec1.empty());
    static_assert(Vec1.capacity() == 10);
    static_assert(!Vec2.empty());
    static_assert(Vec2.capacity() == 10);
    static_assert(testClear());
}

constexpr void StaticVectorTester::testPushEmplaceBack() noexcept
{
    constexpr auto test = []() constexpr
    {
        auto Vec = eqx::StaticVector<SomeType, 10>();
        auto Expected = std::array<int, 4>({ 5, 6, 1, 10 });
        auto Val = SomeType(5);
        Vec.push_back(Val);
        Vec.push_back(SomeType(6));
        Vec.push_back(1);
        Vec.emplace_back(10);


        return std::ranges::equal(
            Vec |
            std::views::transform([](const auto& val)
                { return val.get();  }),
            Expected);
    };

    static_assert(test());
}

constexpr void StaticVectorTester::testPopResize() noexcept
{
    constexpr auto test = []() constexpr
    {
        auto Vec = eqx::StaticVector<int, 10>();
        auto Result = true;
        std::ranges::copy(std::views::iota(1, 11), std::back_inserter(Vec));
        Vec.pop_back();
        Vec.pop_back();
        Result = Result && Vec.size() == 8;
        Result = Result && std::ranges::equal(std::views::iota(1, 9), Vec);
        Vec.resize(5);
        Result = Result && Vec.size() == 5;
        Result = Result && std::ranges::equal(std::views::iota(1, 6), Vec);
        Vec.resize(10);
        Result = Result && Vec.size() == 10;
        Result = Result && std::ranges::equal(std::views::iota(1, 6),
            Vec | std::views::take(5));
        Result = Result && std::ranges::equal(
            std::views::iota(0) |
            std::views::take(5) |
            std::views::transform([](int val) { return val * 0; }),
            Vec |
            std::views::drop(5));

        return Result;
    };

    static_assert(test());
}

#endif // PROVINGGROUNDS_TESTS_DETAILS_STATICVECTORTESTERIMPL_IPP
