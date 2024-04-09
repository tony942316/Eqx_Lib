import Equinox;

using namespace eqx::literals;

constexpr auto inc = 0.00001;
constexpr auto pio2 = stdm::numbers::pi / 2.0;
constexpr auto arrSize = static_cast<stdm::size_t>(pio2 / inc);
constinit auto vals = stdm::array<double, arrSize>{};

[[nodiscard]] double sineGen() noexcept
{
    constinit static auto i = 0.0;

    auto result = stdm::sin(i);
    i += inc;

    return result;
}

[[nodiscard]] double mySine(double rad) noexcept
{
    auto lb = static_cast<stdm::size_t>(rad / inc);
    auto ub = static_cast<stdm::size_t>(rad / inc) + 1_uz;
    auto floor = vals.at(lb);
    auto ceil = vals.at(ub);

    eqx::print("lb: "sv);
    eqx::println(lb);
    eqx::print("floor: "sv);
    eqx::println(floor);
    eqx::print("ub: "sv);
    eqx::println(ub);
    eqx::print("ceil: "sv);
    eqx::println(ceil);
    eqx::print("t: "sv);
    eqx::println(rad);

    return stdm::lerp(floor, ceil, rad);
}

int main()
{
    stdm::ranges::generate(vals, sineGen);

    [[maybe_unused]] auto i = stdm::numeric_limits<int>::max();
    i++;
    stdm::cout << i << stdm::endl;

    /*
    constexpr auto val = 0.03;
    auto myResult = mySine(val);
    auto correct = stdm::sin(val);
    auto error = stdm::abs(correct - myResult);
    eqx::print("std::sin: "sv);
    eqx::println(correct);
    eqx::print("mySine: "sv);
    eqx::println(myResult);
    eqx::print("Error: "sv);
    eqx::println(error);*/
    return 0;
}
