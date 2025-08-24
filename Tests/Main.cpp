// Main.cpp

import <Eqx/std.hpp>;
import Eqx.Lib;
import Eqx.Lib.CT_Math;

using namespace std::literals;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostreambuf_iterator<char>(std::cout), "Start\n\n"sv);

    std::format_to(std::ostreambuf_iterator<char>(std::cout),
        "eqx::lib::Math::hypot2(3, 4) = {}\n"sv, eqx::lib::Math::hypot2(3, 4));
    [[maybe_unused]] auto poly = eqx::lib::PolyF<4>{
        eqx::lib::PointF{1.0f, 1.0f},
        eqx::lib::PointF{0.0f, 1.0f},
        eqx::lib::PointF{0.0f, 0.0f},
        eqx::lib::PointF{1.0f, 0.0f}};
    [[maybe_unused]] auto poly2 = eqx::lib::PolyF<4>{
        eqx::lib::PointF{2.0f, 1.0f},
        eqx::lib::PointF{1.0f, 1.0f},
        eqx::lib::PointF{1.0f, 0.0f},
        eqx::lib::PointF{2.0f, 0.0f}};
    [[maybe_unused]] auto poly3 = eqx::lib::PolyF<4>{
        eqx::lib::PointF{2.1f, 1.0f},
        eqx::lib::PointF{1.1f, 1.0f},
        eqx::lib::PointF{1.1f, 0.0f},
        eqx::lib::PointF{2.1f, 0.0f}};
    std::format_to(std::ostreambuf_iterator<char>(std::cout),
        "poly = \n{}\npoly2 = \n{}\n"sv, poly.to_string(), poly2.to_string());
    std::format_to(std::ostreambuf_iterator<char>(std::cout),
        "aabb = {} = {}\n"sv, poly.aabb(poly2), poly2.aabb(poly));

    if (poly.aabb(poly2) != true
        || poly2.aabb(poly) != true)
    {
        return EXIT_FAILURE;
    }
    if (poly.aabb(poly3) == true
        || poly3.aabb(poly) == true)
    {
        return EXIT_FAILURE;
    }

    auto p1 = eqx::lib::PointF{ 1.0f, 0.0f };
    for (auto i = 0; i < 90; ++i)
    {
        p1.rot(eqx::lib::Math::to_radians(1.0F));
    }
    std::format_to(std::ostreambuf_iterator<char>(std::cout),
        "p1 = {}\n"sv, p1.to_string());

    auto p2 = eqx::lib::PointF{ 1.0f, 0.0f };
    p2.rot(eqx::lib::Math::to_radians(90.0F));
    std::format_to(std::ostreambuf_iterator<char>(std::cout),
        "p2 = {}\n"sv, p2.to_string());

    std::format_to(std::ostreambuf_iterator<char>(std::cout),
        "std::sin = {}\n"sv
        "eqx::lib::Math::sin<float> = {}\n"sv
        "eqx::lib::CT_Math::sin<float> = {}\n"sv,
        std::sin(1.0F), eqx::lib::Math::sin(1.0F),
        eqx::lib::CT_Math::sin(1.0F));

    std::format_to(std::ostreambuf_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
