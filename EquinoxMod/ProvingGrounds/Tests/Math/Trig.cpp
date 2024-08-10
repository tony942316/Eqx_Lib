module Eqx.Tests.Math:Trig;

import Eqx.Stdm;
import Equinox.Math.Core;
import Equinox.Math.Modulator;
import Equinox.Math.Trig;

using namespace eqx::literals;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
static_assert(eqx::equals(eqx::degreesToRadians(0.0_degF), 0.0_radF));
static_assert(eqx::equals(eqx::degreesToRadians(0.0_deg), 0.0_rad));
static_assert(eqx::equals(eqx::degreesToRadians(0.0_degL), 0.0_radL));
static_assert(eqx::equals(eqx::degreesToRadians(1.0_deg), 0.0174533_rad));
static_assert(eqx::equals(eqx::degreesToRadians(30.0_deg), 0.523599_rad));
static_assert(eqx::equals(eqx::degreesToRadians(45.0_deg), 0.785398_rad));
static_assert(eqx::equals(eqx::degreesToRadians(60.0_deg), 1.0472_rad));
static_assert(eqx::equals(eqx::degreesToRadians(90.0_deg), 1.5708_rad));
static_assert(eqx::equals(eqx::degreesToRadians(120.0_deg), 2.0944_rad));
static_assert(eqx::equals(eqx::degreesToRadians(135.0_deg), 2.35619_rad));
static_assert(eqx::equals(eqx::degreesToRadians(150.0_deg), 2.61799_rad));
static_assert(eqx::equals(eqx::degreesToRadians(180.0_deg), 3.14159_rad));
static_assert(eqx::equals(eqx::degreesToRadians(210.0_deg), 3.66519_rad));
static_assert(eqx::equals(eqx::degreesToRadians(225.0_deg), 3.92699_rad));
static_assert(eqx::equals(eqx::degreesToRadians(240.0_deg), 4.18879_rad));
static_assert(eqx::equals(eqx::degreesToRadians(270.0_deg), 4.71239_rad));
static_assert(eqx::equals(eqx::degreesToRadians(300.0_deg), 5.23599_rad));
static_assert(eqx::equals(eqx::degreesToRadians(315.0_deg), 5.49779_rad));
static_assert(eqx::equals(eqx::degreesToRadians(330.0_deg), 5.75959_rad));
static_assert(eqx::equals(eqx::degreesToRadians(360.0_deg), 6.28319_rad));

static_assert(eqx::equals(eqx::radiansToDegrees(0.0_radF), 0.0_degF));
static_assert(eqx::equals(eqx::radiansToDegrees(0.0_rad), 0.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(0.0_radL), 0.0_degL));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_Pi6<double>}), 30.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_Pi4<double>}), 45.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(1.0_rad), 57.29578_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_Pi3<double>}), 60.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_Pi2<double>}), 90.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_2Pi3<double>}), 120.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_3Pi4<double>}), 135.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_5Pi6<double>}), 150.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{std::numbers::pi}), 180.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_7Pi6<double>}), 210.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_5Pi4<double>}), 225.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_4Pi3<double>}), 240.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_3Pi2<double>}), 270.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_5Pi3<double>}), 300.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_7Pi4<double>}), 315.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_11Pi6<double>}), 330.0_deg));
static_assert(eqx::equals(eqx::radiansToDegrees(
    eqx::Radians<double>{eqx::c_2Pi<double>}), 360.0_deg));

static_assert(eqx::equals(eqx::sin(0.0_radF), 0.0F));
static_assert(eqx::equals(eqx::sin(0.0_rad), 0.0));
static_assert(eqx::equals(eqx::sin(0.0_radL), 0.0L));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_Pi6<double>}), 0.5));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_Pi4<double>}), 0.707107));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_Pi3<double>}), 0.866025));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_Pi2<double>}), 1.0));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_2Pi3<double>}), 0.866025));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_3Pi4<double>}), 0.707107));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_5Pi6<double>}), 0.5));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{std::numbers::pi}), 0.0));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_7Pi6<double>}), -0.5));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_5Pi4<double>}), -0.707107));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_4Pi3<double>}), -0.866025));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_3Pi2<double>}), -1.0));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_5Pi3<double>}), -0.866025));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_7Pi4<double>}), -0.707107));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_11Pi6<double>}), -0.5));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{eqx::c_2Pi<double>}), 0.0));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_Pi6<double>}), -0.5));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_Pi4<double>}), -0.707107));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_Pi3<double>}), -0.866025));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_Pi2<double>}), -1.0));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_2Pi3<double>}), -0.866025));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_3Pi4<double>}), -0.707107));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_5Pi6<double>}), -0.5));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-std::numbers::pi}), 0.0));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_7Pi6<double>}), 0.5));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_5Pi4<double>}), 0.707107));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_4Pi3<double>}), 0.866025));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_3Pi2<double>}), 1.0));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_5Pi3<double>}), 0.866025));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_7Pi4<double>}), 0.707107));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_11Pi6<double>}), 0.5));
static_assert(eqx::equals(eqx::sin(
    eqx::Radians<double>{-eqx::c_2Pi<double>}), 0.0));

static_assert(eqx::equals(eqx::cos(0.0_radF), 1.0F));
static_assert(eqx::equals(eqx::cos(0.0_rad), 1.0));
static_assert(eqx::equals(eqx::cos(0.0_radL), 1.0L));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_Pi6<double>}), 0.866025));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_Pi4<double>}), 0.707107));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_Pi3<double>}), 0.5));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_Pi2<double>}), 0.0));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_2Pi3<double>}), -0.5));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_3Pi4<double>}), -0.707107));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_5Pi6<double>}), -0.866025));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{std::numbers::pi}), -1.0));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_7Pi6<double>}), -0.866025));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_5Pi4<double>}), -0.707107));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_4Pi3<double>}), -0.5));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_3Pi2<double>}), 0.0));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_5Pi3<double>}), 0.5));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_7Pi4<double>}), 0.707107));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_11Pi6<double>}), 0.866025));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{eqx::c_2Pi<double>}), 1.0));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_Pi6<double>}), 0.866025));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_Pi4<double>}), 0.707107));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_Pi3<double>}), 0.5));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_Pi2<double>}), 0.0));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_2Pi3<double>}), -0.5));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_3Pi4<double>}), -0.707107));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_5Pi6<double>}), -0.866025));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-std::numbers::pi}), -1.0));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_7Pi6<double>}), -0.866025));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_5Pi4<double>}), -0.707107));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_4Pi3<double>}), -0.5));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_3Pi2<double>}), 0.0));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_5Pi3<double>}), 0.5));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_7Pi4<double>}), 0.707107));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_11Pi6<double>}), 0.866025));
static_assert(eqx::equals(eqx::cos(
    eqx::Radians<double>{-eqx::c_2Pi<double>}), 1.0));

static_assert(eqx::equals(eqx::tan(0.0_radF), 0.0F));
static_assert(eqx::equals(eqx::tan(0.0_rad), 0.0));
static_assert(eqx::equals(eqx::tan(0.0_radL), 0.0L));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_Pi6<double>}), 0.57735));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_Pi4<double>}), 1.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_Pi3<double>}), 1.73205));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_2Pi3<double>}), -1.73205));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_3Pi4<double>}), -1.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_5Pi6<double>}), -0.57735));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{std::numbers::pi}), 0.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_7Pi6<double>}), 0.57735));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_5Pi4<double>}), 1.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_4Pi3<double>}), 1.73205));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_5Pi3<double>}), -1.73205));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_7Pi4<double>}), -1.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_11Pi6<double>}), -0.57735));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{eqx::c_2Pi<double>}), 0.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_Pi6<double>}), -0.57735));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_Pi4<double>}), -1.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_Pi3<double>}), -1.73205));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_2Pi3<double>}), 1.73205));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_3Pi4<double>}), 1.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_5Pi6<double>}), 0.57735));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-std::numbers::pi}), 0.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_7Pi6<double>}), -0.57735));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_5Pi4<double>}), -1.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_4Pi3<double>}), -1.73205));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_5Pi3<double>}), 1.73205));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_7Pi4<double>}), 1.0));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_11Pi6<double>}), 0.57735));
static_assert(eqx::equals(eqx::tan(
    eqx::Radians<double>{-eqx::c_2Pi<double>}), 0.0));

static_assert(eqx::equals(eqx::asin(0.0F), 0.0_radF));
static_assert(eqx::equals(eqx::asin(0.0), 0.0_rad));
static_assert(eqx::equals(eqx::asin(0.0L), 0.0_radL));
static_assert(eqx::equals(eqx::asin(-1.0),
    eqx::Radians<double>{-eqx::c_Pi2<double>}));
static_assert(eqx::equals(eqx::asin(-0.866025),
    eqx::Radians<double>{-eqx::c_Pi3<double>}));
static_assert(eqx::equals(eqx::asin(-0.707107),
    eqx::Radians<double>{-eqx::c_Pi4<double>}));
static_assert(eqx::equals(eqx::asin(-0.5),
    eqx::Radians<double>{-eqx::c_Pi6<double>}));
static_assert(eqx::equals(eqx::asin(0.5),
    eqx::Radians<double>{eqx::c_Pi6<double>}));
static_assert(eqx::equals(eqx::asin(0.707107),
    eqx::Radians<double>{eqx::c_Pi4<double>}));
static_assert(eqx::equals(eqx::asin(0.866025),
    eqx::Radians<double>{eqx::c_Pi3<double>}));
static_assert(eqx::equals(eqx::asin(1.0),
    eqx::Radians<double>{eqx::c_Pi2<double>}));

static_assert(eqx::equals(eqx::acos(0.0F),
    eqx::Radians<float>{eqx::c_Pi2<float>}));
static_assert(eqx::equals(eqx::acos(0.0),
    eqx::Radians<double>{eqx::c_Pi2<double>}));
static_assert(eqx::equals(eqx::acos(0.0L),
    eqx::Radians<long double>{eqx::c_Pi2<long double>}));
static_assert(eqx::equals(eqx::acos(-1.0),
    eqx::Radians<double>{std::numbers::pi}));
static_assert(eqx::equals(eqx::acos(-0.866025),
    eqx::Radians<double>{eqx::c_5Pi6<double>}));
static_assert(eqx::equals(eqx::acos(-0.707107),
    eqx::Radians<double>{eqx::c_3Pi4<double>}));
static_assert(eqx::equals(eqx::acos(-0.5),
    eqx::Radians<double>{eqx::c_2Pi3<double>}));
static_assert(eqx::equals(eqx::acos(0.5),
    eqx::Radians<double>{eqx::c_Pi3<double>}));
static_assert(eqx::equals(eqx::acos(0.707107),
    eqx::Radians<double>{eqx::c_Pi4<double>}));
static_assert(eqx::equals(eqx::acos(0.866025),
    eqx::Radians<double>{eqx::c_Pi6<double>}));
static_assert(eqx::equals(eqx::acos(1.0), 0.0_rad));

static_assert(eqx::equals(eqx::atan(0.0F), 0.0_radF));
static_assert(eqx::equals(eqx::atan(0.0), 0.0_rad));
static_assert(eqx::equals(eqx::atan(0.0L), 0.0_radL));
static_assert(eqx::equals(eqx::atan(0.57735),
    eqx::Radians<double>{eqx::c_Pi6<double>}));
static_assert(eqx::equals(eqx::atan(1.0),
    eqx::Radians<double>{eqx::c_Pi4<double>}));
static_assert(eqx::equals(eqx::atan(1.73205),
    eqx::Radians<double>{eqx::c_Pi3<double>}));
static_assert(eqx::equals(eqx::atan(-1.73205),
    eqx::Radians<double>{eqx::c_5Pi3<double>}));
static_assert(eqx::equals(eqx::atan(-1.0),
    eqx::Radians<double>{eqx::c_7Pi4<double>}));
static_assert(eqx::equals(eqx::atan(-0.57735),
    eqx::Radians<double>{eqx::c_11Pi6<double>}));
static_assert(eqx::equals(eqx::atan(0.0),
    eqx::Radians<double>{eqx::c_2Pi<double>}));

//static_assert(eqx::equals(eqx::atan2(1.0F, 0.0F), 0.0_radF));
static_assert(eqx::equals(eqx::atan2(1.0, 0.0), 0.0_rad));
static_assert(eqx::equals(eqx::atan2(1.0L, 0.0L), 0.0_radL));
static_assert(eqx::equals(eqx::atan2(0.866025, 0.5),
    eqx::Radians<double>{eqx::c_Pi6<double>}));
static_assert(eqx::equals(eqx::atan2(0.707107, 0.707107),
    eqx::Radians<double>{eqx::c_Pi4<double>}));
static_assert(eqx::equals(eqx::atan2(0.5, 0.866025),
    eqx::Radians<double>{eqx::c_Pi3<double>}));
static_assert(eqx::equals(eqx::atan2(0.0, 1.0),
    eqx::Radians<double>{eqx::c_Pi2<double>}));
static_assert(eqx::equals(eqx::atan2(-0.5, 0.866025),
    eqx::Radians<double>{eqx::c_2Pi3<double>}));
static_assert(eqx::equals(eqx::atan2(-0.707107, 0.707107),
    eqx::Radians<double>{eqx::c_3Pi4<double>}));
static_assert(eqx::equals(eqx::atan2(-0.866025, 0.5),
    eqx::Radians<double>{eqx::c_5Pi6<double>}));
static_assert(eqx::equals(eqx::atan2(-1.0, 0.0),
    eqx::Radians<double>{std::numbers::pi}));
static_assert(eqx::equals(eqx::atan2(-0.866025, -0.5),
    eqx::Radians<double>{eqx::c_7Pi6<double>}));
static_assert(eqx::equals(eqx::atan2(-0.707107, -0.707107),
    eqx::Radians<double>{eqx::c_5Pi4<double>}));
static_assert(eqx::equals(eqx::atan2(-0.5, -0.866025),
    eqx::Radians<double>{eqx::c_4Pi3<double>}));
static_assert(eqx::equals(eqx::atan2(0.0, -1.0),
    eqx::Radians<double>{eqx::c_3Pi2<double>}));
static_assert(eqx::equals(eqx::atan2(0.5, -0.866025),
    eqx::Radians<double>{eqx::c_5Pi3<double>}));
static_assert(eqx::equals(eqx::atan2(0.707107, -0.707107),
    eqx::Radians<double>{eqx::c_7Pi4<double>}));
static_assert(eqx::equals(eqx::atan2(0.866025, -0.5),
    eqx::Radians<double>{eqx::c_11Pi6<double>}));

static_assert(eqx::equals(eqx::arcsin(0.0F),
    std::make_pair(0.0_radF,
        eqx::Radians<float>{std::numbers::pi_v<float>})));
static_assert(eqx::equals(eqx::arcsin(0.0),
    std::make_pair(0.0_rad,
        eqx::Radians<double>{std::numbers::pi})));
static_assert(eqx::equals(eqx::arcsin(0.0L),
    std::make_pair(0.0_radL,
        eqx::Radians<long double>{std::numbers::pi_v<long double>})));

static_assert(eqx::equals(eqx::arcsin(-1.0),
    std::make_pair(eqx::Radians<double>{eqx::c_3Pi2<double>},
        eqx::Radians<double>{eqx::c_3Pi2<double>})));
static_assert(eqx::equals(eqx::arcsin(-0.866025),
    std::make_pair(eqx::Radians<double>{eqx::c_5Pi3<double>},
        eqx::Radians<double>{eqx::c_4Pi3<double>})));
static_assert(eqx::equals(eqx::arcsin(-0.707107),
    std::make_pair(eqx::Radians<double>{eqx::c_7Pi4<double>},
        eqx::Radians<double>{eqx::c_5Pi4<double>})));
static_assert(eqx::equals(eqx::arcsin(-0.5),
    std::make_pair(eqx::Radians<double>{eqx::c_11Pi6<double>},
        eqx::Radians<double>{eqx::c_7Pi6<double>})));
static_assert(eqx::equals(eqx::arcsin(0.5),
    std::make_pair(eqx::Radians<double>{eqx::c_Pi6<double>},
        eqx::Radians<double>{eqx::c_5Pi6<double>})));
static_assert(eqx::equals(eqx::arcsin(0.707107),
    std::make_pair(eqx::Radians<double>{eqx::c_Pi4<double>},
        eqx::Radians<double>{eqx::c_3Pi4<double>})));
static_assert(eqx::equals(eqx::arcsin(0.866025),
    std::make_pair(eqx::Radians<double>{eqx::c_Pi3<double>},
        eqx::Radians<double>{eqx::c_2Pi3<double>})));
static_assert(eqx::equals(eqx::arcsin(1.0),
    std::make_pair(eqx::Radians<double>{eqx::c_Pi2<double>},
        eqx::Radians<double>{eqx::c_Pi2<double>})));

static_assert(eqx::equals(eqx::arccos(0.0F),
    std::make_pair(eqx::Radians<float>{eqx::c_Pi2<float>},
        eqx::Radians<float>{eqx::c_3Pi2<float>})));
static_assert(eqx::equals(eqx::arccos(0.0),
    std::make_pair(eqx::Radians<double>{eqx::c_Pi2<double>},
        eqx::Radians<double>{eqx::c_3Pi2<double>})));
static_assert(eqx::equals(eqx::arccos(0.0L),
    std::make_pair(eqx::Radians<long double>{eqx::c_Pi2<long double>},
        eqx::Radians<long double>{eqx::c_3Pi2<long double>})));
static_assert(eqx::equals(eqx::arccos(-1.0),
    std::make_pair(eqx::Radians<double>{std::numbers::pi},
        eqx::Radians<double>{std::numbers::pi})));
static_assert(eqx::equals(eqx::arccos(-0.866025),
    std::make_pair(eqx::Radians<double>{eqx::c_5Pi6<double>},
        eqx::Radians<double>{eqx::c_7Pi6<double>})));
static_assert(eqx::equals(eqx::arccos(-0.707107),
    std::make_pair(eqx::Radians<double>{eqx::c_3Pi4<double>},
        eqx::Radians<double>{eqx::c_5Pi4<double>})));
static_assert(eqx::equals(eqx::arccos(-0.5),
    std::make_pair(eqx::Radians<double>{eqx::c_2Pi3<double>},
        eqx::Radians<double>{eqx::c_4Pi3<double>})));
static_assert(eqx::equals(eqx::arccos(0.5),
    std::make_pair(eqx::Radians<double>{eqx::c_Pi3<double>},
        eqx::Radians<double>{eqx::c_5Pi3<double>})));
static_assert(eqx::equals(eqx::arccos(0.707107),
    std::make_pair(eqx::Radians<double>{eqx::c_Pi4<double>},
        eqx::Radians<double>{eqx::c_7Pi4<double>})));
static_assert(eqx::equals(eqx::arccos(0.866025),
    std::make_pair(eqx::Radians<double>{eqx::c_Pi6<double>},
        eqx::Radians<double>{eqx::c_11Pi6<double>})));
static_assert(eqx::equals(eqx::arccos(1.0), std::make_pair(0.0_rad, 0.0_rad)));
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
