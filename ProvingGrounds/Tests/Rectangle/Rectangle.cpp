export module Eqx.Tests.Rectangle;

import :Core;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Point;
import Equinox.Rectangle;
import Eqx.UnitTester;

namespace test::rectangle
{
    export inline UnitTester all() noexcept;
    inline void toString(UnitTester& tester) noexcept;
}

// Implementations

namespace test::rectangle
{
    export inline UnitTester all() noexcept
    {
        auto tester = UnitTester{};
        toString(tester);
        return tester;
    }

    inline void toString(UnitTester& tester) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto expected_actual =
            std::vector<std::pair<std::string, std::string>>{
                { "(1.000000, 1.000000, 1.000000, 1.000000)"s,
                    eqx::toString(eqx::Rectangle<double>{1.0, 1.0, 1.0, 1.0}) },
                { "(-10.000000, -10.000000, 3.000000, 15.000000)"s,
                    eqx::toString(eqx::Rectangle<double>{
                        -10.0, -10.0, 3.0, 15.0}) },
                { "(6.123000, -9.874000, 6.548000, 3.698000)"s,
                    eqx::toString(eqx::Rectangle<double>{
                        6.123, -9.874, 6.548, 3.698}) },
                { "(0.000000, 0.000000, 10.000000, 10.000000)"s,
                    eqx::toString(eqx::Rectangle<double>{
                        eqx::Point<double>{0.0, 0.0},
                        eqx::Point<double>{10.0, -10.0}}) },
                { "(-22.500000, 15.300000, 28.200000, 48.400000)"s,
                    eqx::toString(eqx::Rectangle<double>{
                        eqx::Point<double>{-22.5, 15.3},
                        eqx::Point<double>{5.7, -33.1}}) }
            };

        tester.addTests(expected_actual);
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }
}
