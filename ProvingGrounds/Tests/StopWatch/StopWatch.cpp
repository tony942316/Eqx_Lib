export module Eqx.Tests.StopWatch;

#include <Eqx/std.hpp>

import Eqx.Lib.Misc;
import Eqx.Lib.StopWatch;
import Eqx.UnitTester;

using namespace std::literals;

static_assert(std::is_standard_layout_v<eqx::StopWatch>);
static_assert(!std::is_trivial_v<eqx::StopWatch>);

static_assert(!std::is_trivially_default_constructible_v<eqx::StopWatch>);

static_assert(std::is_trivially_copyable_v<eqx::StopWatch>);

namespace test::stopwatch
{
    export inline UnitTester all() noexcept;
    void inline readSeconds(UnitTester& tester) noexcept;
    void inline toString(UnitTester& tester) noexcept;
    void inline wasteTime(std::chrono::microseconds ms);
}

// Implementations

namespace test::stopwatch
{
    export inline UnitTester all() noexcept
    {
        auto tester = UnitTester{};
        readSeconds(tester);
        toString(tester);
        return tester;
    }

    inline void readSeconds(UnitTester& tester) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto watch = eqx::StopWatch{};
        watch.start();
        wasteTime(1s);
        const auto result = watch.readSeconds();

        tester.addTest(result, 1.0, std::ranges::greater_equal{});
        tester.addTest(result, 5.0, std::ranges::less_equal{});
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    inline void toString(UnitTester& tester) noexcept
    {
        using namespace eqx::TimeTypes;

        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto watch = eqx::StopWatch{};
        watch.start();
        wasteTime(1s);
        watch.stop();

        tester.addTest(std::to_string(watch.getTime<t_NS>()) + "ns"s,
            watch.toString<t_NS>());
        tester.addTest(std::to_string(watch.getTime<t_US>()) + "us"s,
            watch.toString<t_US>());
        tester.addTest(std::to_string(watch.getTime<t_MS>()) + "ms"s,
            watch.toString<t_MS>());
        tester.addTest(std::to_string(watch.getTime<t_S>()) + "s"s,
            watch.toString<t_S>());
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    inline void wasteTime(std::chrono::microseconds ms)
    {
        std::this_thread::sleep_for(ms);
    }
}
