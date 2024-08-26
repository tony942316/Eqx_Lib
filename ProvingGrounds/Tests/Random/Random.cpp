export module Eqx.Tests.Random;

#include <Eqx/std.hpp>

import Eqx.Lib.Misc;
import Eqx.Lib.Random;
import Eqx.UnitTester;

namespace test::random
{
    export inline UnitTester all() noexcept;
    inline void num(UnitTester& tester) noexcept;
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
        num(tester);
        flip(tester);
        dice(tester);
        seed(tester);
        return tester;
    }

    inline void num(UnitTester& tester) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto testRange =
            [&tester]<typename T>
                requires std::is_arithmetic_v<T>
            (const T lb, const T ub)
            {
                constexpr auto trials = 1'000'000;

                const auto tolerance = (std::abs((static_cast<double>(ub)
                    * static_cast<double>(trials))
                    - (static_cast<double>(lb) * static_cast<double>(trials))))
                    * 0.005;

                const auto expectedCount =
                    ((static_cast<double>(ub) / 2.0)
                        + (static_cast<double>(lb) / 2.0))
                    * static_cast<double>(trials);

                auto total = 0.0;
                for (auto i = 0; i < trials; ++i)
                {
                    total += static_cast<double>(eqx::randomNumber(lb, ub));
                }

                const auto error =
                    std::abs(total - expectedCount)
                    / tolerance;

                tester.addTest(error, 1.0, std::ranges::less{});
            };

        testRange(0, 1);
        testRange(0U, 1U);
        testRange(0L, 1L);
        testRange(0UL, 1UL);
        testRange(0LL, 1LL);
        testRange(0ULL, 1ULL);
        testRange(0, 100);
        testRange(50, 100);
        testRange(-100, -50);
        testRange(-1, 1);
        testRange(-5, 10);
        testRange(-10, 5);
        testRange(-100, 100);
        testRange(-1'000, 1'000);
        testRange(-10'000, 10'000);
        testRange(-100'000, 100'000);
        testRange(-1'000'000, 1'000'000);
        testRange(-10'000'000, 10'000'000);

        testRange(0.0F, 1.0F);
        testRange(0.0, 1.0);
        testRange(0.0L, 1.0L);
        testRange(-1.0, 1.0);
        testRange(-5.0, 10.0);
        testRange(-10.0, 5.0);
        testRange(-10'000'000.0, 10'000'000.0);
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
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

        auto error = std::abs(1.0
            - (expectedCount / static_cast<double>(total)));
        tester.addTest(error, 0.01, std::ranges::less{});
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

        auto error = std::abs(1.0
            - (expectedCount / static_cast<double>(total)));
        tester.addTest(error, 0.01, std::ranges::less{});
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    inline void seed(UnitTester& tester) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        constexpr auto trials = 1'000'000;

        auto values = std::unordered_set<unsigned int>{};
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
        tester.addTest(error, 0.001, std::ranges::less{});
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }
}
