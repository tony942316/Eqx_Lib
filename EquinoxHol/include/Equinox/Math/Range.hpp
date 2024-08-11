



#ifndef EQX_Math_Range_123
#define EQX_Math_Range_123


#include <stdh.hpp>
#include <Equinox/Misc/Misc.hpp>
#include <Equinox/Math/Core.hpp>

namespace eqx
{
    template <typename T>
    concept ArithmeticRange = std::ranges::range<T>
        && std::is_arithmetic_v<std::ranges::range_value_t<T>>;

    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double median(const T& range) noexcept;

    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double average(const T& range) noexcept;
}

// Implementations

namespace eqx
{
    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double median(const T& range) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        eqx::ENSURE_HARD(std::ranges::is_sorted(range),
            "Range Is Not Sorted!!!"sv);
        const auto len = std::ranges::size(range);
        if (eqx::isOdd(len))
        {
            return static_cast<double>(range.at((len - 1) / 2));
        }
        else
        {
            return static_cast<double>(
                range.at(len / 2) + range.at((len / 2) - 1)) / 2.0;
        }
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double average(const T& range) noexcept
    {
        using E = std::ranges::range_value_t<T>;
        return static_cast<double>(std::reduce(std::ranges::begin(range),
            std::ranges::end(range), eqx::c_Zero<E>, std::plus<void>{}))
            / static_cast<double>(std::ranges::size(range));
    }
}

#endif // EQX_Math_Range_123