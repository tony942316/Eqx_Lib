// Main.cpp

import <Eqx/std.hpp>;
import Eqx.Lib.Math;

using namespace std::literals;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);
    const auto num = 1.0149460139383671e+308;
    const auto want = std::sqrt(num);
    const auto got = eqx::lib::Math::sqrt(num);

    std::format_to(std::ostream_iterator<char>(std::cout),
        "num: {}\n"sv
        "want: {}\n"sv
        "got: {}\n"sv, num, want, got);

    std::format_to(std::ostream_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
