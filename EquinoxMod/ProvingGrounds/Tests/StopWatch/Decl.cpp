export module Eqx.Tests.StopWatch:Decl;

import Eqx.Stdm;

namespace test::stopwatch
{
    export void all() noexcept;
    void readSeconds() noexcept;
    void toString() noexcept;
    void wasteTime(stdm::chrono::microseconds ms);
}
