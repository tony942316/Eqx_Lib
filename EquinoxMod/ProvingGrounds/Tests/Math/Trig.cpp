module Eqx.Tests.Math:Trig;

import Eqx.Stdm;
import Equinox.Math.Core;
import Equinox.Math.Trig;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
static_assert(eqx::equals(eqx::degreesToRadians(0.0F), 0.0F));
static_assert(eqx::equals(eqx::degreesToRadians(0.0), 0.0));
static_assert(eqx::equals(eqx::degreesToRadians(0.0L), 0.0L));
static_assert(eqx::equals(eqx::degreesToRadians(1.0), 0.0174533));
static_assert(eqx::equals(eqx::degreesToRadians(30.0), 0.523599));
static_assert(eqx::equals(eqx::degreesToRadians(45.0), 0.785398));
static_assert(eqx::equals(eqx::degreesToRadians(60.0), 1.0472));
static_assert(eqx::equals(eqx::degreesToRadians(90.0), 1.5708));
static_assert(eqx::equals(eqx::degreesToRadians(120.0), 2.0944));
static_assert(eqx::equals(eqx::degreesToRadians(135.0), 2.35619));
static_assert(eqx::equals(eqx::degreesToRadians(150.0), 2.61799));
static_assert(eqx::equals(eqx::degreesToRadians(180.0), 3.14159));
static_assert(eqx::equals(eqx::degreesToRadians(210.0), 3.66519));
static_assert(eqx::equals(eqx::degreesToRadians(225.0), 3.92699));
static_assert(eqx::equals(eqx::degreesToRadians(240.0), 4.18879));
static_assert(eqx::equals(eqx::degreesToRadians(270.0), 4.71239));
static_assert(eqx::equals(eqx::degreesToRadians(300.0), 5.23599));
static_assert(eqx::equals(eqx::degreesToRadians(315.0), 5.49779));
static_assert(eqx::equals(eqx::degreesToRadians(330.0), 5.75959));
static_assert(eqx::equals(eqx::degreesToRadians(360.0), 6.28319));

constexpr auto pi6 = stdm::numbers::pi / 6.0;
constexpr auto pi4 = stdm::numbers::pi / 4.0;
constexpr auto pi3 = stdm::numbers::pi / 3.0;
constexpr auto pi2 = stdm::numbers::pi / 2.0;

static_assert(eqx::equals(eqx::radiansToDegrees(0.0F), 0.0F));
static_assert(eqx::equals(eqx::radiansToDegrees(0.0), 0.0));
static_assert(eqx::equals(eqx::radiansToDegrees(0.0L), 0.0L));
static_assert(eqx::equals(eqx::radiansToDegrees(pi6), 30.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi4), 45.0));
static_assert(eqx::equals(eqx::radiansToDegrees(1.0), 57.29578));
static_assert(eqx::equals(eqx::radiansToDegrees(pi3), 60.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi2), 90.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi3 * 2.0), 120.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi4 * 3.0), 135.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi6 * 5.0), 150.0));
static_assert(eqx::equals(eqx::radiansToDegrees(stdm::numbers::pi), 180.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi6 * 7.0), 210.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi4 * 5.0), 225.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi3 * 4.0), 240.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi2 * 3.0), 270.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi3 * 5.0), 300.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi4 * 7.0), 315.0));
static_assert(eqx::equals(eqx::radiansToDegrees(pi6 * 11.0), 330.0));
static_assert(
    eqx::equals(eqx::radiansToDegrees(stdm::numbers::pi * 2.0), 360.0));

//static_assert(eqx::equals(eqx::angAbs(-0.0F),
    //2.0F * stdm::numbers::pi_v<float>));
//static_assert(eqx::equals(eqx::angAbs(-0.0), 2.0 * stdm::numbers::pi));
//static_assert(eqx::equals(eqx::angAbs(-0.0L),
    //2.0L * stdm::numbers::pi_v<long double>));
static_assert(eqx::equals(eqx::angAbs(-stdm::numbers::pi), stdm::numbers::pi));
static_assert(eqx::equals(eqx::angAbs(-5.0 * pi6), 7.0 * pi6));
static_assert(eqx::equals(eqx::angAbs(-3.0 * pi4), 5.0 * pi4));
static_assert(eqx::equals(eqx::angAbs(-2.0 * pi3), 4.0 * pi3));
static_assert(eqx::equals(eqx::angAbs(-pi2), 3.0 * pi2));
static_assert(eqx::equals(eqx::angAbs(-pi3), 5.0 * pi3));
static_assert(eqx::equals(eqx::angAbs(-pi4), 7.0 * pi4));
static_assert(eqx::equals(eqx::angAbs(-pi6), 11.0 * pi6));

static_assert(eqx::equals(eqx::sin(0.0F), 0.0F));
static_assert(eqx::equals(eqx::sin(0.0), 0.0));
static_assert(eqx::equals(eqx::sin(0.0L), 0.0L));
static_assert(eqx::equals(eqx::sin(pi6), 0.5));
static_assert(eqx::equals(eqx::sin(pi4), 0.707107));
static_assert(eqx::equals(eqx::sin(pi3), 0.866025));
static_assert(eqx::equals(eqx::sin(pi2), 1.0));
static_assert(eqx::equals(eqx::sin(pi3 * 2.0), 0.866025));
static_assert(eqx::equals(eqx::sin(pi4 * 3.0), 0.707107));
static_assert(eqx::equals(eqx::sin(pi6 * 5.0), 0.5));
static_assert(eqx::equals(eqx::sin(stdm::numbers::pi), 0.0));
static_assert(eqx::equals(eqx::sin(pi6 * 7.0), -0.5));
static_assert(eqx::equals(eqx::sin(pi4 * 5.0), -0.707107));
static_assert(eqx::equals(eqx::sin(pi3 * 4.0), -0.866025));
static_assert(eqx::equals(eqx::sin(pi2 * 3.0), -1.0));
static_assert(eqx::equals(eqx::sin(pi3 * 5.0), -0.866025));
static_assert(eqx::equals(eqx::sin(pi4 * 7.0), -0.707107));
static_assert(eqx::equals(eqx::sin(pi6 * 11.0), -0.5));
static_assert(eqx::equals(eqx::sin(stdm::numbers::pi * 2.0), 0.0));
static_assert(eqx::equals(eqx::sin(-pi6), -0.5));
static_assert(eqx::equals(eqx::sin(-pi4), -0.707107));
static_assert(eqx::equals(eqx::sin(-pi3), -0.866025));
static_assert(eqx::equals(eqx::sin(-pi2), -1.0));
static_assert(eqx::equals(eqx::sin(-pi3 * 2.0), -0.866025));
static_assert(eqx::equals(eqx::sin(-pi4 * 3.0), -0.707107));
static_assert(eqx::equals(eqx::sin(-pi6 * 5.0), -0.5));
static_assert(eqx::equals(eqx::sin(-stdm::numbers::pi), 0.0));
static_assert(eqx::equals(eqx::sin(-pi6 * 7.0), 0.5));
static_assert(eqx::equals(eqx::sin(-pi4 * 5.0), 0.707107));
static_assert(eqx::equals(eqx::sin(-pi3 * 4.0), 0.866025));
static_assert(eqx::equals(eqx::sin(-pi2 * 3.0), 1.0));
static_assert(eqx::equals(eqx::sin(-pi3 * 5.0), 0.866025));
static_assert(eqx::equals(eqx::sin(-pi4 * 7.0), 0.707107));
static_assert(eqx::equals(eqx::sin(-pi6 * 11.0), 0.5));
static_assert(eqx::equals(eqx::sin(-stdm::numbers::pi * 2.0), 0.0));

static_assert(eqx::equals(eqx::cos(0.0F), 1.0F));
static_assert(eqx::equals(eqx::cos(0.0), 1.0));
static_assert(eqx::equals(eqx::cos(0.0L), 1.0L));
static_assert(eqx::equals(eqx::cos(pi6), 0.866025));
static_assert(eqx::equals(eqx::cos(pi4), 0.707107));
static_assert(eqx::equals(eqx::cos(pi3), 0.5));
static_assert(eqx::equals(eqx::cos(pi2), 0.0));
static_assert(eqx::equals(eqx::cos(pi3 * 2.0), -0.5));
static_assert(eqx::equals(eqx::cos(pi4 * 3.0), -0.707107));
static_assert(eqx::equals(eqx::cos(pi6 * 5.0), -0.866025));
static_assert(eqx::equals(eqx::cos(stdm::numbers::pi), -1.0));
static_assert(eqx::equals(eqx::cos(pi6 * 7.0), -0.866025));
static_assert(eqx::equals(eqx::cos(pi4 * 5.0), -0.707107));
static_assert(eqx::equals(eqx::cos(pi3 * 4.0), -0.5));
static_assert(eqx::equals(eqx::cos(pi2 * 3.0), 0.0));
static_assert(eqx::equals(eqx::cos(pi3 * 5.0), 0.5));
static_assert(eqx::equals(eqx::cos(pi4 * 7.0), 0.707107));
static_assert(eqx::equals(eqx::cos(pi6 * 11.0), 0.866025));
static_assert(eqx::equals(eqx::cos(stdm::numbers::pi * 2.0), 1.0));
static_assert(eqx::equals(eqx::cos(-pi6), 0.866025));
static_assert(eqx::equals(eqx::cos(-pi4), 0.707107));
static_assert(eqx::equals(eqx::cos(-pi3), 0.5));
static_assert(eqx::equals(eqx::cos(-pi2), 0.0));
static_assert(eqx::equals(eqx::cos(-pi3 * 2.0), -0.5));
static_assert(eqx::equals(eqx::cos(-pi4 * 3.0), -0.707107));
static_assert(eqx::equals(eqx::cos(-pi6 * 5.0), -0.866025));
static_assert(eqx::equals(eqx::cos(-stdm::numbers::pi), -1.0));
static_assert(eqx::equals(eqx::cos(-pi6 * 7.0), -0.866025));
static_assert(eqx::equals(eqx::cos(-pi4 * 5.0), -0.707107));
static_assert(eqx::equals(eqx::cos(-pi3 * 4.0), -0.5));
static_assert(eqx::equals(eqx::cos(-pi2 * 3.0), 0.0));
static_assert(eqx::equals(eqx::cos(-pi3 * 5.0), 0.5));
static_assert(eqx::equals(eqx::cos(-pi4 * 7.0), 0.707107));
static_assert(eqx::equals(eqx::cos(-pi6 * 11.0), 0.866025));
static_assert(eqx::equals(eqx::cos(-stdm::numbers::pi * 2.0), 1.0));

static_assert(eqx::equals(eqx::asin(0.0F), 0.0F));
static_assert(eqx::equals(eqx::asin(0.0), 0.0));
static_assert(eqx::equals(eqx::asin(0.0L), 0.0L));
static_assert(eqx::equals(eqx::asin(-1.0), -pi2));
static_assert(eqx::equals(eqx::asin(-0.866025), -pi3));
static_assert(eqx::equals(eqx::asin(-0.707107), -pi4));
static_assert(eqx::equals(eqx::asin(-0.5), -pi6));
static_assert(eqx::equals(eqx::asin(0.5), pi6));
static_assert(eqx::equals(eqx::asin(0.707107), pi4));
static_assert(eqx::equals(eqx::asin(0.866025), pi3));
static_assert(eqx::equals(eqx::asin(1.0), pi2));

static_assert(eqx::equals(eqx::acos(0.0F), static_cast<float>(pi2)));
static_assert(eqx::equals(eqx::acos(0.0), pi2));
static_assert(eqx::equals(eqx::acos(0.0L), static_cast<long double>(pi2)));
static_assert(eqx::equals(eqx::acos(-1.0), stdm::numbers::pi));
static_assert(eqx::equals(eqx::acos(-0.866025), pi6 * 5.0));
static_assert(eqx::equals(eqx::acos(-0.707107), pi4 * 3.0));
static_assert(eqx::equals(eqx::acos(-0.5), pi3 * 2.0));
static_assert(eqx::equals(eqx::acos(0.5), pi3));
static_assert(eqx::equals(eqx::acos(0.707107), pi4));
static_assert(eqx::equals(eqx::acos(0.866025), pi6));
static_assert(eqx::equals(eqx::acos(1.0), 0.0));

static_assert(eqx::equals(eqx::arcsin(0.0F),
    stdm::make_pair(0.0F, stdm::numbers::pi_v<float>)));
static_assert(eqx::equals(eqx::arcsin(0.0),
    stdm::make_pair(0.0, stdm::numbers::pi)));
static_assert(eqx::equals(eqx::arcsin(0.0L),
    stdm::make_pair(0.0L, stdm::numbers::pi_v<long double>)));
static_assert(eqx::equals(eqx::arcsin(-1.0),
    stdm::make_pair(3.0 * pi2, 3.0 * pi2)));
static_assert(eqx::equals(eqx::arcsin(-0.866025),
    stdm::make_pair(5.0 * pi3, 4.0 * pi3)));
static_assert(eqx::equals(eqx::arcsin(-0.707107),
    stdm::make_pair(7.0 * pi4, 5.0 * pi4)));
static_assert(eqx::equals(eqx::arcsin(-0.5),
    stdm::make_pair(11.0 * pi6, 7.0 * pi6)));
static_assert(eqx::equals(eqx::arcsin(0.5),
    stdm::make_pair(pi6, 5.0 * pi6)));
static_assert(eqx::equals(eqx::arcsin(0.707107),
    stdm::make_pair(pi4, 3.0 * pi4)));
static_assert(eqx::equals(eqx::arcsin(0.866025),
    stdm::make_pair(pi3, 2.0 * pi3)));
static_assert(eqx::equals(eqx::arcsin(1.0),
    stdm::make_pair(pi2, pi2)));

static_assert(eqx::equals(eqx::arccos(0.0F),
    stdm::make_pair(static_cast<float>(pi2), static_cast<float>(3.0F * pi2))));
static_assert(eqx::equals(eqx::arccos(0.0), stdm::make_pair(pi2, 3.0F * pi2)));
static_assert(eqx::equals(eqx::arccos(0.0L),
    stdm::make_pair(static_cast<long double>(pi2),
        static_cast<long double>(3.0L * pi2))));
static_assert(eqx::equals(eqx::arccos(-1.0),
    stdm::make_pair(stdm::numbers::pi, stdm::numbers::pi)));
static_assert(eqx::equals(eqx::arccos(-0.866025),
    stdm::make_pair(pi6 * 5.0, pi6 * 7.0)));
static_assert(eqx::equals(eqx::arccos(-0.707107),
    stdm::make_pair(pi4 * 3.0, pi4 * 5.0)));
static_assert(eqx::equals(eqx::arccos(-0.5),
    stdm::make_pair(pi3 * 2.0, pi3 * 4.0)));
static_assert(eqx::equals(eqx::arccos(0.5), stdm::make_pair(pi3, 5.0 * pi3)));
static_assert(eqx::equals(eqx::arccos(0.707107),
    stdm::make_pair(pi4, 7.0 * pi4)));
static_assert(eqx::equals(eqx::arccos(0.866025),
    stdm::make_pair(pi6, 11.0 * pi6)));
//static_assert(eqx::equals(eqx::arccos(1.0), stdm::make_pair(0.0, 0.0)));
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
