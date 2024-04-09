export module Equinox.Math;

import Stdm;
import Equinox.Misc;

export namespace eqx
{
    template <typename T>
        requires requires() { static_cast<T>(0); }
    inline constexpr auto c_Zero = static_cast<T>(0);

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
        return eqx::equals<T>(x, y, static_cast<T>(0.001));
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
        eqx::ensure(val != eqx::c_Zero<T>,
            "Zero Is Not Positive Or Negative!"sv);
        if (stdm::is_constant_evaluated())
        {
            return val < eqx::c_Zero<T> ? false : true;
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
            eqx::ensure(x >= stdm::numeric_limits<stdm::intmax_t>::min() &&
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
    [[nodiscard]] constexpr T degreesToRadians(const T degrees) noexcept
    {
        return degrees * (stdm::numbers::pi_v<T> / static_cast<T>(180.0));
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T radiansToDegrees(const T radians) noexcept
    {
        return radians * (static_cast<T>(180.0) / stdm::numbers::pi_v<T>);
    }
}
