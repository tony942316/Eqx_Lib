// Timer.cpp

import Eqx.Lib.Math;
import Eqx.Lib.Timer;

import <Eqx/std.hpp>;

import <gtest.hpp>;

using namespace std::literals;

#ifndef CMAKE_TARGET_NAME
    static_assert(false, "CMAKE_TARGET_NAME not defined!");
#endif // CMAKE_TARGET_NAME

static_assert(std::semiregular<eqx::lib::Timer>);
static_assert(std::is_trivially_copyable_v<eqx::lib::Timer>);
static_assert(
    !std::is_trivially_default_constructible_v<eqx::lib::Timer>);
static_assert(std::is_standard_layout_v<eqx::lib::Timer>);

inline void timer_basic() noexcept
{
    constexpr auto ctimer = eqx::lib::Timer{};

    static_assert(eqx::lib::Math::near(ctimer.seconds(), 0.0));
    static_assert(eqx::lib::Math::near(ctimer.secondsf(), 0.0F));

    auto timer = eqx::lib::Timer{};

    timer.start();
    std::this_thread::sleep_for(1s);
    timer.end();

    ASSERT_GE(timer.seconds(), 1.0);
    ASSERT_GE(timer.secondsf(), 1.0F);
}

TEST(CMAKE_TARGET_NAME, timer_basic)
{
    timer_basic();
}
