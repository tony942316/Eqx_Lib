import <Eqx/std.hpp>;

import <Eqx/Lib/Macros.hpp>;
import Eqx.Lib;
import Eqx.Tests;

//constexpr auto val = (8.0 * std::numbers::pi);
//constexpr auto inc = 0.01;
//constexpr auto cnt = static_cast<std::size_t>(eqx::ceil((2 * val / inc)) + 1);

/*constexpr auto values = std::invoke([]() consteval
    {
        auto result = std::array<double, cnt>{};
        auto i = 0ULL;
        for (auto v = -val; v < val; v += inc)
        {
            result.at(i) = eqx::sin(v);
            i++;
        }
        return result;
    });*/

int main()
{
    std::cout << "Start\n\n"sv;

    test::clientserver::all().print("Client & Server"sv);
    test::math::all().print("Math"sv);
    test::misc::all().print("Misc"sv);
    test::point::all().print("Point"sv);
    test::random::all().print("Random"sv);
    test::rectangle::all().print("Rectangle"sv);
    test::stopwatch::all().print("StopWatch"sv);

    /*
    auto stats = std::vector<double>{};
    stats.reserve(cnt);
    std::cout << cnt << std::endl;
    //auto i = 0ULL;
    for (auto v = -val; v < val; v += inc)
    {
        //auto error = std::abs(values.at(i) - std::sin(v));
        //stats.emplace_back(error);
        //i++;
    }
    std::ranges::sort(stats);
    std::cout << "Median Error: " << eqx::median(stats) << std::endl;
    std::cout << "Avg Error: " << eqx::average(stats) << std::endl;
    std::cout << "Max Error: " << std::ranges::max(stats) << std::endl;
    std::cout << "Min Error: " << std::ranges::min(stats) << std::endl;
    std::cout << "End" << std::endl;
    */
    std::cout << "\nEnd: "sv;
    std::cin.get();
    return 0;
}
