// Main.cpp

import <Eqx/std.hpp>;
import Eqx.Lib.Math;
import Eqx.Lib.CMath;
import Eqx.Lib.Point;

using namespace std::literals;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);

    [[maybe_unused]] auto num = 0.0F;
    [[maybe_unused]] auto p1 = eqx::lib::Point<float>{ 1.0F, 1.0F };
    [[maybe_unused]] auto p2 = eqx::lib::Point<float>{ -1.0F, -1.0F };

    const auto want = 8.0F;
    const auto got = p1.distance2(p2);

    std::format_to(std::ostream_iterator<char>(std::cout),
        "want: {:.8f}\n"sv
        "got: {:.8f}\n"sv, want, got);

    std::format_to(std::ostream_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
