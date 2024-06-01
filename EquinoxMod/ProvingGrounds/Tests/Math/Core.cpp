module Eqx.Tests.Math:Core;

import Eqx.Stdm;
import Equinox.Math.Core;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
static_assert(eqx::abs(0) == 0);
static_assert(eqx::abs(-0) == 0);
static_assert(eqx::abs(1) == 1);
static_assert(eqx::abs(-1) == 1);
static_assert(eqx::abs(5) == 5);
static_assert(eqx::abs(-5) == 5);
static_assert(eqx::abs(5L) == 5L);
static_assert(eqx::abs(-5L) == 5L);
static_assert(eqx::abs(5LL) == 5LL);
static_assert(eqx::abs(-5LL) == 5LL);
static_assert(eqx::abs(5U) == 5U);
static_assert(eqx::abs(5UL) == 5UL);
static_assert(eqx::abs(5ULL) == 5ULL);
static_assert(eqx::abs(0.0) == 0.0);
static_assert(eqx::abs(-0.0) == 0.0);
static_assert(eqx::abs(0.1) == 0.1);
static_assert(eqx::abs(-0.1) == 0.1);
static_assert(eqx::abs(5.5F) == 5.5F);
static_assert(eqx::abs(-5.5F) == 5.5F);
static_assert(eqx::abs(5.5) == 5.5);
static_assert(eqx::abs(-5.5) == 5.5);
static_assert(eqx::abs(5.5L) == 5.5L);
static_assert(eqx::abs(-5.5L) == 5.5L);
static_assert(eqx::abs(100.05) == 100.05);
static_assert(eqx::abs(-100.05) == 100.05);
static_assert(eqx::abs(stdm::numeric_limits<int>::lowest() + 1)
    == (stdm::numeric_limits<int>::min() + 1) * -1);
static_assert(eqx::abs(stdm::numeric_limits<int>::max())
    == stdm::numeric_limits<int>::max());
static_assert(eqx::abs(stdm::numeric_limits<double>::lowest())
    == stdm::numeric_limits<double>::max());

static_assert(eqx::equals(5, 5));
static_assert(eqx::equals(stdm::vector<int>{ 1, 2 },
    stdm::vector<int>{ 1, 2 }));
static_assert(eqx::equals(stdm::pair<stdm::string, int>("Hello"s, 5),
    stdm::pair<stdm::string, int>("Hello"s, 5)));
static_assert(eqx::equals(stdm::make_pair(5.000001, 0.0),
    stdm::make_pair(5.000002, 0.0)));
static_assert(!eqx::equals(stdm::make_pair(5.00001, 0.0),
    stdm::make_pair(5.00002, 0.0)));
static_assert(eqx::equals(0.01, 0.01));
static_assert(!eqx::equals(1.01, 0.01));
static_assert(!eqx::equals(0.01, 0.02));
static_assert(!eqx::equals(0.01, 0.02, 0.01));
static_assert(eqx::equals(0.01, 0.02, 0.1));
static_assert(!eqx::equals(0.000001, 0.0000001, 0.0000001));
static_assert(!eqx::equals(1000.0, 1100.0, 100.0));
static_assert(eqx::equals(1000.0, 1099.0, 100.0));
static_assert(eqx::equals(5.5F, 5.5F));
static_assert(eqx::equals(5.5, 5.5));
static_assert(eqx::equals(5.5L, 5.5L));
static_assert(eqx::equals(5.000001, 5.000002));
static_assert(!eqx::equals(5.00001, 5.00002));
static_assert(eqx::equals(5.00001, 5.00002, 0.01));
static_assert(eqx::equals(151.05, 125.22, 50.0));
static_assert(!eqx::equals(151.05, 125.22, 10.0));

static_assert(eqx::isPositive(5));
static_assert(!eqx::isPositive(-5));
static_assert(!eqx::isNegative(5));
static_assert(eqx::isNegative(-5));
static_assert(eqx::isEven(2));
static_assert(!eqx::isEven(3));
static_assert(!eqx::isOdd(2));
static_assert(eqx::isOdd(3));

static_assert(eqx::distance(1, 5) == 4);
static_assert(eqx::distance(-10, 10) == 20);
static_assert(eqx::distance(0, 0) == 0);
static_assert(eqx::distance(0, 1) == 1);
static_assert(eqx::distance(1, 0) == 1);
static_assert(eqx::distance(-1, 1) == 2);
static_assert(eqx::distance(0.0, 0.0) == 0.0);
static_assert(eqx::distance(0.0, 1.0) == 1.0);
static_assert(eqx::distance(1.0, 0.0) == 1.0);
static_assert(eqx::distance(-1.0, 1.0) == 2.0);
static_assert(eqx::distance(-100, 250) == 350);
static_assert(eqx::distance(-250, 100) == 350);
static_assert(eqx::distance(0, 100'000) == 100'000);
static_assert(eqx::distance(-100.0, 250.0) == 350.0);
static_assert(eqx::distance(-250.0, 100.0) == 350.0);
static_assert(eqx::distance(0.0, 100'000.0) == 100'000.0);
static_assert(eqx::distance(1.5, 10.2) == 8.7);
static_assert(eqx::distance(-10.2, -1.5) == 8.7);
static_assert(eqx::distance(-1.054689, 1.5047896) == 2.5594786000000003);
static_assert(eqx::equals(eqx::distance(15.3F, -33.1F), 48.4F));
static_assert(eqx::distance(-22.5F, 5.7F) == 28.2F);
static_assert(eqx::distance(0U, 0U) == 0U);
static_assert(eqx::distance(0U, 1U) == 1U);
static_assert(eqx::distance(0U, 100'000U) == 100'000U);

static_assert(eqx::trunc(1) == 1);
static_assert(eqx::trunc(1U) == 1U);
static_assert(eqx::trunc(1L) == 1L);
static_assert(eqx::trunc(1UL) == 1UL);
static_assert(eqx::trunc(1LL) == 1LL);
static_assert(eqx::trunc(1ULL) == 1ULL);
static_assert(eqx::trunc(1.05F) == 1.0F);
static_assert(eqx::trunc(1.05) == 1.0);
static_assert(eqx::trunc(1.05L) == 1.0L);
static_assert(eqx::trunc(-1.05) == -1.0);

static_assert(eqx::floor(1) == 1);
static_assert(eqx::floor(1U) == 1U);
static_assert(eqx::floor(1L) == 1L);
static_assert(eqx::floor(1UL) == 1UL);
static_assert(eqx::floor(1LL) == 1LL);
static_assert(eqx::floor(1ULL) == 1ULL);
static_assert(eqx::floor(1.05F) == 1.0F);
static_assert(eqx::floor(1.05) == 1.0);
static_assert(eqx::floor(1.05L) == 1.0L);
static_assert(eqx::floor(-1.05) == -2.0);

static_assert(eqx::ceil(1) == 1);
static_assert(eqx::ceil(1U) == 1U);
static_assert(eqx::ceil(1L) == 1L);
static_assert(eqx::ceil(1UL) == 1UL);
static_assert(eqx::ceil(1LL) == 1LL);
static_assert(eqx::ceil(1ULL) == 1ULL);
static_assert(eqx::ceil(1.05F) == 2.0F);
static_assert(eqx::ceil(1.05) == 2.0);
static_assert(eqx::ceil(1.05L) == 2.0L);
static_assert(eqx::ceil(-1.05) == -1.0);

static_assert(eqx::factorial(0) == 1.0);
static_assert(eqx::factorial(1) == 1.0);
static_assert(eqx::factorial(1U) == 1.0);
static_assert(eqx::factorial(1L) == 1.0);
static_assert(eqx::factorial(1UL) == 1.0);
static_assert(eqx::factorial(1LL) == 1.0);
static_assert(eqx::factorial(1ULL) == 1.0);
static_assert(eqx::factorial(2) == 2.0);
static_assert(eqx::factorial(5) == 120.0);

static_assert(eqx::pow(0, 1) == 0);
static_assert(eqx::pow(0, 5) == 0);
static_assert(eqx::pow(1, 0) == 1);
static_assert(eqx::pow(5, 0) == 1);
static_assert(eqx::pow(2, 3) == 8);
static_assert(eqx::pow(2U, 3U) == 8U);
static_assert(eqx::pow(2L, 3L) == 8L);
static_assert(eqx::pow(2UL, 3UL) == 8UL);
static_assert(eqx::pow(2LL, 3LL) == 8LL);
static_assert(eqx::pow(2ULL, 3ULL) == 8ULL);
static_assert(eqx::pow(2.0F, 3.0F) == 8.0F);
static_assert(eqx::pow(2.0, 3.0) == 8.0);
static_assert(eqx::pow(2.0L, 3.0L) == 8.0L);

static_assert(eqx::equals(eqx::fmod(1.0F, 10.0F), 1.0F));
static_assert(eqx::equals(eqx::fmod(1.0, 10.0), 1.0));
static_assert(eqx::equals(eqx::fmod(1.0L, 10.0L), 1.0L));
static_assert(eqx::equals(eqx::fmod(0.0, 5.5), 0.0));
static_assert(eqx::equals(eqx::fmod(2.5, 5.5), 2.5));
static_assert(eqx::equals(eqx::fmod(5.5, 5.5), 0.0));
static_assert(eqx::equals(eqx::fmod(8.0, 5.5), 2.5));
static_assert(eqx::equals(eqx::fmod(11.0, 5.5), 0.0));
static_assert(eqx::equals(eqx::fmod(-2.5, 5.5), -2.5));
static_assert(eqx::equals(eqx::fmod(-5.5, 5.5), 0.0));
static_assert(eqx::equals(eqx::fmod(-8.0, 5.5), -2.5));
static_assert(eqx::equals(eqx::fmod(-11.0, 5.5), 0.0));

static_assert(eqx::equals(eqx::sqrt(1.0F), 1.0F));
static_assert(eqx::equals(eqx::sqrt(1.0), 1.0));
static_assert(eqx::equals(eqx::sqrt(1.0L), 1.0L));
static_assert(eqx::equals(eqx::sqrt(0.0), 0.0));
static_assert(eqx::equals(eqx::sqrt(0.0001), 0.01));
static_assert(eqx::equals(eqx::sqrt(0.1), 0.31622776));
static_assert(eqx::equals(eqx::sqrt(0.5), 0.7071067));
static_assert(eqx::equals(eqx::sqrt(2.0), stdm::numbers::sqrt2));
static_assert(eqx::equals(eqx::sqrt(stdm::numbers::e), 1.64872127));
static_assert(eqx::equals(eqx::sqrt(3.0), stdm::numbers::sqrt3));
static_assert(eqx::equals(eqx::sqrt(stdm::numbers::pi), 1.77245385));
static_assert(eqx::equals(eqx::sqrt(4.0), 2.0));
static_assert(eqx::equals(eqx::sqrt(9.0), 3.0));
static_assert(eqx::equals(eqx::sqrt(10.0), 3.16227766));
static_assert(eqx::equals(eqx::sqrt(15.0), 3.8729833));
static_assert(eqx::equals(eqx::sqrt(16.0), 4.0));
static_assert(eqx::equals(eqx::sqrt(21.0), 4.58257569));
static_assert(eqx::equals(eqx::sqrt(10'000.0), 100.0));
static_assert(eqx::equals(eqx::sqrt(100'000'000.0), 10'000.0));
static_assert(eqx::equals(eqx::sqrt(5'489'632'148'524.0), 2'342'996.4038649));
static_assert(eqx::equals(eqx::sqrt(10'000'000'000'000'000.0), 100'000'000.0));
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
