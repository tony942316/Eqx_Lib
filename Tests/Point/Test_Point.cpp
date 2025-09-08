// Test_Point.cpp

import <Eqx/std.hpp>;
import Eqx.Lib.Point;

using namespace std::literals;

enum class Test
{
    Smoke = 0,
    Getters,
    Unknown
};

[[nodiscard]] inline Test parse(int argc, char* argv[]) noexcept
{
    if (argc != 2) [[unlikely]]
    {
        return Test::Unknown;
    }
    else [[likely]]
    {
        const auto sv = std::string_view{ argv[1] };
        auto value = 0;
        auto [ptr, ec] = std::from_chars(std::ranges::data(sv),
            std::ranges::data(sv) + std::ranges::size(sv), value, 10);
        if (ec != std::errc{}) [[unlikely]]
        {
            std::format_to(std::ostream_iterator<char>(std::cerr),
                "Error: {}\n"sv, std::make_error_code(ec).message());
            return Test::Unknown;
        }
        else if (ptr
            != (std::ranges::data(sv) + std::ranges::size(sv))) [[unlikely]]
        {
            std::format_to(std::ostream_iterator<char>(std::cerr),
                "Arg Not Fully Processed: {}\n"sv, sv);
            return Test::Unknown;
        }
        else [[likely]]
        {
            return Test{ value };
        }
    }
}

[[nodiscard]] inline bool Smoke() noexcept
{
    return true;
}

[[nodiscard]] inline bool Getters() noexcept
{
    auto p1 = eqx::lib::PointF{};
    auto p2 = eqx::lib::PointF{ 1.0F, 1.0F };
    auto p3 = eqx::lib::PointF{ -1.0F, -1.0F };

    auto want = std::to_array<float>({ 1.0F, 1.0F, -1.0F, -1.0F });
    auto got = std::to_array<float>({ p2.get_x(), p2.get_y(), p3.get_x(),
        p3.get_y() });

    return want == got;
}

int main(int argc, char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);

    auto test = parse(argc, argv);
    auto pass = false;
    switch (test)
    {
        case Test::Smoke:
            pass = std::invoke(Smoke);
            break;
        case Test::Getters:
            pass = std::invoke(Getters);
            break;
        case Test::Unknown:
            std::format_to(std::ostream_iterator<char>(std::cerr),
                "Invalid Usage!\n"sv
                "Expected Usage: {} <TEST_ID>\n"sv
                "Example: {} 2\n"sv, argv[1], argv[1]);
            pass = false;
            break;
        default:
            pass = false;
            break;
    }

    std::format_to(std::ostream_iterator<char>(std::cout), "\nEnd\n"sv);
    return pass == true ? EXIT_SUCCESS : EXIT_FAILURE;
}
