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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_POINTTESTERIMPL_IPP
#define PROVINGGROUNDS_TESTS_DETAILS_POINTTESTERIMPL_IPP

#include "PointTesterDecl.hpp"

inline void PointTester::test()
{
    std::cout << "Testing Point..." << std::endl;
    testToString();
    testDistance();
    testNormalize();
    testAngle();
    UnitTester::printStatus();
    UnitTester::clear();
}

inline void PointTester::testToString()
{
    using namespace std::literals;
    constexpr auto point1 = eqx::Point<double>(1.0, 1.0);
    constexpr auto point2 = eqx::Point<double>(-10.0, 10.0);
    constexpr auto point3 = eqx::Point<double>(1.234, 7.654);

    UnitTester::test(eqx::toString(point1), "(1.000000, 1.000000)"s);
    UnitTester::test(eqx::toString(point2), "(-10.000000, 10.000000)"s);
    UnitTester::test(eqx::toString(point3), "(1.234000, 7.654000)"s);
}

inline void PointTester::testDistance()
{
    constexpr auto point1 = eqx::Point<double>(1.0, 1.0);
    constexpr auto point2 = eqx::Point<double>(-10.0, 10.0);
    constexpr auto point3 = eqx::Point<double>(1.234, 7.654);

    UnitTester::test(eqx::distance(point1, point1), 0.0);
    UnitTester::test(eqx::distance(point1, point2), 14.2126704);
    UnitTester::test(eqx::distance(point1, point3), 6.658113246);
    UnitTester::test(eqx::distance(point2, point2), 0.0);
    UnitTester::test(eqx::distance(point2, point3), 11.47634402);
    UnitTester::test(eqx::distance(point3, point3), 0.0);

}

inline void PointTester::testNormalize()
{
    constexpr auto origin = eqx::Point<double>(0.0, 0.0);

    constexpr auto point1 = eqx::Point<double>(1.0, 1.0);
    constexpr auto point2 = eqx::Point<double>(-10.0, 10.0);
    constexpr auto point3 = eqx::Point<double>(1.234, 7.654);

    const auto point1Norm = eqx::normalize(point1);
    const auto point2Norm = eqx::normalize(point2);
    const auto point3Norm = eqx::normalize(point3);

    UnitTester::test(point1Norm.x, 0.70710678);
    UnitTester::test(point1Norm.y, 0.70710678);
    UnitTester::test(point2Norm.x, -0.70710678);
    UnitTester::test(point2Norm.y, 0.70710678);
    UnitTester::test(point3Norm.x, 0.15916755);
    UnitTester::test(point3Norm.y, 0.98725158);

    UnitTester::test(eqx::distance(origin, point1Norm), 1.0);
    UnitTester::test(eqx::distance(origin, point2Norm), 1.0);
    UnitTester::test(eqx::distance(origin, point3Norm), 1.0);
}

inline void PointTester::testAngle()
{
    constexpr auto point1 = eqx::Point<double>(1.0, 1.0);
    constexpr auto point2 = eqx::Point<double>(-10.0, 10.0);
    constexpr auto point3 = eqx::Point<double>(1.234, 7.654);

    UnitTester::test(eqx::angle(point1), 45.0);
    UnitTester::test(eqx::angle(point2), 135.0);
    UnitTester::test(eqx::angle(point3), 80.84141723);
}

constexpr void PointTester::testEquals() noexcept
{
    constexpr auto point1 = eqx::Point<double>(1.0, 1.0);
    constexpr auto point2 = eqx::Point<double>(-10.0, 10.0);
    constexpr auto point3 = eqx::Point<double>(1.234, 7.654);
    constexpr auto point4 = eqx::Point<double>(-10.0, 10.0);

    static_assert(eqx::equals(point1, point1) == true);
    static_assert(eqx::equals(point1, point2) == false);
    static_assert(eqx::equals(point1, point3) == false);
    static_assert(eqx::equals(point1, point4) == false);
    static_assert(eqx::equals(point2, point2) == true);
    static_assert(eqx::equals(point2, point3) == false);
    static_assert(eqx::equals(point2, point4) == true);
    static_assert(eqx::equals(point3, point3) == true);
    static_assert(eqx::equals(point3, point4) == false);
    static_assert(eqx::equals(point4, point4) == true);
}

constexpr void PointTester::testConstruction() noexcept
{
    constexpr auto pointDefault = eqx::Point<double>();
    static_assert(pointDefault.x == 0.0);
    static_assert(pointDefault.y == 0.0);

    constexpr auto pointParam = eqx::Point<double>(1.5, 3.9);
    static_assert(pointParam.x == 1.5);
    static_assert(pointParam.y == 3.9);
}

constexpr void PointTester::testPlus() noexcept
{
    constexpr auto point1 = eqx::Point<double>(1.0, 1.0);
    constexpr auto point2 = eqx::Point<double>(-10.0, 10.0);
    constexpr auto point3 = eqx::Point<double>(1.234, 7.654);

    constexpr auto testLambda =
        [](const eqx::Point<double>& point, double x, double y) constexpr
        {
            return UnitTesterFunctions::E.first(point.x, x) &&
                UnitTesterFunctions::E.first(point.y, y);
        };

    static_assert(testLambda(point1 + point1, 2.0, 2.0));
    static_assert(testLambda(point1 + point2, -9.0, 11.0));
    static_assert(testLambda(point1 + point3, 2.234, 8.654));
    static_assert(testLambda(point2 + point2, -20.0, 20.0));
    static_assert(testLambda(point2 + point3, -8.766, 17.654));
    static_assert(testLambda(point3 + point3, 2.468, 15.308));
}

constexpr void PointTester::testMinus() noexcept
{
    constexpr auto point1 = eqx::Point<double>(1.0, 1.0);
    constexpr auto point2 = eqx::Point<double>(-10.0, 10.0);
    constexpr auto point3 = eqx::Point<double>(1.234, 7.654);

    constexpr auto testLambda =
        [](const eqx::Point<double>& point, double x, double y) constexpr
        {
            return UnitTesterFunctions::E.first(point.x, x) &&
                UnitTesterFunctions::E.first(point.y, y);
        };

    static_assert(testLambda(point1 - point1, 0.0, 0.0));
    static_assert(testLambda(point1 - point2, 11.0, -9.0));
    static_assert(testLambda(point1 - point3, -0.234, -6.654));
    static_assert(testLambda(point2 - point2, 0.0, 0.0));
    static_assert(testLambda(point2 - point3, -11.234, 2.346));
    static_assert(testLambda(point3 - point3, 0.0, 0.0));
}

constexpr void PointTester::testTimes() noexcept
{
    constexpr auto point1 = eqx::Point<double>(1.0, 1.0);
    constexpr auto point2 = eqx::Point<double>(-10.0, 10.0);
    constexpr auto point3 = eqx::Point<double>(1.234, 7.654);

    constexpr auto testLambda =
        [](const eqx::Point<double>& point, double x, double y) constexpr
        {
            return UnitTesterFunctions::E.first(point.x, x) &&
                UnitTesterFunctions::E.first(point.y, y);
        };

    static_assert(testLambda(point1 * 2.0, 2.0, 2.0));
    static_assert(testLambda(point1 * -2.0, -2.0, -2.0));
    static_assert(testLambda(point1 * 0.0, 0.0, 0.0));
    static_assert(testLambda(point2 * 1.0, -10.0, 10.0));
    static_assert(testLambda(point2 * -3.0, 30.0, -30.0));
    static_assert(testLambda(point2 * 1.5, -15.0, 15.0));
    static_assert(testLambda(point3 * 10.0, 12.34, 76.54));
    static_assert(testLambda(point3 * -10.0, -12.34, -76.54));
    static_assert(testLambda(point3 * 1.02, 1.25868, 7.80708));
}

constexpr void PointTester::testDivide() noexcept
{

    constexpr auto point1 = eqx::Point<double>(1.0, 1.0);
    constexpr auto point2 = eqx::Point<double>(-10.0, 10.0);
    constexpr auto point3 = eqx::Point<double>(1.234, 7.654);

    constexpr auto testLambda =
        [](const eqx::Point<double>& point, double x, double y) constexpr
        {
            return UnitTesterFunctions::E.first(point.x, x) &&
                UnitTesterFunctions::E.first(point.y, y);
        };

    static_assert(testLambda(point1 / 2.0, 0.5, 0.5));
    static_assert(testLambda(point1 / -2.0, -0.5, -0.5));
    static_assert(testLambda(point2 / 1.0, -10.0, 10.0));
    static_assert(testLambda(point2 / -3.0, 3.3333333, -3.3333333));
    static_assert(testLambda(point2 / 1.5, -6.6666666, 6.6666666));
    static_assert(testLambda(point3 / 10.0, 0.1234, 0.7654));
    static_assert(testLambda(point3 / -10.0, -0.1234, -0.7654));
    static_assert(testLambda(point3 / 1.02, 1.209803, 7.50392));
}

constexpr void PointTester::testIndexConversions() noexcept
{
    constexpr auto Point1 = eqx::Point<int>(0, 0);
    constexpr auto Point2 = eqx::Point<int>(0, 10);
    constexpr auto Point3 = eqx::Point<int>(10, 0);
    constexpr auto Point4 = eqx::Point<int>(10, 10);

    static_assert(eqx::coordToIndex(Point1, 10) == 0);
    static_assert(eqx::coordToIndex(Point1, 1) == 0);
    static_assert(eqx::coordToIndex(Point1, 100) == 0);
    static_assert(eqx::coordToIndex(Point2, 10) == 100);
    static_assert(eqx::coordToIndex(Point2, 1) == 10);
    static_assert(eqx::coordToIndex(Point2, 100) == 1000);
    static_assert(eqx::coordToIndex(Point3, 100) == 10);
    static_assert(eqx::coordToIndex(Point3, 50) == 10);
    static_assert(eqx::coordToIndex(Point3, 10000) == 10);
    static_assert(eqx::coordToIndex(Point4, 100) == 1010);
    static_assert(eqx::coordToIndex(Point4, 50) == 510);
    static_assert(eqx::coordToIndex(Point4, 10000) == 100010);

    static_assert(eqx::indexToCoord(0, 10) == Point1);
    static_assert(eqx::indexToCoord(0, 1) == Point1);
    static_assert(eqx::indexToCoord(0, 100) == Point1);
    static_assert(eqx::indexToCoord(100, 10) == Point2);
    static_assert(eqx::indexToCoord(10, 1) == Point2);
    static_assert(eqx::indexToCoord(1000, 100) == Point2);
    static_assert(eqx::indexToCoord(10, 100) == Point3);
    static_assert(eqx::indexToCoord(10, 50) == Point3);
    static_assert(eqx::indexToCoord(10, 10000) == Point3);
    static_assert(eqx::indexToCoord(1010, 100) == Point4);
    static_assert(eqx::indexToCoord(510, 50) == Point4);
    static_assert(eqx::indexToCoord(100010, 10000) == Point4);
}

#endif // PROVINGGROUNDS_TESTS_DETAILS_POINTTESTERIMPL_IPP
