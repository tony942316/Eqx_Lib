import <Eqx/std.hpp>;

import Eqx.Lib;

using namespace std::literals;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostreambuf_iterator<char>(std::cout), "Start\n\n"sv);

    std::format_to(std::ostreambuf_iterator<char>(std::cout),
        "eqx::lib::Math::hypot2(3, 4) = {}\n"sv, eqx::lib::Math::hypot2(3, 4));
    [[maybe_unused]] auto poly = eqx::lib::Poly<float, 4>{
        eqx::lib::Point<float>{1.0f, 1.0f},
        eqx::lib::Point<float>{0.0f, 1.0f},
        eqx::lib::Point<float>{0.0f, 0.0f},
        eqx::lib::Point<float>{1.0f, 0.0f}};
    [[maybe_unused]] auto poly2 = eqx::lib::Poly<float, 4>{
        eqx::lib::Point<float>{2.1f, 1.0f},
        eqx::lib::Point<float>{1.1f, 1.0f},
        eqx::lib::Point<float>{1.1f, 0.0f},
        eqx::lib::Point<float>{2.1f, 0.0f}};
    std::format_to(std::ostreambuf_iterator<char>(std::cout),
        "poly = \n{}\npoly2 = \n{}\n"sv, poly.to_string(), poly2.to_string());
    std::format_to(std::ostreambuf_iterator<char>(std::cout),
        "aabb = {} = {}\n"sv, poly.aabb(poly2), poly2.aabb(poly));

    std::format_to(std::ostreambuf_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
