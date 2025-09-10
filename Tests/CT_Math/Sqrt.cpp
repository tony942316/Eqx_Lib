// Sqrt.cpp

import Eqx.Lib.Math;

import <Eqx/std.hpp>;

import <gtest.hpp>;

#ifndef CMAKE_TARGET_NAME
    static_assert(false, "CMAKE_TARGET_NAME not defined!");
#endif // CMAKE_TARGET_NAME

template <typename T>
[[nodiscard]] consteval bool sqrt_prove_callability() noexcept
{
    static_assert(std::is_const_v<T> == false);
    static_assert(std::is_volatile_v<T> == false);
    static_assert(std::is_reference_v<T> == false);

    static_assert(requires { eqx::lib::Math::sqrt(T{}); });

    static_assert(requires { eqx::lib::Math::sqrt(std::declval<T&>()); });
    static_assert(requires
        { eqx::lib::Math::sqrt(std::declval<const T&>()); });
    static_assert(requires
        { eqx::lib::Math::sqrt(std::declval<volatile T&>()); });
    static_assert(requires
        { eqx::lib::Math::sqrt(std::declval<const volatile T&>()); });

    static_assert(requires
        { eqx::lib::Math::sqrt(std::declval<T&&>()); });
    static_assert(requires
        { eqx::lib::Math::sqrt(std::declval<const T&&>()); });
    static_assert(requires
        { eqx::lib::Math::sqrt(std::declval<volatile T&&>()); });
    static_assert(requires
        { eqx::lib::Math::sqrt(std::declval<const volatile T&&>()); });

    return true;
}

template <typename T>
[[nodiscard]] consteval bool sqrt_constexpr_sampler() noexcept
{
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 0 }), T{ 0 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 1 }), T{ 1 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 4 }), T{ 2 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 9 }), T{ 3 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 16 }), T{ 4 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 25 }), T{ 5 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 36 }), T{ 6 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 100 }), T{ 10 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 10'000 }), T{ 100 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 1'000'000 }), T{ 1'000 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 6'250'000 }), T{ 2'500 }));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 25'000'000 }), T{ 5'000 }));

    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 2 }), std::numbers::sqrt2_v<T>));
    static_assert(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 3 }), std::numbers::sqrt3_v<T>));
    static_assert(eqx::lib::Math::near(
        T{ 1 } / eqx::lib::Math::sqrt(T{ 3 }), std::numbers::inv_sqrt3_v<T>));
    static_assert(eqx::lib::Math::near(
        T{ 1 } / eqx::lib::Math::sqrt(std::numbers::pi_v<T>),
        std::numbers::inv_sqrtpi_v<T>));

    return true;
}

static_assert(sqrt_prove_callability<float>());
static_assert(sqrt_prove_callability<double>());
static_assert(sqrt_prove_callability<long double>());

static_assert(sqrt_constexpr_sampler<float>());
static_assert(sqrt_constexpr_sampler<double>());
static_assert(sqrt_constexpr_sampler<long double>());

static_assert(eqx::lib::Math::near(
    eqx::lib::Math::c_fpt<float>, 0.001F, 1E-10F));
static_assert(eqx::lib::Math::near(
    eqx::lib::Math::c_fpt<double>, 0.001, 1E-10));
static_assert(eqx::lib::Math::near(
    eqx::lib::Math::c_fpt<long double>, 0.001L, 1E-10L));

template<class T>
class CMAKE_TARGET_NAME : public ::testing::Test
{
};
using My_Types = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(CMAKE_TARGET_NAME, My_Types);

template <typename T>
inline void sqrt_callability() noexcept
{
    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 0 }), std::sqrt(T{ 0 })));

    T lv = T{ 0 };
    const T clv = T{ 0 };
    volatile T vlv = T{ 0 };
    const volatile T cvlv = T{ 0 };

    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(lv), std::sqrt(lv)));
    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(clv), std::sqrt(clv)));
    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(vlv), std::sqrt(vlv)));
    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(cvlv), std::sqrt(cvlv)));

    T& ref = lv;
    const T& cref = lv;
    const T& crefc = clv;

    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(ref), std::sqrt(ref)));
    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(cref), std::sqrt(cref)));
    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(crefc), std::sqrt(crefc)));
}

template <typename T>
inline void sqrt_edge() noexcept
{
    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 0 }), std::sqrt(T{ 0 })));
    EXPECT_TRUE(eqx::lib::Math::near(
        eqx::lib::Math::sqrt(T{ 1 }), std::sqrt(T{ 1 })));
}

template <typename T>
inline void sqrt_narrow_sweep() noexcept
{
    auto want = T{ 0 };
    auto got = T{ 0 };
    auto diff = T{ 0 };
    for (auto i = static_cast<T>(0.001F); i < T{ 10'000 };
        i += static_cast<T>(0.001F))
    {
        want = std::sqrt(i);
        got = eqx::lib::Math::sqrt(i);
        diff = std::abs(want - got);
        ASSERT_TRUE(eqx::lib::Math::near(want, got))
            << "i: " << i << '\n' << "Want: " << want << '\n'
            << "Got:  " << got << '\n' << "Diff: " << diff;
    }
}

template <typename T>
inline void sqrt_broad_sweep() noexcept
{
    auto want = T{ 0 };
    auto got = T{ 0 };
    auto diff = T{ 0 };
    for (auto i = T{ 10'000 }; i < T{ 15'000'000 }; i += T{ 1 })
    {
        want = std::sqrt(i);
        got = eqx::lib::Math::sqrt(i);
        diff = std::abs(want - got);
        ASSERT_TRUE(eqx::lib::Math::near(want, got))
            << "i: " << i << '\n' << "Want: " << want << '\n'
            << "Got:  " << got << '\n' << "Diff: " << diff;
    }
}

template <typename T>
inline void sqrt_fuzz_canonical() noexcept
{
    auto rd = std::random_device{};
    auto seed = std::seed_seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    auto eng = std::mt19937_64{ seed };

    auto num = T{ 0 };
    auto want = T{ 0 };
    auto got = T{ 0 };
    auto diff = T{ 0 };
    for (auto i = 0; i < 20'000'000; ++i)
    {
        num = std::generate_canonical<T, std::numeric_limits<T>::digits>(eng);
        want = std::sqrt(num);
        got = eqx::lib::Math::sqrt(num);
        diff = std::abs(want - got);
        ASSERT_TRUE(eqx::lib::Math::near(want, got))
            << "Num: " << num << '\n' << "Want: " << want << '\n'
            << "Got:  " << got << '\n' << "Diff: " << diff;
    }
}

template <typename T>
inline void sqrt_fuzz_narrow() noexcept
{
    auto rd = std::random_device{};
    auto seed = std::seed_seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    auto eng = std::mt19937_64{ seed };
    auto dist = std::uniform_real_distribution<T>{ T{ 0 }, T{ 10'000 } };

    auto num = T{ 0 };
    auto want = T{ 0 };
    auto got = T{ 0 };
    auto diff = T{ 0 };
    for (auto i = 0; i < 20'000'000; ++i)
    {
        num = dist(eng);
        want = std::sqrt(num);
        got = eqx::lib::Math::sqrt(num);
        diff = std::abs(want - got);
        ASSERT_TRUE(eqx::lib::Math::near(want, got))
            << "Num: " << num << '\n' << "Want: " << want << '\n'
            << "Got:  " << got << '\n' << "Diff: " << diff;
    }
}

template <typename T>
inline void sqrt_fuzz_broad() noexcept
{
    auto rd = std::random_device{};
    auto seed = std::seed_seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    auto eng = std::mt19937_64{ seed };
    auto dist =
        std::uniform_real_distribution<T>{ T{ 10'000 }, T{ 15'000'000 } };

    auto num = T{ 0 };
    auto want = T{ 0 };
    auto got = T{ 0 };
    auto diff = T{ 0 };
    for (auto i = 0; i < 20'000'000; ++i)
    {
        num = dist(eng);
        want = std::sqrt(num);
        got = eqx::lib::Math::sqrt(num);
        diff = std::abs(want - got);
        ASSERT_TRUE(eqx::lib::Math::near(want, got))
            << "Num: " << num << '\n' << "Want: " << want << '\n'
            << "Got:  " << got << '\n' << "Diff: " << diff;
    }
}

template <typename T>
inline void sqrt_fuzz_whole() noexcept
{
    auto rd = std::random_device{};
    auto seed = std::seed_seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    auto eng = std::mt19937_64{ seed };
    auto dist = std::uniform_real_distribution<T>{
        T{ 0 }, std::numeric_limits<T>::max() };

    auto num = T{ 0 };
    auto want = T{ 0 };
    auto got = T{ 0 };
    auto diff = T{ 0 };
    for (auto i = 0; i < 2'000'000; ++i)
    {
        num = dist(eng);
        want = std::sqrt(num);
        got = eqx::lib::Math::sqrt(num);
        diff = std::abs(want - got);
        ASSERT_TRUE(eqx::lib::Math::near(want, got))
            << "Num: " << num << '\n' << "Want: " << want << '\n'
            << "Got:  " << got << '\n' << "Diff: " << diff;
    }
}

TYPED_TEST(CMAKE_TARGET_NAME, sqrt_callability)
{
    sqrt_callability<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, sqrt_edge)
{
    sqrt_edge<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, sqrt_narrow_sweep)
{
    sqrt_narrow_sweep<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, sqrt_broad_sweep)
{
    sqrt_broad_sweep<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, sqrt_fuzz_canonical)
{
    sqrt_fuzz_canonical<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, sqrt_fuzz_narrow)
{
    sqrt_fuzz_narrow<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, sqrt_fuzz_broad)
{
    sqrt_fuzz_broad<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, sqrt_fuzz_whole)
{
    sqrt_fuzz_whole<TypeParam>();
}
