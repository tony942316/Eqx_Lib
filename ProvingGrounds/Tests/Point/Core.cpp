module Eqx.Tests.Point:Core;

#include <Eqx/std.hpp>

import Eqx.Lib.Math.Core;
import Eqx.Lib.Math.Modulator;
import Eqx.Lib.Point;

using namespace eqx::literals;

static_assert(std::is_trivial_v<eqx::Point<double>>);
static_assert(std::is_standard_layout_v<eqx::Point<double>>);

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
constexpr auto point0I = eqx::Point<int>{0, 0};
constexpr auto point0F = eqx::Point<float>{0.0F, 0.0F};
constexpr auto point0 = eqx::Point<double>{0.0, 0.0};
constexpr auto point0L = eqx::Point<long double>{0.0L, 0.0L};
constexpr auto point1 = eqx::Point<double>{1.5, 3.9};
constexpr auto point2 = eqx::Point<double>{1.0, 1.0};
constexpr auto point3 = eqx::Point<double>{-10.0, 10.0};
constexpr auto point4 = eqx::Point<double>{1.234, 7.654};

static_assert(point0I.x == 0 && point0I.y == 0);
static_assert(point0F.x == 0.0F && point0F.y == 0.0F);
static_assert(point0.x == 0.0 && point0.y == 0.0);
static_assert(point0L.x == 0.0L && point0L.y == 0.0L);
static_assert(point1.x == 1.5 && point1.y == 3.9);
static_assert(point2.x == 1.0 && point2.y == 1.0);
static_assert(point3.x == -10.0 && point3.y == 10.0);
static_assert(point4.x == 1.234 && point4.y == 7.654);

// NOLINTBEGIN(misc-redundant-expression)
static_assert(point0I == point0I);
static_assert(point0F == point0F);
static_assert(point0 == point0);
static_assert(point0L == point0L);
static_assert(point1 == point1);
static_assert(point2 == point2);
static_assert(point3 == point3);
static_assert(point4 == point4);
// NOLINTEND(misc-redundant-expression)

static_assert(point0 != point1);
static_assert(point0 != point2);
static_assert(point0 != point3);
static_assert(point0 != point4);
static_assert(point1 != point2);
static_assert(point1 != point3);
static_assert(point1 != point4);
static_assert(point2 != point3);
static_assert(point2 != point4);
static_assert(point3 != point4);

static_assert(eqx::equals(point0I, point0I));
static_assert(eqx::equals(point0F, point0F));
static_assert(eqx::equals(point0, point0));
static_assert(eqx::equals(point0L, point0L));
static_assert(eqx::equals(point1, point1));
static_assert(eqx::equals(point2, point2));
static_assert(eqx::equals(point3, point3));
static_assert(eqx::equals(point4, point4));

static_assert(eqx::equals(eqx::distance(point0F, point0F), 0.0F));
static_assert(eqx::equals(eqx::distance(point0, point0), 0.0));
static_assert(eqx::equals(eqx::distance(point0L, point0L), 0.0L));
static_assert(eqx::equals(eqx::distance(point0, point1), 4.17851));
static_assert(eqx::equals(eqx::distance(point0, point2), std::numbers::sqrt2));
static_assert(eqx::equals(eqx::distance(point0, point3), 14.14213));
static_assert(eqx::equals(eqx::distance(point0, point4), 7.75283));
static_assert(eqx::equals(eqx::distance(point1, point1), 0.0));
static_assert(eqx::equals(eqx::distance(point1, point2), 2.94278));
static_assert(eqx::equals(eqx::distance(point1, point3), 13.01768));
static_assert(eqx::equals(eqx::distance(point1, point4), 3.76341));
static_assert(eqx::equals(eqx::distance(point2, point2), 0.0));
static_assert(eqx::equals(eqx::distance(point2, point3), 14.21267));
static_assert(eqx::equals(eqx::distance(point2, point4), 6.65811));
static_assert(eqx::equals(eqx::distance(point3, point3), 0.0));
static_assert(eqx::equals(eqx::distance(point3, point4), 11.47634));
static_assert(eqx::equals(eqx::distance(point4, point4), 0.0));

static_assert(eqx::equals(eqx::normalize(eqx::Point<float>(1.0F, 0.0F)),
    eqx::Point<float>(1.0F, 0.0F)));
static_assert(eqx::equals(eqx::normalize(eqx::Point<double>(1.0, 0.0)),
    eqx::Point<double>(1.0, 0.0)));
static_assert(eqx::equals(eqx::normalize(eqx::Point<long double>(1.0L, 0.0L)),
    eqx::Point<long double>(1.0L, 0.0L)));
static_assert(eqx::equals(eqx::normalize(point1),
    eqx::Point<double>(0.35897, 0.93334)));
static_assert(eqx::equals(eqx::normalize(point2),
    eqx::Point<double>(0.7071, 0.7071)));
static_assert(eqx::equals(eqx::normalize(point3),
    eqx::Point<double>(-0.7071, 0.7071)));
static_assert(eqx::equals(eqx::normalize(point4),
    eqx::Point<double>(0.15916, 0.98725)));

//static_assert(eqx::equals(eqx::angle(eqx::Point<float>{1.0F, 0.0F}), 0.0_radF));
static_assert(eqx::equals(eqx::angle(eqx::Point<double>{1.0, 0.0}), 0.0_rad));
static_assert(
    eqx::equals(eqx::angle(eqx::Point<long double>(1.0L, 0.0L)), 0.0_radL));
static_assert(eqx::equals(eqx::angle(point1), 1.20362_rad));
static_assert(eqx::equals(eqx::angle(point2),
    eqx::Radians<double>{eqx::c_Pi4<double>}));
static_assert(eqx::equals(eqx::angle(point3),
    eqx::Radians<double>{eqx::c_3Pi4<double>}));
static_assert(eqx::equals(eqx::angle(point4), 1.410949_rad));


static_assert(eqx::equals(point0I + point0I, point0I));
static_assert(eqx::equals(point0F + point0F, point0F));
static_assert(eqx::equals(point0 + point0, point0));
static_assert(eqx::equals(point0L + point0L, point0L));
static_assert(eqx::equals(point0 + point1, point1));
static_assert(eqx::equals(point0 + point2, point2));
static_assert(eqx::equals(point0 + point3, point3));
static_assert(eqx::equals(point0 + point4, point4));
static_assert(eqx::equals(point1 + point1, eqx::Point<double>(3.0, 7.8)));
static_assert(eqx::equals(point1 + point2, eqx::Point<double>(2.5, 4.9)));
static_assert(eqx::equals(point1 + point3, eqx::Point<double>(-8.5, 13.9)));
static_assert(eqx::equals(point1 + point4, eqx::Point<double>(2.734, 11.554)));
static_assert(eqx::equals(point2 + point2, eqx::Point<double>(2.0, 2.0)));
static_assert(eqx::equals(point2 + point3, eqx::Point<double>(-9.0, 11.0)));
static_assert(eqx::equals(point2 + point4, eqx::Point<double>(2.234, 8.654)));
static_assert(eqx::equals(point3 + point3, eqx::Point<double>(-20.0, 20.0)));
static_assert(eqx::equals(point3 + point4, eqx::Point<double>(-8.766, 17.654)));
static_assert(eqx::equals(point4 + point4, eqx::Point<double>(2.468, 15.308)));

// NOLINTBEGIN(misc-redundant-expression)
static_assert(eqx::equals(point0I - point0I, point0I));
static_assert(eqx::equals(point0F - point0F, point0F));
static_assert(eqx::equals(point0 - point0, point0));
static_assert(eqx::equals(point0L - point0L, point0L));
static_assert(eqx::equals(point0 - point1, eqx::Point<double>(-1.5, -3.9)));
static_assert(eqx::equals(point0 - point2, eqx::Point<double>(-1.0, -1.0)));
static_assert(eqx::equals(point0 - point3, eqx::Point<double>(10.0, -10.0)));
static_assert(eqx::equals(point0 - point4, eqx::Point<double>(-1.234, -7.654)));
static_assert(eqx::equals(point1 - point1, point0));
static_assert(eqx::equals(point1 - point2, eqx::Point<double>(0.5, 2.9)));
static_assert(eqx::equals(point1 - point3, eqx::Point<double>(11.5, -6.1)));
static_assert(eqx::equals(point1 - point4, eqx::Point<double>(0.266, -3.754)));
static_assert(eqx::equals(point2 - point2, point0));
static_assert(eqx::equals(point2 - point3, eqx::Point<double>(11.0, -9.0)));
static_assert(eqx::equals(point2 - point4, eqx::Point<double>(-0.234, -6.654)));
static_assert(eqx::equals(point3 - point3, point0));
static_assert(eqx::equals(point3 - point4, eqx::Point<double>(-11.234, 2.346)));
static_assert(eqx::equals(point4 - point4, point0));
// NOLINTEND(misc-redundant-expression)

static_assert(eqx::equals(point0I * 0, point0I));
static_assert(eqx::equals(point0F * 0.0F, point0F));
static_assert(eqx::equals(point0 * 0.0, point0));
static_assert(eqx::equals(point0L * 0.0L, point0L));
static_assert(eqx::equals(point1 * 0.0, point0));
static_assert(eqx::equals(point2 * 0.0, point0));
static_assert(eqx::equals(point3 * 0.0, point0));
static_assert(eqx::equals(point4 * 0.0, point0));
static_assert(eqx::equals(point0 * 1.0, point0));
static_assert(eqx::equals(point1 * 1.0, point1));
static_assert(eqx::equals(point2 * 1.0, point2));
static_assert(eqx::equals(point3 * 1.0, point3));
static_assert(eqx::equals(point4 * 1.0, point4));
static_assert(eqx::equals(point0 * -1.0, point0));
static_assert(eqx::equals(point1 * -1.0, eqx::Point<double>(-1.5, -3.9)));
static_assert(eqx::equals(point2 * -1.0, eqx::Point<double>(-1.0, -1.0)));
static_assert(eqx::equals(point3 * -1.0, eqx::Point<double>(10.0, -10.0)));
static_assert(eqx::equals(point4 * -1.0, eqx::Point<double>(-1.234, -7.654)));
static_assert(eqx::equals(point0 * 1.5, point0));
static_assert(eqx::equals(point1 * 1.5, eqx::Point<double>(2.25, 5.85)));
static_assert(eqx::equals(point2 * 1.5, eqx::Point<double>(1.5, 1.5)));
static_assert(eqx::equals(point3 * 1.5, eqx::Point<double>(-15.0, 15.0)));
static_assert(eqx::equals(point4 * 1.5, eqx::Point<double>(1.851, 11.481)));
static_assert(eqx::equals(point0 * -1.5, point0));
static_assert(eqx::equals(point1 * -1.5, eqx::Point<double>(-2.25, -5.85)));
static_assert(eqx::equals(point2 * -1.5, eqx::Point<double>(-1.5, -1.5)));
static_assert(eqx::equals(point3 * -1.5, eqx::Point<double>(15.0, -15.0)));
static_assert(eqx::equals(point4 * -1.5, eqx::Point<double>(-1.851, -11.481)));

static_assert(eqx::equals(point0 / 1, point0));
static_assert(eqx::equals(point0F / 1.0, point0F));
static_assert(eqx::equals(point0 / 1.0, point0));
static_assert(eqx::equals(point0L / 1.0, point0L));
static_assert(eqx::equals(point1 / 1.0, point1));
static_assert(eqx::equals(point2 / 1.0, point2));
static_assert(eqx::equals(point3 / 1.0, point3));
static_assert(eqx::equals(point4 / 1.0, point4));
static_assert(eqx::equals(point0 / -1.0, point0));
static_assert(eqx::equals(point1 / -1.0, eqx::Point<double>(-1.5, -3.9)));
static_assert(eqx::equals(point2 / -1.0, eqx::Point<double>(-1.0, -1.0)));
static_assert(eqx::equals(point3 / -1.0, eqx::Point<double>(10.0, -10.0)));
static_assert(eqx::equals(point4 / -1.0, eqx::Point<double>(-1.234, -7.654)));
static_assert(eqx::equals(point0 / 1.5, point0));
static_assert(eqx::equals(point1 / 1.5, eqx::Point<double>(1.0, 2.6)));
static_assert(eqx::equals(point2 / 1.5, eqx::Point<double>(0.66666, 0.66666)));
static_assert(eqx::equals(point3 / 1.5, eqx::Point<double>(-6.66666, 6.66666)));
static_assert(eqx::equals(point4 / 1.5, eqx::Point<double>(0.82266, 5.10266)));
static_assert(eqx::equals(point0 / -1.5, point0));
static_assert(eqx::equals(point1 / -1.5, eqx::Point<double>(-1.0, -2.6)));
static_assert(
    eqx::equals(point2 / -1.5, eqx::Point<double>(-0.66666, -0.66666)));
static_assert(
    eqx::equals(point3 / -1.5, eqx::Point<double>(6.66666, -6.66666)));
static_assert(
    eqx::equals(point4 / -1.5, eqx::Point<double>(-0.82266, -5.10266)));

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

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
