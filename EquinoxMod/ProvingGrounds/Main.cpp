import Equinox;
import Eqx.Tests;

using namespace eqx::literals;

//constexpr auto val = (8.0 * stdm::numbers::pi);
//constexpr auto inc = 0.01;
//constexpr auto cnt = static_cast<stdm::size_t>(eqx::ceil((2 * val / inc)) + 1);

/*constexpr auto values = stdm::invoke([]() consteval
    {
        auto result = stdm::array<double, cnt>{};
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
    stdm::cout << "Start\n\n";

    test::clientserver::all().print("Client & Server"sv);
    test::math::all().print("Math"sv);
    test::misc::all().print("Misc"sv);
    test::point::all().print("Point"sv);
    test::random::all().print("Random"sv);
    test::rectangle::all().print("Rectangle"sv);
    test::stopwatch::all().print("StopWatch"sv);

    /*
    auto stats = stdm::vector<double>{};
    stats.reserve(cnt);
    stdm::cout << cnt << stdm::endl;
    //auto i = 0ULL;
    for (auto v = -val; v < val; v += inc)
    {
        //auto error = stdm::abs(values.at(i) - stdm::sin(v));
        //stats.emplace_back(error);
        //i++;
    }
    stdm::ranges::sort(stats);
    stdm::cout << "Median Error: " << eqx::median(stats) << stdm::endl;
    stdm::cout << "Avg Error: " << eqx::average(stats) << stdm::endl;
    stdm::cout << "Max Error: " << stdm::ranges::max(stats) << stdm::endl;
    stdm::cout << "Min Error: " << stdm::ranges::min(stats) << stdm::endl;
    stdm::cout << "End" << stdm::endl;
    */
    stdm::cout << "\nEnd: ";
    stdm::cin.get();
    return stdm::Exit_Success;
}
