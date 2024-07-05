export module Eqx.Tests.StopWatch;

import Eqx.Stdm;
import Equinox.StopWatch;
import Eqx.UnitTester;

namespace test::stopwatch
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    constinit inline auto tester = UnitTester{};
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

    export inline void all() noexcept;
    void inline readSeconds() noexcept;
    void inline toString() noexcept;
    void inline wasteTime(stdm::chrono::microseconds ms);
}

// Implementations

namespace test::stopwatch
{
    export inline void all() noexcept
    {
        stdm::cout << "Testing StopWatch...\n";
        readSeconds();
        toString();
        tester.print();
    }

    inline void readSeconds() noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto watch = eqx::StopWatch{};
        watch.start();
        wasteTime(1s);
        const auto result = watch.readSeconds();

        tester.addTest(result, 1.0, stdm::ranges::greater_equal{});
        tester.addTest(result, 5.0, stdm::ranges::less_equal{});
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    inline void toString() noexcept
    {
        using namespace eqx::TimeTypes;

        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto watch = eqx::StopWatch{};
        watch.start();
        wasteTime(1s);
        watch.stop();

        tester.addTest(stdm::to_string(watch.getTime<t_NS>()) + "ns"s,
            watch.toString<t_NS>());
        tester.addTest(stdm::to_string(watch.getTime<t_US>()) + "us"s,
            watch.toString<t_US>());
        tester.addTest(stdm::to_string(watch.getTime<t_MS>()) + "ms"s,
            watch.toString<t_MS>());
        tester.addTest(stdm::to_string(watch.getTime<t_S>()) + "s"s,
            watch.toString<t_S>());
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    inline void wasteTime(stdm::chrono::microseconds ms)
    {
        stdm::this_thread::sleep_for(ms);
    }
}
