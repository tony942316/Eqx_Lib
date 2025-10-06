// Point.cpp

import Eqx.Lib.Math;
import Eqx.Lib.Point;

import <Eqx/std.hpp>;

import <gtest.hpp>;

#ifndef CMAKE_TARGET_NAME
    static_assert(false, "CMAKE_TARGET_NAME not defined!");
#endif // CMAKE_TARGET_NAME

template<class T>
class CMAKE_TARGET_NAME : public ::testing::Test
{
    static_assert(std::semiregular<eqx::lib::Point<T>>);
    static_assert(std::is_trivially_copyable_v<eqx::lib::Point<T>>);
    static_assert(
        std::is_trivially_default_constructible_v<eqx::lib::Point<T>>);
    static_assert(std::is_standard_layout_v<eqx::lib::Point<T>>);
};
using My_Types = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(CMAKE_TARGET_NAME, My_Types);

template <typename T>
inline void point_negate() noexcept
{
    constexpr auto cp1 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            p.negate();
            return p;
        });
    constexpr auto cp2 = eqx::lib::Point<T>::negate(cp1);

    static_assert(eqx::lib::Math::near(cp1.get_x(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp1.get_y(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp2.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2.get_y(), T{ 1 }));

    auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    auto p2 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };

    const auto pn1 = eqx::lib::Point<T>::negate(p1);
    const auto pn2 = eqx::lib::Point<T>::negate(p2);

    p1.negate();
    p2.negate();

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn1.get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn1.get_y(), T{ -1 }));

    ASSERT_TRUE(eqx::lib::Math::near(p2.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn2.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn2.get_y(), T{ 1 }));
}

template <typename T>
inline void point_translate() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp2 = std::invoke([]() constexpr noexcept
            -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            const auto p2 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
            p1.translate(p2);
            return p1;
        });
    constexpr auto cp3 = eqx::lib::Point<T>::translate(cp1, cp2);

    static_assert(eqx::lib::Math::near(cp2.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp3.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp3.get_y(), T{ 1 }));

    auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    auto p2 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };

    const auto pt1 = eqx::lib::Point<T>::translate(p1, p2);
    const auto pt2 = eqx::lib::Point<T>::translate(p2,
        eqx::lib::Point<T>::origin());

    p1.translate(p2);
    p2.translate(eqx::lib::Point<T>::origin());

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pt1.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pt1.get_y(), T{ 0 }));

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pt1.get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pt1.get_y(), T{ -1 }));
}

template <typename T>
inline void point_rotate() noexcept
{
    constexpr auto cp1 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            p1.rotate(std::numbers::pi_v<T> * T{ 2 });
            return p1;
        });
    constexpr auto cp2 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            const auto p2 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
            p1.rotate(std::numbers::pi_v<T>, p2);
            return p1;
        });
    constexpr auto cp3 = eqx::lib::Point<T>::rotate(
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } }, std::numbers::pi_v<T> * T{ 2 });
    constexpr auto cp4 = eqx::lib::Point<T>::rotate(
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } }, std::numbers::pi_v<T>,
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } });

    static_assert(eqx::lib::Math::near(cp1.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2.get_x(), T{ -3 }));
    static_assert(eqx::lib::Math::near(cp2.get_y(), T{ -3 }));
    static_assert(eqx::lib::Math::near(cp3.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp3.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp4.get_x(), T{ -3 }));
    static_assert(eqx::lib::Math::near(cp4.get_y(), T{ -3 }));

    auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p2 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
    auto p3 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };

    const auto pr1 = eqx::lib::Point<T>::rotate(p1,
        std::numbers::pi_v<T> * T{ 2 });
    const auto pr2 = eqx::lib::Point<T>::rotate(p1, std::numbers::pi_v<T>, p2);

    p1.rotate(std::numbers::pi_v<T> * T{ 2 });
    p3.rotate(std::numbers::pi_v<T>, p2);

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.get_x(), T{ -3 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.get_y(), T{ -3 }));

    ASSERT_TRUE(eqx::lib::Math::near(pr1.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pr1.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pr2.get_x(), T{ -3 }));
    ASSERT_TRUE(eqx::lib::Math::near(pr2.get_y(), T{ -3 }));
}

template <typename T>
inline void point_scale() noexcept
{
    constexpr auto cp1 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            p1.scale(T{ 2 });
            return p1;
        });

    constexpr auto cp2 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
            p1.scale(T{ -2 });
            return p1;
        });
    constexpr auto cp3 = eqx::lib::Point<T>::scale(
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } }, T{ 2 });
    constexpr auto cp4 = eqx::lib::Point<T>::scale(
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } }, T{ -2 });

    static_assert(eqx::lib::Math::near(cp1.get_x(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp1.get_y(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp2.get_x(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp2.get_y(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp3.get_x(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp3.get_y(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp4.get_x(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp4.get_y(), T{ 2 }));

    auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    auto p2 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };

    const auto ps1 = eqx::lib::Point<T>::scale(p1, T{ 2 });
    const auto ps2 = eqx::lib::Point<T>::scale(p2, T{ -2 });

    p1.scale(T{ 2 });
    p2.scale(T{ -2 });

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_x(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_y(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_x(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_y(), T{ 2 }));

    ASSERT_TRUE(eqx::lib::Math::near(ps1.get_x(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(ps1.get_y(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(ps2.get_x(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(ps2.get_y(), T{ 2 }));
}

template <typename T>
inline void point_magnitude() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    constexpr auto cp3 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp4 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
    constexpr auto cp5 = eqx::lib::Point<T>{ T{ 0 }, T{ 2 } };

    static_assert(eqx::lib::Math::near(cp1.magnitude(),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(cp2.magnitude(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp3.magnitude(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp4.magnitude(),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(cp5.magnitude(), T{ 2 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::origin().magnitude(), T{ 0 }));

    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(cp1),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(cp2),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(cp4),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(cp5),
        T{ 2 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::magnitude(eqx::lib::Point<T>::origin()), T{ 0 }));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    const auto p3 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p4 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
    const auto p5 = eqx::lib::Point<T>{ T{ 0 }, T{ 2 } };

    ASSERT_TRUE(eqx::lib::Math::near(p1.magnitude(),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(p2.magnitude(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.magnitude(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.magnitude(),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(p5.magnitude(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::origin().magnitude(),
        T{ 0 }));

    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(p1),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(p2),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(p4),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude(p5),
        T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::magnitude(eqx::lib::Point<T>::origin()), T{ 0 }));
}

template <typename T>
inline void point_magnitude2() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    constexpr auto cp3 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp4 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
    constexpr auto cp5 = eqx::lib::Point<T>{ T{ 0 }, T{ 2 } };

    static_assert(eqx::lib::Math::near(cp1.magnitude2(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp2.magnitude2(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp3.magnitude2(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp4.magnitude2(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp5.magnitude2(), T{ 4 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::origin().magnitude2(), T{ 0 }));

    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(cp1),
        T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(cp2),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(cp4),
        T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(cp5),
        T{ 4 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::magnitude2(eqx::lib::Point<T>::origin()), T{ 0 }));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    const auto p3 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p4 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
    const auto p5 = eqx::lib::Point<T>{ T{ 0 }, T{ 2 } };

    ASSERT_TRUE(eqx::lib::Math::near(p1.magnitude2(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.magnitude2(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.magnitude2(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.magnitude2(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p5.magnitude2(), T{ 4 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::origin().magnitude2(),
        T{ 0 }));

    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(p1),
        T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(p2),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(p4),
        T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::magnitude2(p5),
        T{ 4 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::magnitude2(eqx::lib::Point<T>::origin()), T{ 0 }));
}

template <typename T>
inline void point_normalize() noexcept
{
    constexpr auto cp1 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            p1.normalize();
            return p1;
        });
    constexpr auto cp2 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 2 }, T{ 0 } };
            p1.normalize();
            return p1;
        });
    constexpr auto cp3 = eqx::lib::Point<T>::normalize(
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } });
    constexpr auto cp4 = eqx::lib::Point<T>::normalize(
        eqx::lib::Point<T>{ T{ 2 }, T{ 0 } });

    static_assert(eqx::lib::Math::near(cp1.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp1.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp2.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp3.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp3.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp4.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp4.get_y(), T{ 0 }));

    auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    auto p2 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    auto p3 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    auto p4 = eqx::lib::Point<T>{ T{ 2 }, T{ 2 } };
    auto p5 = eqx::lib::Point<T>{ T{ 2 }, T{ 0 } };

    const auto pn1 = eqx::lib::Point<T>::normalize(p1);
    const auto pn2 = eqx::lib::Point<T>::normalize(p2);
    const auto pn3 = eqx::lib::Point<T>::normalize(p3);
    const auto pn4 = eqx::lib::Point<T>::normalize(p4);
    const auto pn5 = eqx::lib::Point<T>::normalize(p5);

    p1.normalize();
    p2.normalize();
    p3.normalize();
    p4.normalize();
    p5.normalize();

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p5.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p5.get_y(), T{ 0 }));

    ASSERT_TRUE(eqx::lib::Math::near(pn1.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn1.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn2.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn2.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn3.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn3.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn4.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn4.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn5.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pn5.get_y(), T{ 0 }));
}

template <typename T>
inline void point_distance() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    constexpr auto cp3 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp4 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
    constexpr auto cp5 = eqx::lib::Point<T>{ T{ 0 }, T{ 2 } };

    static_assert(eqx::lib::Math::near(cp1.distance(cp1), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.distance(cp2), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.distance(cp3), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.distance(cp4),
        T{ 2 } * std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(cp1.distance(cp5),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(cp2.distance(cp2), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2.distance(cp3),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(cp2.distance(cp4),
        static_cast<T>(2.236067F)));
    static_assert(eqx::lib::Math::near(cp2.distance(cp5), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp3.distance(cp3), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp3.distance(cp4),
        static_cast<T>(2.236067F)));
    static_assert(eqx::lib::Math::near(cp3.distance(cp5),
        static_cast<T>(2.236067F)));
    static_assert(eqx::lib::Math::near(cp4.distance(cp4), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp4.distance(cp5),
        static_cast<T>(3.162277F)));
    static_assert(eqx::lib::Math::near(cp5.distance(cp5), T{ 0 }));

    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp1, cp1),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp1, cp2),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp1, cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp1, cp4),
        T{ 2 } * std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp1, cp5),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp2, cp2),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp2, cp3),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp2, cp4),
        static_cast<T>(2.236067F)));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp2, cp5),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp3, cp3),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp3, cp4),
        static_cast<T>(2.236067F)));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp3, cp5),
        static_cast<T>(2.236067F)));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp4, cp4),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp4, cp5),
        static_cast<T>(3.162277F)));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance(cp5, cp5),
        T{ 0 }));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    const auto p3 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p4 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
    const auto p5 = eqx::lib::Point<T>{ T{ 0 }, T{ 2 } };

    ASSERT_TRUE(eqx::lib::Math::near(p1.distance(p1), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.distance(p2), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.distance(p3), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.distance(p4),
        T{ 2 } * std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(p1.distance(p5),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(p2.distance(p2), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.distance(p3),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(p2.distance(p4),
        static_cast<T>(2.236067F)));
    ASSERT_TRUE(eqx::lib::Math::near(p2.distance(p5), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.distance(p3), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.distance(p4),
        static_cast<T>(2.236067F)));
    ASSERT_TRUE(eqx::lib::Math::near(p3.distance(p5),
        static_cast<T>(2.236067F)));
    ASSERT_TRUE(eqx::lib::Math::near(p4.distance(p4), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.distance(p5),
        static_cast<T>(3.162277F)));
    ASSERT_TRUE(eqx::lib::Math::near(p5.distance(p5), T{ 0 }));

    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p1, p1),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p1, p2),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p1, p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p1, p4),
        T{ 2 } * std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p1, p5),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p2, p2),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p2, p3),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p2, p4),
        static_cast<T>(2.236067F)));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p2, p5),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p3, p3),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p3, p4),
        static_cast<T>(2.236067F)));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p3, p5),
        static_cast<T>(2.236067F)));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p4, p4),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p4, p5),
        static_cast<T>(3.162277F)));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance(p5, p5),
        T{ 0 }));
}

template <typename T>
inline void point_distance2() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    constexpr auto cp3 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp4 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
    constexpr auto cp5 = eqx::lib::Point<T>{ T{ 0 }, T{ 2 } };

    static_assert(eqx::lib::Math::near(cp1.distance2(cp1), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.distance2(cp2), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.distance2(cp3), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.distance2(cp4), T{ 8 }));
    static_assert(eqx::lib::Math::near(cp1.distance2(cp5), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp2.distance2(cp2), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2.distance2(cp3), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp2.distance2(cp4), T{ 5 }));
    static_assert(eqx::lib::Math::near(cp2.distance2(cp5), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp3.distance2(cp3), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp3.distance2(cp4), T{ 5 }));
    static_assert(eqx::lib::Math::near(cp3.distance2(cp5), T{ 5 }));
    static_assert(eqx::lib::Math::near(cp4.distance2(cp4), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp4.distance2(cp5), T{ 10 }));
    static_assert(eqx::lib::Math::near(cp5.distance2(cp5), T{ 0 }));

    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp1, cp1),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp1, cp2),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp1, cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp1, cp4),
        T{ 8 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp1, cp5),
        T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp2, cp2),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp2, cp3),
        T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp2, cp4),
        T{ 5 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp2, cp5),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp3, cp3),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp3, cp4),
        T{ 5 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp3, cp5),
        T{ 5 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp4, cp4),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp4, cp5),
        T{ 10 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(cp5, cp5),
        T{ 0 }));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    const auto p3 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p4 = eqx::lib::Point<T>{ T{ -1 }, T{ -1 } };
    const auto p5 = eqx::lib::Point<T>{ T{ 0 }, T{ 2 } };

    ASSERT_TRUE(eqx::lib::Math::near(p1.distance2(p1), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.distance2(p2), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.distance2(p3), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.distance2(p4), T{ 8 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.distance2(p5), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.distance2(p2), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.distance2(p3), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.distance2(p4), T{ 5 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.distance2(p5), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.distance2(p3), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.distance2(p4), T{ 5 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.distance2(p5), T{ 5 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.distance2(p4), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.distance2(p5), T{ 10 }));
    ASSERT_TRUE(eqx::lib::Math::near(p5.distance2(p5), T{ 0 }));

    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p1, p1),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p1, p2),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p1, p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p1, p4),
        T{ 8 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p1, p5),
        T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p2, p2),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p2, p3),
        T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p2, p4),
        T{ 5 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p2, p5),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p3, p3),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p3, p4),
        T{ 5 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p3, p5),
        T{ 5 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p4, p4),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p4, p5),
        T{ 10 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::distance2(p5, p5),
        T{ 0 }));
}

template <typename T>
inline void point_lerp() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    constexpr auto cp12d3 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            auto p2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            p1.lerp(p2, static_cast<T>(0.3F));
            return p1;
        });
    constexpr auto cp12d7 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            auto p2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            p1.lerp(p2, static_cast<T>(0.7F));
            return p1;
        });
    constexpr auto cp14d3 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            auto p4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };
            p1.lerp(p4, static_cast<T>(0.3F));
            return p1;
        });
    constexpr auto cp14d7 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            auto p4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };
            p1.lerp(p4, static_cast<T>(0.7F));
            return p1;
        });

    constexpr auto cp12d3l = eqx::lib::Point<T>::lerp(cp1, cp2,
        static_cast<T>(0.3F));
    constexpr auto cp12d7l = eqx::lib::Point<T>::lerp(cp1, cp2,
        static_cast<T>(0.7F));
    constexpr auto cp14d3l = eqx::lib::Point<T>::lerp(cp1, cp4,
        static_cast<T>(0.3F));
    constexpr auto cp14d7l = eqx::lib::Point<T>::lerp(cp1, cp4,
        static_cast<T>(0.7F));

    static_assert(eqx::lib::Math::near(cp12d3.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp12d3.get_y(), static_cast<T>(0.3F)));
    static_assert(eqx::lib::Math::near(cp12d7.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp12d7.get_y(), static_cast<T>(0.7F)));
    static_assert(eqx::lib::Math::near(cp14d3.get_x(), static_cast<T>(0.1F)));
    static_assert(eqx::lib::Math::near(cp14d3.get_y(), static_cast<T>(-0.6F)));
    static_assert(eqx::lib::Math::near(cp14d7.get_x(), static_cast<T>(-1.1F)));
    static_assert(eqx::lib::Math::near(cp14d7.get_y(), static_cast<T>(-1.4F)));
    static_assert(eqx::lib::Math::near(cp12d3l.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp12d3l.get_y(), static_cast<T>(0.3F)));
    static_assert(eqx::lib::Math::near(cp12d7l.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp12d7l.get_y(), static_cast<T>(0.7F)));
    static_assert(eqx::lib::Math::near(cp14d3l.get_x(), static_cast<T>(0.1F)));
    static_assert(eqx::lib::Math::near(cp14d3l.get_y(), static_cast<T>(-0.6F)));
    static_assert(eqx::lib::Math::near(cp14d7l.get_x(), static_cast<T>(-1.1F)));
    static_assert(eqx::lib::Math::near(cp14d7l.get_y(), static_cast<T>(-1.4F)));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    auto p12d3 = p1;
    auto p12d7 = p1;
    auto p14d3 = p1;
    auto p14d7 = p1;

    p12d3.lerp(p2, static_cast<T>(0.3F));
    p12d7.lerp(p2, static_cast<T>(0.7F));
    p14d3.lerp(p4, static_cast<T>(0.3F));
    p14d7.lerp(p4, static_cast<T>(0.7F));

    auto p12d3l = eqx::lib::Point<T>::lerp(p1, p2, static_cast<T>(0.3F));
    auto p12d7l = eqx::lib::Point<T>::lerp(p1, p2, static_cast<T>(0.7F));
    auto p14d3l = eqx::lib::Point<T>::lerp(p1, p4, static_cast<T>(0.3F));
    auto p14d7l = eqx::lib::Point<T>::lerp(p1, p4, static_cast<T>(0.7F));

    ASSERT_TRUE(eqx::lib::Math::near(p12d3.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p12d3.get_y(), static_cast<T>(0.3F)));
    ASSERT_TRUE(eqx::lib::Math::near(p12d7.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p12d7.get_y(), static_cast<T>(0.7F)));
    ASSERT_TRUE(eqx::lib::Math::near(p14d3.get_x(), static_cast<T>(0.1F)));
    ASSERT_TRUE(eqx::lib::Math::near(p14d3.get_y(), static_cast<T>(-0.6F)));
    ASSERT_TRUE(eqx::lib::Math::near(p14d7.get_x(), static_cast<T>(-1.1F)));
    ASSERT_TRUE(eqx::lib::Math::near(p14d7.get_y(), static_cast<T>(-1.4F)));
    ASSERT_TRUE(eqx::lib::Math::near(p12d3l.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p12d3l.get_y(), static_cast<T>(0.3F)));
    ASSERT_TRUE(eqx::lib::Math::near(p12d7l.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p12d7l.get_y(), static_cast<T>(0.7F)));
    ASSERT_TRUE(eqx::lib::Math::near(p14d3l.get_x(), static_cast<T>(0.1F)));
    ASSERT_TRUE(eqx::lib::Math::near(p14d3l.get_y(), static_cast<T>(-0.6F)));
    ASSERT_TRUE(eqx::lib::Math::near(p14d7l.get_x(), static_cast<T>(-1.1F)));
    ASSERT_TRUE(eqx::lib::Math::near(p14d7l.get_y(), static_cast<T>(-1.4F)));
}

template <typename T>
inline void point_midpoint() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp3 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    constexpr auto cp4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    constexpr auto cp12 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            auto p2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            p1.midpoint(p2);
            return p1;
        });
    constexpr auto cp13 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            auto p3 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
            p1.midpoint(p3);
            return p1;
        });
    constexpr auto cp14 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            auto p4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };
            p1.midpoint(p4);
            return p1;
        });

    constexpr auto cp12m = eqx::lib::Point<T>::midpoint(cp1, cp2);
    constexpr auto cp13m = eqx::lib::Point<T>::midpoint(cp1, cp3);
    constexpr auto cp14m = eqx::lib::Point<T>::midpoint(cp1, cp4);

    static_assert(eqx::lib::Math::near(cp12.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp12.get_y(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp13.get_x(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp13.get_y(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp14.get_x(), T{ -1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp14.get_y(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp12m.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp12m.get_y(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp13m.get_x(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp13m.get_y(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp14m.get_x(), T{ -1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp14m.get_y(), T{ -1 }));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p3 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    const auto p4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    auto p12 = p1;
    auto p13 = p1;
    auto p14 = p1;

    p12.midpoint(p2);
    p13.midpoint(p3);
    p14.midpoint(p4);

    auto p12m = eqx::lib::Point<T>::midpoint(p1, p2);
    auto p13m = eqx::lib::Point<T>::midpoint(p1, p3);
    auto p14m = eqx::lib::Point<T>::midpoint(p1, p4);

    ASSERT_TRUE(eqx::lib::Math::near(p12.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p12.get_y(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p13.get_x(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p13.get_y(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p14.get_x(), T{ -1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p14.get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p12m.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p12m.get_y(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p13m.get_x(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p13m.get_y(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p14m.get_x(), T{ -1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p14m.get_y(), T{ -1 }));
}

template <typename T>
inline void point_dot() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp3 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    constexpr auto cp4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    static_assert(eqx::lib::Math::near(cp1.dot(cp1), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.dot(cp2), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.dot(cp3), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.dot(cp4), T{ -2 }));
    static_assert(eqx::lib::Math::near(cp2.dot(cp2), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp2.dot(cp3), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2.dot(cp4), T{ -4 }));
    static_assert(eqx::lib::Math::near(cp3.dot(cp3), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp3.dot(cp4), T{ -2 }));
    static_assert(eqx::lib::Math::near(cp4.dot(cp4), T{ 8 }));

    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp1, cp1),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp1, cp2),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp1, cp3),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp1, cp4),
        T{ -2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp2, cp2),
        T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp2, cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp2, cp4),
        T{ -4 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp3, cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp3, cp4),
        T{ -2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::dot(cp4, cp4),
        T{ 8 }));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p3 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    const auto p4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    ASSERT_TRUE(eqx::lib::Math::near(p1.dot(p1), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.dot(p2), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.dot(p3), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.dot(p4), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.dot(p2), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.dot(p3), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.dot(p4), T{ -4 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.dot(p3), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.dot(p4), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.dot(p4), T{ 8 }));

    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p1, p1), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p1, p2), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p1, p3), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p1, p4), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p2, p2),
        T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p2, p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p2, p4),
        T{ -4 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p3, p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p3, p4),
        T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::dot(p4, p4),
        T{ 8 }));
}

template <typename T>
inline void point_cross() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp3 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    constexpr auto cp4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    static_assert(eqx::lib::Math::near(cp1.cross(cp1), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.cross(cp2), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.cross(cp3), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.cross(cp4), T{ -2 }));
    static_assert(eqx::lib::Math::near(cp2.cross(cp1), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp2.cross(cp2), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2.cross(cp3), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2.cross(cp4), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp3.cross(cp1), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp3.cross(cp2), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp3.cross(cp3), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp3.cross(cp4), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp4.cross(cp1), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp4.cross(cp2), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp4.cross(cp3), T{ -2 }));
    static_assert(eqx::lib::Math::near(cp4.cross(cp4), T{ 0 }));

    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp1, cp1),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp1, cp2),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp1, cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp1, cp4),
        T{ -2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp2, cp1),
        T{ -1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp2, cp2),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp2, cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp2, cp4),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp3, cp1),
        T{ -1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp3, cp2),
        T{ -1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp3, cp3),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp3, cp4),
        T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp4, cp1),
        T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp4, cp2),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp4, cp3),
        T{ -2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::cross(cp4, cp4),
        T{ 0 }));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p3 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    const auto p4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    ASSERT_TRUE(eqx::lib::Math::near(p1.cross(p1), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.cross(p2), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.cross(p3), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.cross(p4), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.cross(p1), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.cross(p2), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.cross(p3), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.cross(p4), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.cross(p1), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.cross(p2), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.cross(p3), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.cross(p4), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.cross(p1), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.cross(p2), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.cross(p3), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.cross(p4), T{ 0 }));

    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p1, p1),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p1, p2),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p1, p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p1, p4),
        T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p2, p1),
        T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p2, p2),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p2, p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p2, p4),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p3, p1),
        T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p3, p2),
        T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p3, p3),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p3, p4),
        T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p4, p1),
        T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p4, p2),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p4, p3),
        T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::cross(p4, p4),
        T{ 0 }));
}

template <typename T>
inline void point_component() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp3 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    constexpr auto cp4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    static_assert(eqx::lib::Math::near(cp1.component(cp1), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.component(cp2),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp1.component(cp3), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.component(cp4),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp2.component(cp1), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2.component(cp2),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(cp2.component(cp3), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2.component(cp4),
        -std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(cp3.component(cp1), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp3.component(cp2),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp3.component(cp3), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp3.component(cp4),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp4.component(cp1), T{ -2 }));
    static_assert(eqx::lib::Math::near(cp4.component(cp2),
        T{ -2 } * std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(cp4.component(cp3), T{ -2 }));
    static_assert(eqx::lib::Math::near(cp4.component(cp4),
        T{ 2 } * std::numbers::sqrt2_v<T>));

    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp1, cp1),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp1, cp2),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp1, cp3),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp1, cp4),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp2, cp1),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp2, cp2),
        std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp2, cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp2, cp4),
        -std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp3, cp1),
        T{ 0 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp3, cp2),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp3, cp3),
        T{ 1 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp3, cp4),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp4, cp1),
        T{ -2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp4, cp2),
        T{ -2 } * std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp4, cp3),
        T{ -2 }));
    static_assert(eqx::lib::Math::near(eqx::lib::Point<T>::component(cp4, cp4),
        T{ 2 } * std::numbers::sqrt2_v<T>));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p3 = eqx::lib::Point<T>{ T{ 0 }, T{ 1 } };
    const auto p4 = eqx::lib::Point<T>{ T{ -2 }, T{ -2 } };

    ASSERT_TRUE(eqx::lib::Math::near(p1.component(p1), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.component(p2),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.component(p3), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.component(p4),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.component(p1), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.component(p2),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(p2.component(p3), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.component(p4),
        -std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(p3.component(p1), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.component(p2),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.component(p3), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3.component(p4),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.component(p1), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.component(p2),
        T{ -2 } * std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(p4.component(p3), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p4.component(p4),
        T{ 2 } * std::numbers::sqrt2_v<T>));

    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p1, p1),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p1, p2),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p1, p3),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p1, p4),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p2, p1),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p2, p2),
        std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p2, p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p2, p4),
        -std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p3, p1),
        T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p3, p2),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p3, p3),
        T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p3, p4),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p4, p1),
        T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p4, p2),
        T{ -2 } * std::numbers::sqrt2_v<T>));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p4, p3),
        T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(eqx::lib::Point<T>::component(p4, p4),
        T{ 2 } * std::numbers::sqrt2_v<T>));
}

template <typename T>
inline void point_projection() noexcept
{
    constexpr auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    constexpr auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    constexpr auto cp3 = eqx::lib::Point<T>{ T{ -2 }, T{ -3 } };

    constexpr auto cp11 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            cp1.projection(cp1);
            return cp1;
        });
    constexpr auto cp12 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            cp1.projection(cp2);
            return cp1;
        });
    constexpr auto cp13 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            auto cp3 = eqx::lib::Point<T>{ T{ -2 }, T{ -3 } };
            cp1.projection(cp3);
            return cp1;
        });
    constexpr auto cp21 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            cp2.projection(cp1);
            return cp2;
        });
    constexpr auto cp22 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            cp2.projection(cp2);
            return cp2;
        });
    constexpr auto cp23 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            auto cp3 = eqx::lib::Point<T>{ T{ -2 }, T{ -3 } };
            cp2.projection(cp3);
            return cp2;
        });
    constexpr auto cp31 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto cp3 = eqx::lib::Point<T>{ T{ -2 }, T{ -3 } };
            auto cp1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
            cp3.projection(cp1);
            return cp3;
        });
    constexpr auto cp32 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto cp3 = eqx::lib::Point<T>{ T{ -2 }, T{ -3 } };
            auto cp2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
            cp3.projection(cp2);
            return cp3;
        });
    constexpr auto cp33 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Point<T>
        {
            auto cp3 = eqx::lib::Point<T>{ T{ -2 }, T{ -3 } };
            cp3.projection(cp3);
            return cp3;
        });

    static_assert(eqx::lib::Math::near(cp11.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp11.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp12.get_x(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp12.get_y(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp13.get_x(), T{ 4 } / T{ 13 }));
    static_assert(eqx::lib::Math::near(cp13.get_y(), T{ 6 } / T{ 13 }));
    static_assert(eqx::lib::Math::near(cp21.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp21.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp22.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp22.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp23.get_x(), T{ 10 } / T{ 13 }));
    static_assert(eqx::lib::Math::near(cp23.get_y(), T{ 15 } / T{ 13 }));
    static_assert(eqx::lib::Math::near(cp31.get_x(), T{ -2 }));
    static_assert(eqx::lib::Math::near(cp31.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp32.get_x(), T{ -5 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp32.get_y(), T{ -5 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp33.get_x(), T{ -2 }));
    static_assert(eqx::lib::Math::near(cp33.get_y(), T{ -3 }));

    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp1, cp1).get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp1, cp1).get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp1, cp2).get_x(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp1, cp2).get_y(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp1, cp3).get_x(), T{ 4 } / T{ 13 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp1, cp3).get_y(), T{ 6 } / T{ 13 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp2, cp1).get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp2, cp1).get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp2, cp2).get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp2, cp2).get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp2, cp3).get_x(), T{ 10 } / T{ 13 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp2, cp3).get_y(), T{ 15 } / T{ 13 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp3, cp1).get_x(), T{ -2 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp3, cp1).get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp3, cp2).get_x(), T{ -5 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp3, cp2).get_y(), T{ -5 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp3, cp3).get_x(), T{ -2 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(cp3, cp3).get_y(), T{ -3 }));

    const auto p1 = eqx::lib::Point<T>{ T{ 1 }, T{ 0 } };
    const auto p2 = eqx::lib::Point<T>{ T{ 1 }, T{ 1 } };
    const auto p3 = eqx::lib::Point<T>{ T{ -2 }, T{ -3 } };

    auto p11 = p1;
    auto p13 = p1;
    auto p12 = p1;
    auto p21 = p2;
    auto p22 = p2;
    auto p23 = p2;
    auto p31 = p3;
    auto p32 = p3;
    auto p33 = p3;

    p11.projection(p1);
    p12.projection(p2);
    p13.projection(p3);
    p21.projection(p1);
    p22.projection(p2);
    p23.projection(p3);
    p31.projection(p1);
    p32.projection(p2);
    p33.projection(p3);

    ASSERT_TRUE(eqx::lib::Math::near(p11.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p11.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p12.get_x(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p12.get_y(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p13.get_x(), T{ 4 } / T{ 13 }));
    ASSERT_TRUE(eqx::lib::Math::near(p13.get_y(), T{ 6 } / T{ 13 }));
    ASSERT_TRUE(eqx::lib::Math::near(p21.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p21.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p22.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p22.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p23.get_x(), T{ 10 } / T{ 13 }));
    ASSERT_TRUE(eqx::lib::Math::near(p23.get_y(), T{ 15 } / T{ 13 }));
    ASSERT_TRUE(eqx::lib::Math::near(p31.get_x(), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p31.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p32.get_x(), T{ -5 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p32.get_y(), T{ -5 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p33.get_x(), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p33.get_y(), T{ -3 }));

    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p1, p1).get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p1, p1).get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p1, p2).get_x(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p1, p2).get_y(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p1, p3).get_x(), T{ 4 } / T{ 13 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p1, p3).get_y(), T{ 6 } / T{ 13 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p2, p1).get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p2, p1).get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p2, p2).get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p2, p2).get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p2, p3).get_x(), T{ 10 } / T{ 13 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p2, p3).get_y(), T{ 15 } / T{ 13 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p3, p1).get_x(), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p3, p1).get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p3, p2).get_x(), T{ -5 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p3, p2).get_y(), T{ -5 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p3, p3).get_x(), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(
        eqx::lib::Point<T>::projection(p3, p3).get_y(), T{ -3 }));
}

template <typename T>
inline void point_origin() noexcept
{
    constexpr auto c_origin = eqx::lib::Point<T>::origin();
    static_assert(eqx::lib::Math::near(c_origin.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(c_origin.get_y(), T{ 0 }));

    const auto origin = eqx::lib::Point<T>::origin();
    ASSERT_TRUE(eqx::lib::Math::near(origin.get_x(), T{ 0 },
        static_cast<T>(1E-10F)));
    ASSERT_TRUE(eqx::lib::Math::near(origin.get_y(), T{ 0 },
        static_cast<T>(1E-10F)));
}

TYPED_TEST(CMAKE_TARGET_NAME, point_negate)
{
    point_negate<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_translate)
{
    point_negate<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_rotate)
{
    point_rotate<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_scale)
{
    point_scale<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_magnitude)
{
    point_magnitude<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_magnitude2)
{
    point_magnitude2<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_normalize)
{
    point_normalize<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_distance)
{
    point_distance<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_distance2)
{
    point_distance2<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_lerp)
{
    point_lerp<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_midpoint)
{
    point_midpoint<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_dot)
{
    point_dot<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_cross)
{
    point_cross<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_component)
{
    point_component<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_projection)
{
    point_projection<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, point_origin)
{
    point_origin<TypeParam>();
}
