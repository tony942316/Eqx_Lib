module;

#include <Equinox/Macros.hpp>

export module Equinox.Math;

export import :Decl;

import Eqx.Stdm;
import Equinox.Misc;

export namespace eqx
{
    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T abs(const T val) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            return val < eqx::c_Zero<T> ? -val : val;
        }
        else
        {
            return stdm::abs(val);
        }
    }

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr double factorial(const T val) noexcept
    {
        eqx::ENSURE_HARD(val <= static_cast<T>(170), "Factorial To Large!!!"sv);
        auto iota = stdm::views::iota(1, val + 1);
        return stdm::reduce(stdm::ranges::begin(iota), stdm::ranges::end(iota),
            stdm::multiplies<T>{});
    }

    template <typename T>
        requires requires(const T& x, const T& y)
            { stdm::ranges::equal_to{}(x, y); }
    [[nodiscard]] constexpr bool equals(const T& x, const T& y) noexcept
    {
        return stdm::ranges::equal_to{}(x, y);
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y) noexcept
    {
        return eqx::equals<T>(x, y, eqx::c_FPT);
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y,
        const T error) noexcept
    {
        return eqx::abs(x - y) < error;
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isPositive(const T val) noexcept
    {
        eqx::ENSURE_HARD(val != eqx::c_Zero<T>,
            "Zero Is Not Positive Or Negative!"sv);
        if (stdm::is_constant_evaluated())
        {
            return val < eqx::c_Zero<T>;
        }
        else
        {
            return !stdm::signbit(val);
        }
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isNegative(const T val) noexcept
    {
        return !eqx::isPositive(val);
    }

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr bool isEven(const T val) noexcept
    {
        return val % 2 == 0;
    }

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr bool isOdd(const T val) noexcept
    {
        return !isEven(val);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept
    {
        return eqx::abs(x - y);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T trunc(const T x) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            eqx::ENSURE_HARD(x >= stdm::numeric_limits<stdm::intmax_t>::min() &&
                x <= stdm::numeric_limits<stdm::intmax_t>::max(),
                "Constexpr Domain Violation!"sv);
            return static_cast<T>(static_cast<stdm::intmax_t>(x));
        }
        else
        {
            return stdm::trunc(x);
        }
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T floor(const T x) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            auto result = eqx::trunc(x);
            if (eqx::isPositive(x) || eqx::equals(result, x))
            {
                return result;
            }
            else
            {
                return result -= static_cast<T>(1);
            }
            return result;
        }
        else
        {
            return stdm::floor(x);
        }
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T ceil(const T x) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            auto result = eqx::trunc(x);
            if (eqx::isNegative(x) || eqx::equals(result, x))
            {
                return result;
            }
            else
            {
                return result += static_cast<T>(1);
            }
            return result;
        }
        else
        {
            return stdm::ceil(x);
        }
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr double
        median(const stdm::span<const T> range) noexcept
    {
        eqx::ENSURE_HARD(stdm::ranges::is_sorted(range),
            "Range Is Not Sorted!!!"sv);
        auto len = stdm::ranges::size(range);
        if (eqx::isOdd(len))
        {
            return range.at((len + 1) / 2);
        }
        else
        {
            return (range.at(len / 2) + range.at((len / 2) + 1)) / 2;
        }
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr double
        average(const stdm::span<const T> range) noexcept
    {
        return stdm::reduce(stdm::ranges::begin(range),
            stdm::ranges::end(range), stdm::plus<T>{})
            / static_cast<double>(stdm::ranges::size(range));
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T degreesToRadians(const T degrees) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return degrees * (stdm::numbers::pi_v<T> / static_cast<T>(180.0));
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T radiansToDegrees(const T radians) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return radians * (static_cast<T>(180.0) / stdm::numbers::pi_v<T>);
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }
}
