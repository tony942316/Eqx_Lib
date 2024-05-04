import Equinox;

using namespace eqx::literals;

[[nodiscard]] constexpr double myFMod(const double val, const double mod) noexcept
{
    return val - eqx::trunc(val / mod) * mod;
}

[[nodiscard]] constexpr double myPow(const double val, const double pow) noexcept
{
    auto result = 1.0;
    for (int i = 0; i < pow; i++)
    {
        result *= val;
    }
    return result;
}

[[nodiscard]] constexpr double mySine(const double rad) noexcept
{
    constexpr auto terms = 7;
    constexpr auto taylordeg = (terms * 4) + 1;
    auto mod = eqx::abs(myFMod(rad, 2 * stdm::numbers::pi));
    auto result = 0.0;

    for (auto i = 1; i < taylordeg; i += 4)
    {
        result -= myPow(mod - stdm::numbers::pi, i) / fac(i);
        result += myPow(mod - stdm::numbers::pi, i + 2) / fac(i + 2);
    }

    return rad < 0.0 ? -result : result;
}

int main()
{
    constexpr auto val = (8.0 * stdm::numbers::pi);
    constexpr auto inc = 0.001;
    stdm::cout << stdm::setprecision(20);
    auto stats = stdm::vector<double>{};
    stats.reserve(static_cast<stdm::size_t>(stdm::ceil((2 * val) / inc)));
    for (auto i = -val; i < val; i += inc)
    {
        auto error = stdm::abs(mySine(i) - stdm::sin(i));
        stats.emplace_back(error);
    }
    stdm::cout << "(" << stats.front() << ") <=> (" << stats.back() << ")" << stdm::endl;
    stdm::cout << "(" << mySine(stdm::numbers::pi) << ")" << "(" << stdm::sin(stdm::numbers::pi) << ")" << stdm::endl;
    stdm::cout << "(" << mySine(val - 0.01) << ")" << "(" << stdm::sin(val - 0.01) << ")" << stdm::endl;
    stdm::cout << "Median Error: " << median(stats) << stdm::endl;
    stdm::cout << "Avg Error: " << avg(stats) << stdm::endl;
    stdm::cout << "Max Error: " << stdm::ranges::max(stats) << stdm::endl;
    stdm::cout << "Min Error: " << stdm::ranges::min(stats) << stdm::endl;
    stdm::cout << "End" << stdm::endl;
    return 0;
}
