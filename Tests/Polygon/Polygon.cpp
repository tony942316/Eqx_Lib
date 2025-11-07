// Polygon.cpp

import Eqx.Lib.Math;
import Eqx.Lib.Point;
import Eqx.Lib.Polygon;

import <Eqx/std.hpp>;

import <gtest.hpp>;

#ifndef CMAKE_TARGET_NAME
    static_assert(false, "CMAKE_TARGET_NAME not defined!");
#endif // CMAKE_TARGET_NAME

template<class T>
class CMAKE_TARGET_NAME : public ::testing::Test
{
    static_assert(std::semiregular<eqx::lib::Polygon<T, 3>>);
    static_assert(std::is_trivially_copyable_v<eqx::lib::Polygon<T, 3>>);
    static_assert(
        std::is_trivially_default_constructible_v<eqx::lib::Polygon<T, 3>>);
    static_assert(std::is_standard_layout_v<eqx::lib::Polygon<T, 3>>);
    static_assert(std::semiregular<eqx::lib::Polygon<T, 4>>);
    static_assert(std::is_trivially_copyable_v<eqx::lib::Polygon<T, 4>>);
    static_assert(
        std::is_trivially_default_constructible_v<eqx::lib::Polygon<T, 4>>);
    static_assert(std::is_standard_layout_v<eqx::lib::Polygon<T, 4>>);
    static_assert(std::semiregular<eqx::lib::Polygon<T, 10>>);
    static_assert(std::is_trivially_copyable_v<eqx::lib::Polygon<T, 10>>);
    static_assert(
        std::is_trivially_default_constructible_v<eqx::lib::Polygon<T, 10>>);
    static_assert(std::is_standard_layout_v<eqx::lib::Polygon<T, 10>>);
};
using My_Types = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(CMAKE_TARGET_NAME, My_Types);

template <typename T>
inline void polygon_bounding_box() noexcept
{
    constexpr auto cp1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    constexpr auto cp2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    constexpr auto cp3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };

    constexpr auto cp1bb = cp1.bounding_box();
    constexpr auto cp2bb = cp2.bounding_box();
    constexpr auto cp3bb = cp3.bounding_box();

    static_assert(eqx::lib::Math::near(cp1bb.first.get_x(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp1bb.first.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1bb.second.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1bb.second.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2bb.first.get_x(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp2bb.first.get_y(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp2bb.second.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2bb.second.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp3bb.first.get_x(), T{ -3 }));
    static_assert(eqx::lib::Math::near(cp3bb.first.get_y(), T{ -3 }));
    static_assert(eqx::lib::Math::near(cp3bb.second.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp3bb.second.get_y(), T{ 0 }));

    const auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    const auto p2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    const auto p3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };

    const auto [p1min, p1max] = p1.bounding_box();
    const auto [p2min, p2max] = p2.bounding_box();
    const auto [p3min, p3max] = p3.bounding_box();

    ASSERT_TRUE(eqx::lib::Math::near(p1min.get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1min.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1max.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1max.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2min.get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2min.get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2max.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2max.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3min.get_x(), T{ -3 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3min.get_y(), T{ -3 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3max.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3max.get_y(), T{ 0 }));
}

template <typename T>
inline void polygon_center() noexcept
{
    constexpr auto cp1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    constexpr auto cp2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    constexpr auto cp3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };

    constexpr auto cp1c = cp1.center();
    constexpr auto cp2c = cp2.center();
    constexpr auto cp3c = cp3.center();

    static_assert(eqx::lib::Math::near(cp1c.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1c.get_y(), T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp2c.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2c.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp3c.get_x(), T{ -3 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp3c.get_y(), T{ -3 } / T{ 2 }));

    const auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    const auto p2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    const auto p3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };

    const auto p1c = p1.center();
    const auto p2c = p2.center();
    const auto p3c = p3.center();

    ASSERT_TRUE(eqx::lib::Math::near(p1c.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1c.get_y(), T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2c.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2c.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3c.get_x(), T{ -3 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p3c.get_y(), T{ -3 } / T{ 2 }));
}

template <typename T>
inline void polygon_aabb() noexcept
{
    constexpr auto cp1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    constexpr auto cp2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    constexpr auto cp3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };
    constexpr auto cp4 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 3 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 2 }, T{ 2 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };

    static_assert(cp1.aabb(cp1) == true);
    static_assert(cp1.aabb(cp2) == true);
    static_assert(cp1.aabb(cp3) == true);
    static_assert(cp1.aabb(cp4) == true);
    static_assert(cp2.aabb(cp1) == true);
    static_assert(cp2.aabb(cp2) == true);
    static_assert(cp2.aabb(cp3) == true);
    static_assert(cp2.aabb(cp4) == true);
    static_assert(cp3.aabb(cp1) == true);
    static_assert(cp3.aabb(cp2) == true);
    static_assert(cp3.aabb(cp3) == true);
    static_assert(cp3.aabb(cp4) == false);
    static_assert(cp4.aabb(cp1) == true);
    static_assert(cp4.aabb(cp2) == true);
    static_assert(cp4.aabb(cp3) == false);
    static_assert(cp4.aabb(cp4) == true);

    const auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    const auto p2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    const auto p3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };
    const auto p4 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 3 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 2 }, T{ 2 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };

    ASSERT_TRUE(p1.aabb(p1));
    ASSERT_TRUE(p1.aabb(p2));
    ASSERT_TRUE(p1.aabb(p3));
    ASSERT_TRUE(p1.aabb(p4));
    ASSERT_TRUE(p2.aabb(p1));
    ASSERT_TRUE(p2.aabb(p2));
    ASSERT_TRUE(p2.aabb(p3));
    ASSERT_TRUE(p2.aabb(p4));
    ASSERT_TRUE(p3.aabb(p1));
    ASSERT_TRUE(p3.aabb(p2));
    ASSERT_TRUE(p3.aabb(p3));
    ASSERT_FALSE(p3.aabb(p4));
    ASSERT_TRUE(p4.aabb(p1));
    ASSERT_TRUE(p4.aabb(p2));
    ASSERT_FALSE(p4.aabb(p3));
    ASSERT_TRUE(p4.aabb(p4));
}

template <typename T>
inline void polygon_translate() noexcept
{
    constexpr auto cp1 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Polygon<T, 3>
        {
            auto p1 = eqx::lib::Polygon<T, 3>{
                eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
                eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
                eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
            p1.translate(eqx::lib::Point<T>{ T{ 1 }, T{ 1 } });
            return p1;
       });

    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_y(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_x(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_y(), T{ 1 }));

    auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };

    p1.translate(eqx::lib::Point<T>{ T{ 1 }, T{ 1 } });

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_y(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_x(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_y(), T{ 1 }));
}

template <typename T>
inline void polygon_move() noexcept
{
    constexpr auto cp1 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Polygon<T, 3>
        {
            auto p1 = eqx::lib::Polygon<T, 3>{
                eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
                eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
                eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
            p1.move(eqx::lib::Point<T>{ T{ 0 }, T{ 0 } });
            return p1;
       });

    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_y(),
        T{ 1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_x(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_y(),
        T{ -1 } / T{ 2 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_y(),
        T{ -1 } / T{ 2 }));

    auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    p1.move(eqx::lib::Point<T>{ T{ 0 }, T{ 0 } });

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_y(),
        T{ 1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_y(),
        T{ -1 } / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_y(),
        T{ -1 } / T{ 2 }));
}

template <typename T>
inline void polygon_rotate() noexcept
{
    constexpr auto cp1 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Polygon<T, 3>
        {
            auto p1 = eqx::lib::Polygon<T, 3>{
                eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
                eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
                eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
            p1.rotate(std::numbers::pi_v<T>);
            return p1;
       });
    constexpr auto cp2 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Polygon<T, 3>
        {
            auto p1 = eqx::lib::Polygon<T, 3>{
                eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
                eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
                eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
            p1.rotate(std::numbers::pi_v<T>, eqx::lib::Point<T>::origin());
            return p1;
       });

    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_x(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp1.center().get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.center().get_y(), T{ 1 } / T{ 2 }));

    static_assert(eqx::lib::Math::near(cp2.get_data()[0].get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[0].get_y(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[1].get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[1].get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[2].get_x(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[2].get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2.center().get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2.center().get_y(), T{ -1 } / T{ 2 }));

    auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    p1.rotate(std::numbers::pi_v<T>);

    auto p2 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    p2.rotate(std::numbers::pi_v<T>, eqx::lib::Point<T>::origin());

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.center().get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.center().get_y(), T{ 1 } / T{ 2 }));

    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[0].get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[0].get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[1].get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[1].get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[2].get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[2].get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.center().get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.center().get_y(), T{ -1 } / T{ 2 }));
}

template <typename T>
inline void polygon_scale() noexcept
{
    constexpr auto cp1 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Polygon<T, 3>
        {
            auto p1 = eqx::lib::Polygon<T, 3>{
                eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
                eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
                eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
            p1.scale(T{ 2 });
            return p1;
       });

    constexpr auto cp2 = std::invoke([]() constexpr noexcept
        -> eqx::lib::Polygon<T, 4>
        {
            auto p2 = eqx::lib::Polygon<T, 4>{
                eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
                eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
                eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
                eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
            p2.scale(T{ 1080 });
            return p2;
        });

    constexpr auto cp1c = cp1.center();
    constexpr auto cp2c = cp2.center();

    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_y(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_x(), T{ -2 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_x(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[0].get_x(), T{ 1080 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[0].get_y(), T{ 1080 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[1].get_x(), T{ -1080 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[1].get_y(), T{ 1080 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[2].get_x(), T{ -1080 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[2].get_y(), T{ -1080 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[3].get_x(), T{ 1080 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[3].get_y(), T{ -1080 }));
    static_assert(eqx::lib::Math::near(cp1c.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp1c.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cp2c.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cp2c.get_y(), T{ 0 }));

    auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    auto p2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };

    p1.scale(T{ 2 });
    p2.scale(T{ 1080 });

    auto p1c = p1.center();
    auto p2c = p2.center();

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_y(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_x(), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_x(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[0].get_x(), T{ 1080 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[0].get_y(), T{ 1080 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[1].get_x(), T{ -1080 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[1].get_y(), T{ 1080 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[2].get_x(), T{ -1080 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[2].get_y(), T{ -1080 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[3].get_x(), T{ 1080 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[3].get_y(), T{ -1080 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1c.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p1c.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2c.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2c.get_y(), T{ 0 }));
}

template <typename T>
inline void polygon_midpoint() noexcept
{
    constexpr auto cp1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    constexpr auto cp2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    constexpr auto cp3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };
    constexpr auto cp4 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 3 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 2 }, T{ 2 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };

    constexpr auto cpm10 = cp1.midpoint(std::size_t{ 0 });
    constexpr auto cpm11 = cp1.midpoint(std::size_t{ 1 });
    constexpr auto cpm12 = cp1.midpoint(std::size_t{ 2 });
    constexpr auto cpm20 = cp2.midpoint(std::size_t{ 0 });
    constexpr auto cpm21 = cp2.midpoint(std::size_t{ 1 });
    constexpr auto cpm22 = cp2.midpoint(std::size_t{ 2 });
    constexpr auto cpm23 = cp2.midpoint(std::size_t{ 3 });
    constexpr auto cpm30 = cp3.midpoint(std::size_t{ 0 });
    constexpr auto cpm31 = cp3.midpoint(std::size_t{ 1 });
    constexpr auto cpm32 = cp3.midpoint(std::size_t{ 2 });
    constexpr auto cpm33 = cp3.midpoint(std::size_t{ 3 });
    constexpr auto cpm34 = cp3.midpoint(std::size_t{ 4 });
    constexpr auto cpm35 = cp3.midpoint(std::size_t{ 5 });
    constexpr auto cpm36 = cp3.midpoint(std::size_t{ 6 });
    constexpr auto cpm37 = cp3.midpoint(std::size_t{ 7 });
    constexpr auto cpm40 = cp4.midpoint(std::size_t{ 0 });
    constexpr auto cpm41 = cp4.midpoint(std::size_t{ 1 });
    constexpr auto cpm42 = cp4.midpoint(std::size_t{ 2 });

    static_assert(eqx::lib::Math::near(cpm10.get_x(), static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cpm10.get_y(), static_cast<T>(0.5F)));
    static_assert(eqx::lib::Math::near(cpm11.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm11.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm12.get_x(), static_cast<T>(0.5F)));
    static_assert(eqx::lib::Math::near(cpm12.get_y(), static_cast<T>(0.5F)));
    static_assert(eqx::lib::Math::near(cpm20.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm20.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cpm21.get_x(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cpm21.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm22.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm22.get_y(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cpm23.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cpm23.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm30.get_x(), static_cast<T>(-1.5F)));
    static_assert(eqx::lib::Math::near(cpm30.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm31.get_x(), static_cast<T>(-2.5F)));
    static_assert(eqx::lib::Math::near(cpm31.get_y(), static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cpm32.get_x(), T{ -3 }));
    static_assert(eqx::lib::Math::near(cpm32.get_y(), static_cast<T>(-1.5F)));
    static_assert(eqx::lib::Math::near(cpm33.get_x(), static_cast<T>(-2.5F)));
    static_assert(eqx::lib::Math::near(cpm33.get_y(), static_cast<T>(-2.5F)));
    static_assert(eqx::lib::Math::near(cpm34.get_x(), static_cast<T>(-1.5F)));
    static_assert(eqx::lib::Math::near(cpm34.get_y(), T{ -3 }));
    static_assert(eqx::lib::Math::near(cpm35.get_x(), static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cpm35.get_y(), static_cast<T>(-2.5F)));
    static_assert(eqx::lib::Math::near(cpm36.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm36.get_y(), static_cast<T>(-1.5F)));
    static_assert(eqx::lib::Math::near(cpm37.get_x(), static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cpm37.get_y(), static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cpm40.get_x(), static_cast<T>(2.5F)));
    static_assert(eqx::lib::Math::near(cpm40.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cpm41.get_x(), static_cast<T>(1.5F)));
    static_assert(eqx::lib::Math::near(cpm41.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cpm42.get_x(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm42.get_y(), T{ 0 }));

    const auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    const auto p2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    const auto p3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };
    const auto p4 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 3 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 2 }, T{ 2 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };

    const auto pm10 = p1.midpoint(std::size_t{ 0 });
    const auto pm11 = p1.midpoint(std::size_t{ 1 });
    const auto pm12 = p1.midpoint(std::size_t{ 2 });
    const auto pm20 = p2.midpoint(std::size_t{ 0 });
    const auto pm21 = p2.midpoint(std::size_t{ 1 });
    const auto pm22 = p2.midpoint(std::size_t{ 2 });
    const auto pm23 = p2.midpoint(std::size_t{ 3 });
    const auto pm30 = p3.midpoint(std::size_t{ 0 });
    const auto pm31 = p3.midpoint(std::size_t{ 1 });
    const auto pm32 = p3.midpoint(std::size_t{ 2 });
    const auto pm33 = p3.midpoint(std::size_t{ 3 });
    const auto pm34 = p3.midpoint(std::size_t{ 4 });
    const auto pm35 = p3.midpoint(std::size_t{ 5 });
    const auto pm36 = p3.midpoint(std::size_t{ 6 });
    const auto pm37 = p3.midpoint(std::size_t{ 7 });
    const auto pm40 = p4.midpoint(std::size_t{ 0 });
    const auto pm41 = p4.midpoint(std::size_t{ 1 });
    const auto pm42 = p4.midpoint(std::size_t{ 2 });

    ASSERT_TRUE(eqx::lib::Math::near(pm10.get_x(), static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm10.get_y(), static_cast<T>(0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm11.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm11.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm12.get_x(), static_cast<T>(0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm12.get_y(), static_cast<T>(0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm20.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm20.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm21.get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm21.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm22.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm22.get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm23.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm23.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm30.get_x(), static_cast<T>(-1.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm30.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm31.get_x(), static_cast<T>(-2.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm31.get_y(), static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm32.get_x(), T{ -3 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm32.get_y(), static_cast<T>(-1.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm33.get_x(), static_cast<T>(-2.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm33.get_y(), static_cast<T>(-2.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm34.get_x(), static_cast<T>(-1.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm34.get_y(), T{ -3 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm35.get_x(), static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm35.get_y(), static_cast<T>(-2.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm36.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm36.get_y(), static_cast<T>(-1.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm37.get_x(), static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm37.get_y(), static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm40.get_x(), static_cast<T>(2.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm40.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm41.get_x(), static_cast<T>(1.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm41.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm42.get_x(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm42.get_y(), T{ 0 }));
}

template <typename T>
inline void polygon_normal() noexcept
{
    constexpr auto cp1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    constexpr auto cp2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    constexpr auto cp3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };
    constexpr auto cp4 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 3 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 2 }, T{ 2 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };

    constexpr auto cpm10 = cp1.normal(std::size_t{ 0 });
    constexpr auto cpm11 = cp1.normal(std::size_t{ 1 });
    constexpr auto cpm12 = cp1.normal(std::size_t{ 2 });
    constexpr auto cpm20 = cp2.normal(std::size_t{ 0 });
    constexpr auto cpm21 = cp2.normal(std::size_t{ 1 });
    constexpr auto cpm22 = cp2.normal(std::size_t{ 2 });
    constexpr auto cpm23 = cp2.normal(std::size_t{ 3 });
    constexpr auto cpm30 = cp3.normal(std::size_t{ 0 });
    constexpr auto cpm31 = cp3.normal(std::size_t{ 1 });
    constexpr auto cpm32 = cp3.normal(std::size_t{ 2 });
    constexpr auto cpm33 = cp3.normal(std::size_t{ 3 });
    constexpr auto cpm34 = cp3.normal(std::size_t{ 4 });
    constexpr auto cpm35 = cp3.normal(std::size_t{ 5 });
    constexpr auto cpm36 = cp3.normal(std::size_t{ 6 });
    constexpr auto cpm37 = cp3.normal(std::size_t{ 7 });
    constexpr auto cpm40 = cp4.normal(std::size_t{ 0 });
    constexpr auto cpm41 = cp4.normal(std::size_t{ 1 });
    constexpr auto cpm42 = cp4.normal(std::size_t{ 2 });

    static_assert(eqx::lib::Math::near(cpm10.get_x(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm10.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm11.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm11.get_y(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cpm12.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm12.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm20.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm20.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cpm21.get_x(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cpm21.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm22.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm22.get_y(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cpm23.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cpm23.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm30.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm30.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cpm31.get_x(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm31.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm32.get_x(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cpm32.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm33.get_x(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm33.get_y(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm34.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm34.get_y(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cpm35.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm35.get_y(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm36.get_x(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cpm36.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm37.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm37.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    static_assert(eqx::lib::Math::near(cpm40.get_x(), static_cast<T>(0.8944F)));
    static_assert(eqx::lib::Math::near(cpm40.get_y(), static_cast<T>(0.4472F)));
    static_assert(eqx::lib::Math::near(cpm41.get_x(),
        static_cast<T>(-0.8944F)));
    static_assert(eqx::lib::Math::near(cpm41.get_y(), static_cast<T>(0.4472F)));
    static_assert(eqx::lib::Math::near(cpm42.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpm42.get_y(), T{ -1 }));

    const auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    const auto p2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    const auto p3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };
    const auto p4 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 3 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 2 }, T{ 2 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };

    const auto pm10 = p1.normal(std::size_t{ 0 });
    const auto pm11 = p1.normal(std::size_t{ 1 });
    const auto pm12 = p1.normal(std::size_t{ 2 });
    const auto pm20 = p2.normal(std::size_t{ 0 });
    const auto pm21 = p2.normal(std::size_t{ 1 });
    const auto pm22 = p2.normal(std::size_t{ 2 });
    const auto pm23 = p2.normal(std::size_t{ 3 });
    const auto pm30 = p3.normal(std::size_t{ 0 });
    const auto pm31 = p3.normal(std::size_t{ 1 });
    const auto pm32 = p3.normal(std::size_t{ 2 });
    const auto pm33 = p3.normal(std::size_t{ 3 });
    const auto pm34 = p3.normal(std::size_t{ 4 });
    const auto pm35 = p3.normal(std::size_t{ 5 });
    const auto pm36 = p3.normal(std::size_t{ 6 });
    const auto pm37 = p3.normal(std::size_t{ 7 });
    const auto pm40 = p4.normal(std::size_t{ 0 });
    const auto pm41 = p4.normal(std::size_t{ 1 });
    const auto pm42 = p4.normal(std::size_t{ 2 });

    ASSERT_TRUE(eqx::lib::Math::near(pm10.get_x(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm10.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm11.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm11.get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm12.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm12.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm20.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm20.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm21.get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm21.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm22.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm22.get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm23.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm23.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm30.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm30.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm31.get_x(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm31.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm32.get_x(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm32.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm33.get_x(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm33.get_y(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm34.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm34.get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm35.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm35.get_y(),
        -std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm36.get_x(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm36.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm37.get_x(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm37.get_y(),
        std::numbers::sqrt2_v<T> / T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm40.get_x(), static_cast<T>(0.894427F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm40.get_y(), static_cast<T>(0.447214F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm41.get_x(), static_cast<T>(-0.894427F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm41.get_y(), static_cast<T>(0.447214F)));
    ASSERT_TRUE(eqx::lib::Math::near(pm42.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pm42.get_y(), T{ -1 }));
}

template <typename T>
inline void polygon_difference() noexcept
{
    constexpr auto cp1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    constexpr auto cp2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    constexpr auto cp3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };
    constexpr auto cp4 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 3 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 2 }, T{ 2 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };

    constexpr auto cpd11 = cp1.difference(cp1);
    constexpr auto cpd12 = cp1.difference(cp2);
    constexpr auto cpd13 = cp1.difference(cp3);
    constexpr auto cpd14 = cp1.difference(cp4);
    constexpr auto cpd21 = cp2.difference(cp1);
    constexpr auto cpd22 = cp2.difference(cp2);
    constexpr auto cpd23 = cp2.difference(cp3);
    constexpr auto cpd24 = cp2.difference(cp4);
    constexpr auto cpd31 = cp3.difference(cp1);
    constexpr auto cpd32 = cp3.difference(cp2);
    constexpr auto cpd33 = cp3.difference(cp3);
    constexpr auto cpd34 = cp3.difference(cp4);
    constexpr auto cpd41 = cp4.difference(cp1);
    constexpr auto cpd42 = cp4.difference(cp2);
    constexpr auto cpd43 = cp4.difference(cp3);
    constexpr auto cpd44 = cp4.difference(cp4);

    static_assert(eqx::lib::Math::near(cpd11.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpd11.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpd12.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpd12.get_y(), static_cast<T>(0.5F)));
    static_assert(eqx::lib::Math::near(cpd13.get_x(), static_cast<T>(1.5F)));
    static_assert(eqx::lib::Math::near(cpd13.get_y(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cpd14.get_x(), T{ -2 }));
    static_assert(eqx::lib::Math::near(cpd14.get_y(), static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cpd21.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpd21.get_y(), static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cpd22.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpd22.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpd23.get_x(), static_cast<T>(1.5F)));
    static_assert(eqx::lib::Math::near(cpd23.get_y(), static_cast<T>(1.5F)));
    static_assert(eqx::lib::Math::near(cpd24.get_x(), T{ -2 }));
    static_assert(eqx::lib::Math::near(cpd24.get_y(), T{ -1 }));
    static_assert(eqx::lib::Math::near(cpd31.get_x(), static_cast<T>(-1.5)));
    static_assert(eqx::lib::Math::near(cpd31.get_y(), T{ -2 }));
    static_assert(eqx::lib::Math::near(cpd32.get_x(), static_cast<T>(-1.5)));
    static_assert(eqx::lib::Math::near(cpd32.get_y(), static_cast<T>(-1.5)));
    static_assert(eqx::lib::Math::near(cpd33.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpd33.get_y(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpd34.get_x(), static_cast<T>(-3.5)));
    static_assert(eqx::lib::Math::near(cpd34.get_y(), static_cast<T>(-2.5)));
    static_assert(eqx::lib::Math::near(cpd41.get_x(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cpd41.get_y(), static_cast<T>(0.5F)));
    static_assert(eqx::lib::Math::near(cpd42.get_x(), T{ 2 }));
    static_assert(eqx::lib::Math::near(cpd42.get_y(), T{ 1 }));
    static_assert(eqx::lib::Math::near(cpd43.get_x(), static_cast<T>(3.5F)));
    static_assert(eqx::lib::Math::near(cpd43.get_y(), static_cast<T>(2.5F)));
    static_assert(eqx::lib::Math::near(cpd44.get_x(), T{ 0 }));
    static_assert(eqx::lib::Math::near(cpd44.get_y(), T{ 0 }));

    const auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    const auto p2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    const auto p3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };
    const auto p4 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 3 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 2 }, T{ 2 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };

    const auto pd11 = p1.difference(p1);
    const auto pd12 = p1.difference(p2);
    const auto pd13 = p1.difference(p3);
    const auto pd14 = p1.difference(p4);
    const auto pd21 = p2.difference(p1);
    const auto pd22 = p2.difference(p2);
    const auto pd23 = p2.difference(p3);
    const auto pd24 = p2.difference(p4);
    const auto pd31 = p3.difference(p1);
    const auto pd32 = p3.difference(p2);
    const auto pd33 = p3.difference(p3);
    const auto pd34 = p3.difference(p4);
    const auto pd41 = p4.difference(p1);
    const auto pd42 = p4.difference(p2);
    const auto pd43 = p4.difference(p3);
    const auto pd44 = p4.difference(p4);

    ASSERT_TRUE(eqx::lib::Math::near(pd11.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd11.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd12.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd12.get_y(), static_cast<T>(0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pd13.get_x(), static_cast<T>(1.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pd13.get_y(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd14.get_x(), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd14.get_y(), static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pd21.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd21.get_y(), static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pd22.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd22.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd23.get_x(), static_cast<T>(1.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pd23.get_y(), static_cast<T>(1.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pd24.get_x(), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd24.get_y(), T{ -1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd31.get_x(), static_cast<T>(-1.5)));
    ASSERT_TRUE(eqx::lib::Math::near(pd31.get_y(), T{ -2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd32.get_x(), static_cast<T>(-1.5)));
    ASSERT_TRUE(eqx::lib::Math::near(pd32.get_y(), static_cast<T>(-1.5)));
    ASSERT_TRUE(eqx::lib::Math::near(pd33.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd33.get_y(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd34.get_x(), static_cast<T>(-3.5)));
    ASSERT_TRUE(eqx::lib::Math::near(pd34.get_y(), static_cast<T>(-2.5)));
    ASSERT_TRUE(eqx::lib::Math::near(pd41.get_x(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd41.get_y(), static_cast<T>(0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pd42.get_x(), T{ 2 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd42.get_y(), T{ 1 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd43.get_x(), static_cast<T>(3.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pd43.get_y(), static_cast<T>(2.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(pd44.get_x(), T{ 0 }));
    ASSERT_TRUE(eqx::lib::Math::near(pd44.get_y(), T{ 0 }));
}

template <typename T>
inline void polygon_rectangle() noexcept
{
    constexpr auto cp1 = eqx::lib::Polygon<T, 4>::rectangle(T{ 1 }, T{ 1 });
    constexpr auto cp2 = eqx::lib::Polygon<T, 4>::rectangle(
        T{ 1920 }, T{ 1080 });

    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_x(),
        static_cast<T>(0.5F)));
    static_assert(eqx::lib::Math::near(cp1.get_data()[0].get_y(),
        static_cast<T>(0.5F)));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_x(),
        static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cp1.get_data()[1].get_y(),
        static_cast<T>(0.5F)));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_x(),
        static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cp1.get_data()[2].get_y(),
        static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cp1.get_data()[3].get_x(),
        static_cast<T>(0.5F)));
    static_assert(eqx::lib::Math::near(cp1.get_data()[3].get_y(),
        static_cast<T>(-0.5F)));
    static_assert(eqx::lib::Math::near(cp2.get_data()[0].get_x(), T{ 960 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[0].get_y(), T{ 540 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[1].get_x(), T{ -960 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[1].get_y(), T{ 540 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[2].get_x(), T{ -960 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[2].get_y(), T{ -540 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[3].get_x(), T{ 960 }));
    static_assert(eqx::lib::Math::near(cp2.get_data()[3].get_y(), T{ -540 }));

    const auto p1 = eqx::lib::Polygon<T, 4>::rectangle(T{ 1 }, T{ 1 });
    const auto p2 = eqx::lib::Polygon<T, 4>::rectangle(T{ 1920 }, T{ 1080 });

    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_x(),
        static_cast<T>(0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[0].get_y(),
        static_cast<T>(0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_x(),
        static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[1].get_y(),
        static_cast<T>(0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_x(),
        static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[2].get_y(),
        static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[3].get_x(),
        static_cast<T>(0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(p1.get_data()[3].get_y(),
        static_cast<T>(-0.5F)));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[0].get_x(), T{ 960 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[0].get_y(), T{ 540 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[1].get_x(), T{ -960 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[1].get_y(), T{ 540 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[2].get_x(), T{ -960 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[2].get_y(), T{ -540 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[3].get_x(), T{ 960 }));
    ASSERT_TRUE(eqx::lib::Math::near(p2.get_data()[3].get_y(), T{ -540 }));
}

template <typename T>
inline void polygon_size() noexcept
{
    constexpr auto cp1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    constexpr auto cp2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    constexpr auto cp3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };

    static_assert(cp1.size() == 3);
    static_assert(cp2.size() == 4);
    static_assert(cp3.size() == 8);

    const auto p1 = eqx::lib::Polygon<T, 3>{
        eqx::lib::Point<T>{ T{ 0 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ 0 } } };
    const auto p2 = eqx::lib::Polygon<T, 4>{
        eqx::lib::Point<T>{ T{ 1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ 1 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ 1 }, T{ -1 } } };
    const auto p3 = eqx::lib::Polygon<T, 8>{
        eqx::lib::Point<T>{ T{ -1 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ 0 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -1 } },
        eqx::lib::Point<T>{ T{ -3 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ -2 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ -1 }, T{ -3 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -2 } },
        eqx::lib::Point<T>{ T{ 0 }, T{ -1 } } };

    ASSERT_EQ(p1.size(), 3);
    ASSERT_EQ(p2.size(), 4);
    ASSERT_EQ(p3.size(), 8);
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_bounding_box)
{
    polygon_bounding_box<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_center)
{
    polygon_center<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_aabb)
{
    polygon_aabb<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_translate)
{
    polygon_translate<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_move)
{
    polygon_move<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_rotate)
{
    polygon_rotate<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_scale)
{
    polygon_scale<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_midpoint)
{
    polygon_midpoint<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_normal)
{
    polygon_normal<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_difference)
{
    polygon_difference<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_rectangle)
{
    polygon_rectangle<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, polygon_size)
{
    polygon_size<TypeParam>();
}
