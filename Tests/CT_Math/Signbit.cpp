// Signbit.cpp

import Eqx.Lib.CT_Math;

import <Eqx/std.hpp>;

import <gtest.hpp>;

#ifndef CMAKE_TARGET_NAME
    static_assert(false, "CMAKE_TARGET_NAME not defined!");
#endif // CMAKE_TARGET_NAME

template <typename T>
[[nodiscard]] consteval bool signbit_prove_callability() noexcept
{
    static_assert(std::is_const_v<T> == false);
    static_assert(std::is_volatile_v<T> == false);
    static_assert(std::is_reference_v<T> == false);

    static_assert(requires { eqx::lib::CT_Math::signbit(T{}); });

    static_assert(requires { eqx::lib::CT_Math::signbit(std::declval<T&>()); });
    static_assert(requires
        { eqx::lib::CT_Math::signbit(std::declval<const T&>()); });
    static_assert(requires
        { eqx::lib::CT_Math::signbit(std::declval<volatile T&>()); });
    static_assert(requires
        { eqx::lib::CT_Math::signbit(std::declval<const volatile T&>()); });

    static_assert(requires
        { eqx::lib::CT_Math::signbit(std::declval<T&&>()); });
    static_assert(requires
        { eqx::lib::CT_Math::signbit(std::declval<const T&&>()); });
    static_assert(requires
        { eqx::lib::CT_Math::signbit(std::declval<volatile T&&>()); });
    static_assert(requires
        { eqx::lib::CT_Math::signbit(std::declval<const volatile T&&>()); });

    return true;
}

template <typename T>
[[nodiscard]] consteval bool signbit_constexpr_sampler() noexcept
{
    // for (T m : {T{1e-45}, T{1e-37}, T{1e-20}, T{1e-10}, T{1e-5}, T{1}, T{10}, T{1e10}}) {

    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e-37F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e-30F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e-23F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e-20F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e-17F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e-10F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(T{ 0 }) == false);
    static_assert(eqx::lib::CT_Math::signbit(T{ 1 }) == false);
    static_assert(eqx::lib::CT_Math::signbit(T{ 10 }) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e10F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e17F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e20F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e23F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e30F)) == false);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(1e37F)) == false);

    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e-37F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e-30F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e-23F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e-20F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e-17F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e-10F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(T{ -1 }) == true);
    static_assert(eqx::lib::CT_Math::signbit(T{ -10 }) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e10F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e17F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e20F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e23F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e30F)) == true);
    static_assert(eqx::lib::CT_Math::signbit(static_cast<T>(-1e37F)) == true);

    return true;
}

static_assert(signbit_prove_callability<float>());
static_assert(signbit_prove_callability<double>());
static_assert(signbit_prove_callability<long double>());

static_assert(signbit_constexpr_sampler<float>());
static_assert(signbit_constexpr_sampler<double>());
static_assert(signbit_constexpr_sampler<long double>());

template<class T>
class CMAKE_TARGET_NAME : public ::testing::Test
{
};
using My_Types = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(CMAKE_TARGET_NAME, My_Types);

template <typename T>
inline void signbit_callability() noexcept
{
    EXPECT_EQ(eqx::lib::CT_Math::signbit(T{ -1 }), std::signbit(T{ -1 }));

    T lv = T{ -1 };
    const T clv = T{ -1 };
    volatile T vlv = T{ -1 };
    const volatile T cvlv = T{ -1 };

    EXPECT_EQ(eqx::lib::CT_Math::signbit(lv), std::signbit(lv));
    EXPECT_EQ(eqx::lib::CT_Math::signbit(clv), std::signbit(clv));
    EXPECT_EQ(eqx::lib::CT_Math::signbit(vlv), std::signbit(vlv));
    EXPECT_EQ(eqx::lib::CT_Math::signbit(cvlv), std::signbit(cvlv));

    T& ref = lv;
    const T& cref = lv;
    const T& crefc = clv;

    EXPECT_EQ(eqx::lib::CT_Math::signbit(ref), std::signbit(ref));
    EXPECT_EQ(eqx::lib::CT_Math::signbit(cref), std::signbit(cref));
    EXPECT_EQ(eqx::lib::CT_Math::signbit(crefc), std::signbit(crefc));
}

template <typename T>
inline void signbit_edge() noexcept
{
    EXPECT_EQ(eqx::lib::CT_Math::signbit(T{ 0 }), std::signbit(T{ 0 }));
}

template <typename T>
    requires std::floating_point<T>
inline constexpr auto eps = static_cast<T>(0.001);

template <typename T>
inline void signbit_narrow_sweep() noexcept
{
    for (auto i = eps<T>; i < T{ 10'000 }; i += eps<T>)
    {
        EXPECT_EQ(eqx::lib::CT_Math::signbit(i), std::signbit(i))
            << "i: " << i;
        EXPECT_EQ(eqx::lib::CT_Math::signbit(-i), std::signbit(-i))
            << "i: " << i;
        EXPECT_NE(eqx::lib::CT_Math::signbit(i), std::signbit(-i))
            << "i: " << i;
        EXPECT_NE(eqx::lib::CT_Math::signbit(-i), std::signbit(i))
            << "i: " << i;
    }
}

template <typename T>
inline void signbit_broad_sweep() noexcept
{
    for (auto i = T{ 10'000 }; i < T{ 15'000'000 }; i += T{ 1 })
    {
        EXPECT_EQ(eqx::lib::CT_Math::signbit(i), std::signbit(i))
            << "i: " << i;
        EXPECT_EQ(eqx::lib::CT_Math::signbit(-i), std::signbit(-i))
            << "i: " << i;
        EXPECT_NE(eqx::lib::CT_Math::signbit(i), std::signbit(-i))
            << "i: " << i;
        EXPECT_NE(eqx::lib::CT_Math::signbit(-i), std::signbit(i))
            << "i: " << i;
    }
}

template <typename T>
inline void signbit_fuzz_canonical() noexcept
{
    auto rd = std::random_device{};
    auto seed = std::seed_seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    auto eng = std::mt19937_64{ seed };

    auto num = T{ 0 };
    for (auto i = 0; i < 20'000'000; ++i)
    {
        num = std::generate_canonical<T, 128>(eng);
        EXPECT_EQ(eqx::lib::CT_Math::signbit(num), std::signbit(num))
            << "num: " << num;
        EXPECT_EQ(eqx::lib::CT_Math::signbit(-num), std::signbit(-num))
            << "num: " << num;
        EXPECT_NE(eqx::lib::CT_Math::signbit(num), std::signbit(-num))
            << "num: " << num;
        EXPECT_NE(eqx::lib::CT_Math::signbit(-num), std::signbit(num))
            << "num: " << num;
    }
}

template <typename T>
inline void signbit_fuzz_narrow() noexcept
{
    auto rd = std::random_device{};
    auto seed = std::seed_seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    auto eng = std::mt19937_64{ seed };
    auto dist =
        std::uniform_real_distribution<T>{ T{ 0 }, T{ 10'000 } };

    auto num = T{ 0 };
    for (auto i = 0; i < 20'000'000; ++i)
    {
        num = dist(eng);
        EXPECT_EQ(eqx::lib::CT_Math::signbit(num), std::signbit(num))
            << "num: " << num;
        EXPECT_EQ(eqx::lib::CT_Math::signbit(-num), std::signbit(-num))
            << "num: " << num;
        EXPECT_NE(eqx::lib::CT_Math::signbit(num), std::signbit(-num))
            << "num: " << num;
        EXPECT_NE(eqx::lib::CT_Math::signbit(-num), std::signbit(num))
            << "num: " << num;
    }
}

template <typename T>
inline void signbit_fuzz_broad() noexcept
{
    auto rd = std::random_device{};
    auto seed = std::seed_seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    auto eng = std::mt19937_64{ seed };
    auto dist =
        std::uniform_real_distribution<T>{ T{ 10'000 }, T{ 15'000'000 } };

    auto num = T{ 0 };
    for (auto i = 0; i < 20'000'000; ++i)
    {
        num = dist(eng);
        EXPECT_EQ(eqx::lib::CT_Math::signbit(num), std::signbit(num))
            << "num: " << num;
        EXPECT_EQ(eqx::lib::CT_Math::signbit(-num), std::signbit(-num))
            << "num: " << num;
        EXPECT_NE(eqx::lib::CT_Math::signbit(num), std::signbit(-num))
            << "num: " << num;
        EXPECT_NE(eqx::lib::CT_Math::signbit(-num), std::signbit(num))
            << "num: " << num;
    }
}

template <typename T>
inline void signbit_fuzz_whole() noexcept
{
    auto rd = std::random_device{};
    auto seed = std::seed_seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    auto eng = std::mt19937_64{ seed };
    auto dist = std::uniform_real_distribution<T>{
        T{ 0 }, std::numeric_limits<T>::max() };

    auto num = T{ 0 };
    for (auto i = 0; i < 20'000'000; ++i)
    {
        num = dist(eng);
        EXPECT_EQ(eqx::lib::CT_Math::signbit(num), std::signbit(num))
            << "num: " << num;
        EXPECT_EQ(eqx::lib::CT_Math::signbit(-num), std::signbit(-num))
            << "num: " << num;
        EXPECT_NE(eqx::lib::CT_Math::signbit(num), std::signbit(-num))
            << "num: " << num;
        EXPECT_NE(eqx::lib::CT_Math::signbit(-num), std::signbit(num))
            << "num: " << num;
    }
}

TYPED_TEST(CMAKE_TARGET_NAME, signbit_callability)
{
    signbit_callability<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, signbit_edge)
{
    signbit_edge<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, signbit_narrow_sweep)
{
    signbit_narrow_sweep<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, signbit_broad_sweep)
{
    signbit_broad_sweep<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, signbit_fuzz_canonical)
{
    signbit_fuzz_canonical<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, signbit_fuzz_narrow)
{
    signbit_fuzz_narrow<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, signbit_fuzz_broad)
{
    signbit_fuzz_broad<TypeParam>();
}

TYPED_TEST(CMAKE_TARGET_NAME, signbit_fuzz_whole)
{
    signbit_fuzz_whole<TypeParam>();
}
