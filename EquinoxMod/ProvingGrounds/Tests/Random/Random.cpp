export module Eqx.Tests.Random;

import :Core;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Random;
import Eqx.UnitTester;

namespace test::random
{
    export inline UnitTester all() noexcept;
    inline void intNum(UnitTester& tester) noexcept;
    inline void floatNum(UnitTester& tester) noexcept;
    inline void flip(UnitTester& tester) noexcept;
    inline void dice(UnitTester& tester) noexcept;
    inline void seed(UnitTester& tester) noexcept;
}

// Implementations

namespace test::random
{
    export inline UnitTester all() noexcept
    {
        auto tester = UnitTester{};
        intNum(tester);
        floatNum(tester);
        flip(tester);
        dice(tester);
        seed(tester);
        return tester;
    }

    inline void intNum(UnitTester& tester) noexcept
    {

    }

    inline void floatNum(UnitTester& tester) noexcept
    {

    }

    inline void flip(UnitTester& tester) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        constexpr auto trials = 1'000'000;
        constexpr auto expectedCount = static_cast<double>(trials) / 2.0;

        auto total = 0U;
        for (auto i = 0; i < trials; ++i)
        {
            total += eqx::flipCoin();
        }

        auto error = stdm::abs(1.0
            - (expectedCount / static_cast<double>(total)));
        tester.addTest(error, 0.01, stdm::ranges::less{});
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    inline void dice(UnitTester& tester) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        constexpr auto trials = 1'000'000;
        constexpr auto sides = 6U;

        constexpr auto sum = (sides * (sides + 1)) / 2;
        constexpr auto expectedCount = (trials / 6.0) * sum;

        auto total = 0U;
        for (auto i = 0; i < trials; ++i)
        {
            total += eqx::rollDice(sides);
        }

        auto error = stdm::abs(1.0
            - (expectedCount / static_cast<double>(total)));
        tester.addTest(error, 0.01, stdm::ranges::greater{});
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    inline void seed(UnitTester& tester) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        constexpr auto trials = 1'000'000;

        auto values = stdm::unordered_set<unsigned int>{};
        values.reserve(trials);
        auto collisions = 0U;
        auto value = 0U;
        for (auto i = 0; i < trials; ++i)
        {
            value = eqx::generateSeed();
            if (values.contains(value))
            {
                ++collisions;
            }
            else
            {
                values.emplace(value);
            }
        }

        auto error = static_cast<double>(collisions)
            / static_cast<double>(trials);
        tester.addTest(error, 0.001, stdm::ranges::less{});
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }
}
