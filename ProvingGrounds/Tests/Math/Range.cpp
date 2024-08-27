module Eqx.Tests.Math:Range;

import <Eqx/std.hpp>;

import Eqx.Lib.Math.Range;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
static_assert(eqx::median(std::vector<int>{ 1 }) == 1.0);
static_assert(eqx::median(std::vector<unsigned int>{ 1U }) == 1.0);
static_assert(eqx::median(std::vector<long>{ 1L }) == 1.0);
static_assert(eqx::median(std::vector<unsigned long>{ 1UL }) == 1.0);
static_assert(eqx::median(std::vector<long long>{ 1LL }) == 1.0);
static_assert(eqx::median(std::vector<unsigned long long>{ 1ULL }) == 1.0);
static_assert(eqx::median(std::vector<float>{ 1.0F }) == 1.0);
static_assert(eqx::median(std::vector<double>{ 1.0 }) == 1.0);
static_assert(eqx::median(std::vector<long double>{ 1.0L }) == 1.0);
static_assert(eqx::median(std::vector<int>{ 0, 1 }) == 0.5);
static_assert(eqx::median(std::vector<int>{ 0, 1, 2 }) == 1.0);
static_assert(eqx::median(std::vector<int>{ 0, 1, 2, 3 }) == 1.5);
static_assert(eqx::median(std::vector<int>{ 0, 1, 2, 3, 4 }) == 2.0);
static_assert(eqx::median(std::array<int, 1>{ 1 }) == 1.0);
static_assert(eqx::median(std::array<unsigned int, 1>{ 1U }) == 1.0);
static_assert(eqx::median(std::array<long, 1>{ 1L }) == 1.0);
static_assert(eqx::median(std::array<unsigned long, 1>{ 1UL }) == 1.0);
static_assert(eqx::median(std::array<long long, 1>{ 1LL }) == 1.0);
static_assert(eqx::median(std::array<unsigned long long, 1>{ 1ULL }) == 1.0);
static_assert(eqx::median(std::array<float, 1>{ 1.0F }) == 1.0);
static_assert(eqx::median(std::array<double, 1>{ 1.0 }) == 1.0);
static_assert(eqx::median(std::array<long double, 1>{ 1.0L }) == 1.0);
static_assert(eqx::median(std::array<int, 2>{ 0, 1 }) == 0.5);
static_assert(eqx::median(std::array<int, 3>{ 0, 1, 2 }) == 1.0);
static_assert(eqx::median(std::array<int, 4>{ 0, 1, 2, 3 }) == 1.5);
static_assert(eqx::median(std::array<int, 5>{ 0, 1, 2, 3, 4 }) == 2.0);

static_assert(eqx::average(std::vector<int>{ 1 }) == 1.0);
static_assert(eqx::average(std::vector<unsigned int>{ 1U }) == 1.0);
static_assert(eqx::average(std::vector<long>{ 1L }) == 1.0);
static_assert(eqx::average(std::vector<unsigned long>{ 1UL }) == 1.0);
static_assert(eqx::average(std::vector<long long>{ 1LL }) == 1.0);
static_assert(eqx::average(std::vector<unsigned long long>{ 1ULL }) == 1.0);
static_assert(eqx::average(std::vector<float>{ 1.0F }) == 1.0);
static_assert(eqx::average(std::vector<double>{ 1.0 }) == 1.0);
static_assert(eqx::average(std::vector<long double>{ 1.0L }) == 1.0);
static_assert(eqx::average(std::vector<int>{ 0, 1 }) == 0.5);
static_assert(eqx::average(std::vector<int>{ 0, 1, 2 }) == 1.0);
static_assert(eqx::average(std::vector<int>{ 0, 1, 2, 3 }) == 1.5);
static_assert(eqx::average(std::vector<int>{ 0, 1, 2, 3, 4 }) == 2.0);
static_assert(eqx::average(std::array<int, 1>{ 1 }) == 1.0);
static_assert(eqx::average(std::array<unsigned int, 1>{ 1U }) == 1.0);
static_assert(eqx::average(std::array<long, 1>{ 1L }) == 1.0);
static_assert(eqx::average(std::array<unsigned long, 1>{ 1UL }) == 1.0);
static_assert(eqx::average(std::array<long long, 1>{ 1LL }) == 1.0);
static_assert(eqx::average(std::array<unsigned long long, 1>{ 1ULL }) == 1.0);
static_assert(eqx::average(std::array<float, 1>{ 1.0F }) == 1.0);
static_assert(eqx::average(std::array<double, 1>{ 1.0 }) == 1.0);
static_assert(eqx::average(std::array<long double, 1>{ 1.0L }) == 1.0);
static_assert(eqx::average(std::array<int, 2>{ 0, 1 }) == 0.5);
static_assert(eqx::average(std::array<int, 3>{ 0, 1, 2 }) == 1.0);
static_assert(eqx::average(std::array<int, 4>{ 0, 1, 2, 3 }) == 1.5);
static_assert(eqx::average(std::array<int, 5>{ 0, 1, 2, 3, 4 }) == 2.0);
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
