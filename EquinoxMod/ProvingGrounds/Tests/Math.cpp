export module Eqx.Tests.Math;

export import :Decl;
import :Core;
import :Range;
import :Trig;

import Eqx.Stdm;
import Equinox.Math;
import Eqx.UnitTester;

namespace test::math
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    constinit auto tester = UnitTester{};
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

    export void all() noexcept
    {
        stdm::cout << "Testing Math...\n";
        //tester.print();
    }
}
