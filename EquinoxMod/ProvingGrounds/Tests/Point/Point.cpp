export module Eqx.Tests.Point;

export import :Decl;
import :Core;

import Eqx.Stdm;
import Equinox.Point;
import Eqx.UnitTester;

namespace test::point
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    constinit auto tester = UnitTester{};
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

    export void all() noexcept
    {
        stdm::cout << "Testing Point...\n";
        toString();
        tester.print();
    }

    void toString() noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto expected_actual =
            stdm::vector<stdm::pair<stdm::string, stdm::string>>{
                { "(0, 0)"s, eqx::toString(eqx::Point<int>{0, 0}) },
                { "(0.000000, 0.000000)"s,
                    eqx::toString(eqx::Point<float>{0.0F, 0.0F}) },
                { "(0.000000, 0.000000)"s,
                    eqx::toString(eqx::Point<double>{0.0, 0.0}) },
                { "(0.000000, 0.000000)"s,
                    eqx::toString(eqx::Point<long double>{0.0L, 0.0L}) },
                { "(1.500000, 3.900000)"s,
                    eqx::toString(eqx::Point<double>{1.5, 3.9}) },
                { "(1.000000, 1.000000)"s,
                    eqx::toString(eqx::Point<double>{1.0, 1.0}) },
                { "(-10.000000, 10.000000)"s,
                    eqx::toString(eqx::Point<double>{-10.0, 10.0}) },
                { "(1.234000, 7.654000)"s,
                    eqx::toString(eqx::Point<double>{1.234, 7.654}) }
            };

        tester.addTests(expected_actual);

        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }
}
