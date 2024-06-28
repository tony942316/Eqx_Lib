module Eqx.Tests.Rectangle:Core;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Math.Core;
import Equinox.Point;
import Equinox.Rectangle;

using namespace eqx::literals;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
constexpr auto rect0DI = eqx::Rectangle<int>{};
constexpr auto rect0DF = eqx::Rectangle<float>{};
constexpr auto rect0D = eqx::Rectangle<double>{};
constexpr auto rect0DL = eqx::Rectangle<long double>{};

constexpr auto rect0I = eqx::Rectangle<int>{0, 0, 0, 0};
constexpr auto rect0F = eqx::Rectangle<float>{0.0F, 0.0F, 0.0F, 0.0F};
constexpr auto rect0 = eqx::Rectangle<double>{0.0, 0.0, 0.0, 0.0};
constexpr auto rect0L = eqx::Rectangle<long double>{0.0L, 0.0L, 0.0L, 0.0L};
constexpr auto rect1 = eqx::Rectangle<double>{1.0, 1.0, 1.0, 1.0};
constexpr auto rect2 = eqx::Rectangle<double>{-10.0, -10.0, 3.0, 15.0};
constexpr auto rect3 = eqx::Rectangle<double>{6.123, -9.874, 6.548, 3.698};
constexpr auto rect4 = eqx::Rectangle<double>{eqx::Point<double>{0.0, 0.0},
    eqx::Point<double>{10.0, -10.0}};
constexpr auto rect5 = eqx::Rectangle<double>{eqx::Point<double>{-22.5, 15.3},
    eqx::Point<double>{5.7, -33.1}};

constexpr auto point1 = eqx::Point<double>{1.5, 0.0};
constexpr auto point2 = eqx::Point<double>{-9.0, -20.0};
constexpr auto point3 = eqx::Point<double>{10, -12.5};

static_assert(rect0DI.x == 0 && rect0DI.y == 0 && rect0DI.w == 0
    && rect0DI.h == 0);
static_assert(rect0DF.x == 0.0F && rect0DF.y == 0.0F && rect0DF.w == 0.0F
    && rect0DF.h == 0.0F);
static_assert(rect0D.x == 0.0 && rect0D.y == 0.0 && rect0D.w == 0.0
    && rect0D.h == 0.0);
static_assert(rect0DL.x == 0.0L && rect0DL.y == 0.0L && rect0DL.w == 0.0L
    && rect0DL.h == 0.0L);

static_assert(rect0I.x == 0 && rect0I.y == 0 && rect0I.w == 0
    && rect0I.h == 0);
static_assert(rect0F.x == 0.0F && rect0F.y == 0.0F && rect0F.w == 0.0F
    && rect0F.h == 0.0F);
static_assert(rect0.x == 0.0 && rect0.y == 0.0 && rect0.w == 0.0
    && rect0.h == 0.0);
static_assert(rect0L.x == 0.0L && rect0L.y == 0.0L && rect0L.w == 0.0L
    && rect0L.h == 0.0L);
static_assert(rect1.x == 1.0 && rect1.y == 1.0 && rect1.w == 1.0
    && rect1.h == 1.0);
static_assert(rect2.x == -10.0 && rect2.y == -10.0 && rect2.w == 3.0
    && rect2.h == 15.0);
static_assert(rect3.x == 6.123 && rect3.y == -9.874 && rect3.w == 6.548
    && rect3.h == 3.698);
static_assert(rect4.x == 0.0 && rect4.y == 0.0 && rect4.w == 10.0
    && rect4.h == 10.0);
static_assert(rect5.x == -22.5 && rect5.y == 15.3 && rect5.w == 28.2
    && eqx::equals(rect5.h, 48.4));

// NOLINTBEGIN(misc-redundant-expression)
static_assert(rect0I == rect0I);
static_assert(rect0F == rect0F);
static_assert(rect0 == rect0);
static_assert(rect0L == rect0L);
static_assert(rect1 == rect1);
static_assert(rect2 == rect2);
static_assert(rect3 == rect3);
static_assert(rect4 == rect4);
static_assert(rect5 == rect5);
// NOLINTEND(misc-redundant-expression)

static_assert(rect0 != rect1);
static_assert(rect0 != rect2);
static_assert(rect0 != rect3);
static_assert(rect0 != rect4);
static_assert(rect0 != rect5);
static_assert(rect1 != rect2);
static_assert(rect1 != rect3);
static_assert(rect1 != rect4);
static_assert(rect1 != rect5);
static_assert(rect2 != rect3);
static_assert(rect2 != rect4);
static_assert(rect2 != rect5);
static_assert(rect3 != rect4);
static_assert(rect3 != rect5);
static_assert(rect4 != rect5);

static_assert(eqx::equals(rect0I, rect0I));
static_assert(eqx::equals(rect0F, rect0F));
static_assert(eqx::equals(rect0, rect0));
static_assert(eqx::equals(rect0L, rect0L));
static_assert(eqx::equals(rect1, rect1));
static_assert(eqx::equals(rect2, rect2));
static_assert(eqx::equals(rect3, rect3));
static_assert(eqx::equals(rect4, rect4));
static_assert(eqx::equals(rect5, rect5));

static_assert(eqx::equals(rect0I.getTopLeftPoint(), eqx::Point<int>{0, 0}));
static_assert(eqx::equals(rect0I.getTopRightPoint(), eqx::Point<int>{0, 0}));
static_assert(eqx::equals(rect0I.getBottomLeftPoint(), eqx::Point<int>{0, 0}));
static_assert(eqx::equals(rect0I.getBottomRightPoint(), eqx::Point<int>{0, 0}));
static_assert(eqx::equals(rect0I.getCenterPoint(), eqx::Point<int>{0, 0}));
static_assert(eqx::equals(rect0F.getTopLeftPoint(),
    eqx::Point<float>{0.0F, 0.0F}));
static_assert(eqx::equals(rect0F.getTopRightPoint(),
    eqx::Point<float>{0.0F, 0.0F}));
static_assert(eqx::equals(rect0F.getBottomLeftPoint(),
    eqx::Point<float>{0.0F, 0.0F}));
static_assert(eqx::equals(rect0F.getBottomRightPoint(),
    eqx::Point<float>{0.0F, 0.0F}));
static_assert(eqx::equals(rect0F.getCenterPoint(),
    eqx::Point<float>{0.0F, 0.0F}));
static_assert(eqx::equals(rect0.getTopLeftPoint(),
    eqx::Point<double>{0.0, 0.0}));
static_assert(eqx::equals(rect0.getTopRightPoint(),
    eqx::Point<double>{0.0, 0.0}));
static_assert(eqx::equals(rect0.getBottomLeftPoint(),
    eqx::Point<double>{0.0, 0.0}));
static_assert(eqx::equals(rect0.getBottomRightPoint(),
    eqx::Point<double>{0.0, 0.0}));
static_assert(eqx::equals(rect0.getCenterPoint(),
    eqx::Point<double>{0.0, 0.0}));
static_assert(eqx::equals(rect0L.getTopLeftPoint(),
    eqx::Point<long double>{0.0L, 0.0L}));
static_assert(eqx::equals(rect0L.getTopRightPoint(),
    eqx::Point<long double>{0.0L, 0.0L}));
static_assert(eqx::equals(rect0L.getBottomLeftPoint(),
    eqx::Point<long double>{0.0L, 0.0L}));
static_assert(eqx::equals(rect0L.getBottomRightPoint(),
    eqx::Point<long double>{0.0L, 0.0L}));
static_assert(eqx::equals(rect0L.getCenterPoint(),
    eqx::Point<long double>{0.0L, 0.0L}));
static_assert(eqx::equals(rect1.getTopLeftPoint(),
    eqx::Point<double>{1.0, 1.0}));
static_assert(eqx::equals(rect1.getTopRightPoint(),
    eqx::Point<double>{2.0, 1.0}));
static_assert(eqx::equals(rect1.getBottomLeftPoint(),
    eqx::Point<double>{1.0, 0.0}));
static_assert(eqx::equals(rect1.getBottomRightPoint(),
    eqx::Point<double>{2.0, 0.0}));
static_assert(eqx::equals(rect1.getCenterPoint(),
    eqx::Point<double>{1.5, 0.5}));
static_assert(eqx::equals(rect2.getTopLeftPoint(),
    eqx::Point<double>{-10.0, -10.0}));
static_assert(eqx::equals(rect2.getTopRightPoint(),
    eqx::Point<double>{-7.0, -10.0}));
static_assert(eqx::equals(rect2.getBottomLeftPoint(),
    eqx::Point<double>{-10.0, -25.0}));
static_assert(eqx::equals(rect2.getBottomRightPoint(),
    eqx::Point<double>{-7.0, -25.0}));
static_assert(eqx::equals(rect2.getCenterPoint(),
    eqx::Point<double>{-8.5, -17.5}));
static_assert(eqx::equals(rect3.getTopLeftPoint(),
    eqx::Point<double>{6.123, -9.874}));
static_assert(eqx::equals(rect3.getTopRightPoint(),
    eqx::Point<double>{12.671, -9.874}));
static_assert(eqx::equals(rect3.getBottomLeftPoint(),
    eqx::Point<double>{6.123, -13.572}));
static_assert(eqx::equals(rect3.getBottomRightPoint(),
    eqx::Point<double>{12.671, -13.572}));
static_assert(eqx::equals(rect3.getCenterPoint(),
    eqx::Point<double>{9.397, -11.723}));
static_assert(eqx::equals(rect4.getTopLeftPoint(),
    eqx::Point<double>{0.0, 0.0}));
static_assert(eqx::equals(rect4.getTopRightPoint(),
    eqx::Point<double>{10.0, 0.0}));
static_assert(eqx::equals(rect4.getBottomLeftPoint(),
    eqx::Point<double>{0.0, -10.0}));
static_assert(eqx::equals(rect4.getBottomRightPoint(),
    eqx::Point<double>{10.0, -10.0}));
static_assert(eqx::equals(rect4.getCenterPoint(),
    eqx::Point<double>{5.0, -5.0}));
static_assert(eqx::equals(rect5.getTopLeftPoint(),
    eqx::Point<double>{-22.5, 15.3}));
static_assert(eqx::equals(rect5.getTopRightPoint(),
    eqx::Point<double>{5.7, 15.3}));
static_assert(eqx::equals(rect5.getBottomLeftPoint(),
    eqx::Point<double>{-22.5, -33.1}));
static_assert(eqx::equals(rect5.getBottomRightPoint(),
    eqx::Point<double>{5.7, -33.1}));
static_assert(eqx::equals(rect5.getCenterPoint(),
    eqx::Point<double>{-8.4, -8.9}));

static_assert(rect1.getEmplaceCenter(rect0) == rect1.getCenterPoint());
static_assert(rect2.getEmplaceCenter(rect0) == rect2.getCenterPoint());
static_assert(rect2.getEmplaceCenter(rect1)
    == eqx::Point<double>{-9.0, -17.0});
static_assert(rect3.getEmplaceCenter(rect0) == rect3.getCenterPoint());
static_assert(rect3.getEmplaceCenter(rect1)
    == eqx::Point<double>{8.897, -11.223});
static_assert(rect4.getEmplaceCenter(rect0) == rect4.getCenterPoint());
static_assert(rect4.getEmplaceCenter(rect1)
    == eqx::Point<double>{4.5, -4.5});
static_assert(rect4.getEmplaceCenter(rect3)
    == eqx::Point<double>{1.726, -3.151});
static_assert(rect5.getEmplaceCenter(rect0) == rect5.getCenterPoint());
static_assert(rect5.getEmplaceCenter(rect1)
    == eqx::Point<double>{-8.9, -8.4});
static_assert(rect5.getEmplaceCenter(rect2)
    == eqx::Point<double>{-9.9, -1.4});
static_assert(rect5.getEmplaceCenter(rect3)
    == eqx::Point<double>{-11.674, -7.051});
static_assert(rect5.getEmplaceCenter(rect4)
    == eqx::Point<double>{-13.4, -3.9});

static_assert(eqx::intersect(rect0, rect0));
static_assert(!eqx::intersect(rect0, rect1));
static_assert(!eqx::intersect(rect0, rect2));
static_assert(!eqx::intersect(rect0, rect3));
static_assert(eqx::intersect(rect0, rect4));
static_assert(eqx::intersect(rect0, rect5));
static_assert(eqx::intersect(rect1, rect1));
static_assert(!eqx::intersect(rect1, rect2));
static_assert(!eqx::intersect(rect1, rect3));
static_assert(eqx::intersect(rect1, rect4));
static_assert(eqx::intersect(rect1, rect5));
static_assert(eqx::intersect(rect2, rect2));
static_assert(!eqx::intersect(rect2, rect3));
static_assert(!eqx::intersect(rect2, rect4));
static_assert(eqx::intersect(rect2, rect5));
static_assert(eqx::intersect(rect3, rect3));
static_assert(eqx::intersect(rect3, rect4));
static_assert(!eqx::intersect(rect3, rect5));
static_assert(eqx::intersect(rect4, rect4));
static_assert(eqx::intersect(rect4, rect5));
static_assert(eqx::intersect(rect5, rect5));

static_assert(!eqx::intersect(rect0, point1));
static_assert(!eqx::intersect(rect0, point2));
static_assert(!eqx::intersect(rect0, point3));
static_assert(eqx::intersect(rect1, point1));
static_assert(!eqx::intersect(rect1, point2));
static_assert(!eqx::intersect(rect1, point3));
static_assert(!eqx::intersect(rect2, point1));
static_assert(eqx::intersect(rect2, point2));
static_assert(!eqx::intersect(rect2, point3));
static_assert(!eqx::intersect(rect3, point1));
static_assert(!eqx::intersect(rect3, point2));
static_assert(eqx::intersect(rect3, point3));
static_assert(eqx::intersect(rect4, point1));
static_assert(!eqx::intersect(rect4, point2));
static_assert(!eqx::intersect(rect4, point3));
static_assert(eqx::intersect(rect5, point1));
static_assert(eqx::intersect(rect5, point2));
static_assert(!eqx::intersect(rect5, point3));

static_assert(!eqx::intersectExclusive(rect0, rect0));
static_assert(!eqx::intersectExclusive(rect0, rect1));
static_assert(!eqx::intersectExclusive(rect0, rect2));
static_assert(!eqx::intersectExclusive(rect0, rect3));
static_assert(!eqx::intersectExclusive(rect0, rect4));
static_assert(eqx::intersectExclusive(rect0, rect5));
static_assert(eqx::intersectExclusive(rect1, rect1));
static_assert(!eqx::intersectExclusive(rect1, rect2));
static_assert(!eqx::intersectExclusive(rect1, rect3));
static_assert(!eqx::intersectExclusive(rect1, rect4));
static_assert(eqx::intersectExclusive(rect1, rect5));
static_assert(eqx::intersectExclusive(rect2, rect2));
static_assert(!eqx::intersectExclusive(rect2, rect3));
static_assert(!eqx::intersectExclusive(rect2, rect4));
static_assert(eqx::intersectExclusive(rect2, rect5));
static_assert(eqx::intersectExclusive(rect3, rect3));
static_assert(eqx::intersectExclusive(rect3, rect4));
static_assert(!eqx::intersectExclusive(rect3, rect5));
static_assert(eqx::intersectExclusive(rect4, rect4));
static_assert(eqx::intersectExclusive(rect4, rect5));
static_assert(eqx::intersectExclusive(rect5, rect5));

static_assert(!eqx::intersectExclusive(rect0, point1));
static_assert(!eqx::intersectExclusive(rect0, point2));
static_assert(!eqx::intersectExclusive(rect0, point3));
static_assert(!eqx::intersectExclusive(rect1, point1));
static_assert(!eqx::intersectExclusive(rect1, point2));
static_assert(!eqx::intersectExclusive(rect1, point3));
static_assert(!eqx::intersectExclusive(rect2, point1));
static_assert(eqx::intersectExclusive(rect2, point2));
static_assert(!eqx::intersectExclusive(rect2, point3));
static_assert(!eqx::intersectExclusive(rect3, point1));
static_assert(!eqx::intersectExclusive(rect3, point2));
static_assert(eqx::intersectExclusive(rect3, point3));
static_assert(!eqx::intersectExclusive(rect4, point1));
static_assert(!eqx::intersectExclusive(rect4, point2));
static_assert(!eqx::intersectExclusive(rect4, point3));
static_assert(eqx::intersectExclusive(rect5, point1));
static_assert(eqx::intersectExclusive(rect5, point2));
static_assert(!eqx::intersectExclusive(rect5, point3));

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
