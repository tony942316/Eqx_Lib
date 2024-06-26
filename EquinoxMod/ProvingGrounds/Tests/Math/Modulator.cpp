export module Eqx.Tests.Math:Modulator;

import Eqx.Stdm;
import Equinox.Math.Core;
import Equinox.Math.Modulator;

constexpr auto rF = eqx::Radians<float>{stdm::numbers::pi_v<float>};
constexpr auto r = eqx::Radians<double>{stdm::numbers::pi_v<double>};
constexpr auto rL = eqx::Radians<long double>{stdm::numbers::pi_v<long double>};

static_assert(rF.get() == stdm::numbers::pi_v<float>);
static_assert(r.get() == stdm::numbers::pi_v<double>);
static_assert(rL.get() == stdm::numbers::pi_v<long double>);

constexpr auto r0 = eqx::Radians<double>{0.0};
constexpr auto r1 = eqx::Radians<double>{stdm::numbers::pi * 3.0};
constexpr auto r2 = eqx::Radians<double>{eqx::c_Pi2<double> * 5.0};
constexpr auto r3 = eqx::Radians<double>{eqx::c_2Pi<double>};
constexpr auto r4 = eqx::Radians<double>{-stdm::numbers::pi};
constexpr auto r5 = eqx::Radians<double>{-eqx::c_11Pi6<double>};
constexpr auto r6 = eqx::Radians<double>{-eqx::c_2Pi<double>};

static_assert(r0.get() == 0.0);
static_assert(r1.get() == stdm::numbers::pi);
static_assert(r2.get() == eqx::c_Pi2<double>);
static_assert(r3.get() == 0.0);
static_assert(r4.get() == stdm::numbers::pi);
static_assert(eqx::equals(r5.get(), eqx::c_Pi6<double>));
static_assert(eqx::equals(r6.get(), 0.0));

static_assert(eqx::equals(rF, rF));
static_assert(eqx::equals(r, r));
static_assert(eqx::equals(rL, rL));
static_assert(eqx::equals(r0, r0));
static_assert(eqx::equals(r1, r1));
static_assert(eqx::equals(r2, r2));
static_assert(eqx::equals(r3, r3));
static_assert(eqx::equals(r4, r4));
static_assert(eqx::equals(r5, r5));
static_assert(eqx::equals(r6, r6));

static_assert(!eqx::equals(r0, r1));
static_assert(!eqx::equals(r0, r2));
static_assert(eqx::equals(r0, r3));
static_assert(!eqx::equals(r0, r4));
static_assert(!eqx::equals(r0, r5));
static_assert(eqx::equals(r0, r6));
static_assert(!eqx::equals(r1, r2));
static_assert(!eqx::equals(r1, r3));
static_assert(eqx::equals(r1, r4));
static_assert(!eqx::equals(r1, r5));
static_assert(!eqx::equals(r1, r6));
static_assert(!eqx::equals(r2, r3));
static_assert(!eqx::equals(r2, r4));
static_assert(!eqx::equals(r2, r5));
static_assert(!eqx::equals(r2, r6));
static_assert(!eqx::equals(r3, r4));
static_assert(!eqx::equals(r3, r5));
static_assert(eqx::equals(r3, r6));
static_assert(!eqx::equals(r4, r5));
static_assert(!eqx::equals(r4, r6));
static_assert(!eqx::equals(r5, r6));

constexpr auto dF = eqx::Degrees<float>{180.0F};
constexpr auto d = eqx::Degrees<double>{180.0};
constexpr auto dL = eqx::Degrees<long double>{180.0L};

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
static_assert(dF.get() == 180.0F);
static_assert(d.get() == 180.0);
static_assert(dL.get() == 180.0L);
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

constexpr auto d0 = eqx::Degrees<double>{0.0};
constexpr auto d1 = eqx::Degrees<double>{540.0};
constexpr auto d2 = eqx::Degrees<double>{450.0};
constexpr auto d3 = eqx::Degrees<double>{360.0};
constexpr auto d4 = eqx::Degrees<double>{-180.0};
constexpr auto d5 = eqx::Degrees<double>{-30.0};
constexpr auto d6 = eqx::Degrees<double>{-360.0};

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
static_assert(d0.get() == 0.0);
static_assert(d1.get() == 180.0);
static_assert(d2.get() == 90.0);
static_assert(d3.get() == 0.0);
static_assert(d4.get() == 180.0);
static_assert(d5.get() == 330.0);
static_assert(d6.get() == 0.0);
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

static_assert(eqx::equals(dF, dF));
static_assert(eqx::equals(d, d));
static_assert(eqx::equals(dL, dL));
static_assert(eqx::equals(d0, d0));
static_assert(eqx::equals(d1, d1));
static_assert(eqx::equals(d2, d2));
static_assert(eqx::equals(d3, d3));
static_assert(eqx::equals(d4, d4));
static_assert(eqx::equals(d5, d5));
static_assert(eqx::equals(d6, d6));

static_assert(!eqx::equals(d0, d1));
static_assert(!eqx::equals(d0, d2));
static_assert(eqx::equals(d0, d3));
static_assert(!eqx::equals(d0, d4));
static_assert(!eqx::equals(d0, d5));
static_assert(eqx::equals(d0, d6));
static_assert(!eqx::equals(d1, d2));
static_assert(!eqx::equals(d1, d3));
static_assert(eqx::equals(d1, d4));
static_assert(!eqx::equals(d1, d5));
static_assert(!eqx::equals(d1, d6));
static_assert(!eqx::equals(d2, d3));
static_assert(!eqx::equals(d2, d4));
static_assert(!eqx::equals(d2, d5));
static_assert(!eqx::equals(d2, d6));
static_assert(!eqx::equals(d3, d4));
static_assert(!eqx::equals(d3, d5));
static_assert(eqx::equals(d3, d6));
static_assert(!eqx::equals(d4, d5));
static_assert(!eqx::equals(d4, d6));
static_assert(!eqx::equals(d5, d6));

static_assert(eqx::equals(stdm::make_pair(d0, d0), stdm::make_pair(d0, d0)));
