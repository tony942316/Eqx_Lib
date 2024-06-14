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
        //tester.print();
    }
}
