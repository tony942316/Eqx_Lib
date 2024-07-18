module;

#include <Equinox/Macros.hpp>

#ifdef _MSC_VER

#endif // _MSC_VER

export module Equinox.Math.Core;

import Eqx.Stdm;
import Equinox.Misc;

export namespace eqx
{
    template <typename T>
        requires requires() { static_cast<T>(0); }
    constexpr auto c_Zero = static_cast<T>(0);

    template <typename T>
        requires stdm::floating_point<T>
    constexpr auto c_FPT = static_cast<T>(0.00001);

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T abs(const T val) noexcept;

    template <typename T>
        requires requires(const T& x, const T& y)
            { x == y; }
            && (!stdm::floating_point<T>)
    [[nodiscard]] constexpr bool equals(const T& x, const T& y) noexcept;

    template <typename T>
    [[nodiscard]] constexpr bool equals(const stdm::pair<T, T>& x,
        const stdm::pair<T, T>& y) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y,
        const T error) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isPositive(const T val) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isNegative(const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
            || stdm::signed_integral<T>
    [[nodiscard]] constexpr T sign(const T val) noexcept;

    template <typename T>
        requires stdm::unsigned_integral<T>
    [[nodiscard]] constexpr T sign([[maybe_unused]] const T val) noexcept;

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr bool isEven(const T val) noexcept;

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr bool isOdd(const T val) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
            && (!stdm::unsigned_integral<T>)
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept;

    template <typename T>
        requires stdm::unsigned_integral<T>
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T trunc(const T x) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T floor(const T x) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T ceil(const T x) noexcept;

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr double factorial(const T val) noexcept;

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T pow(const T val, const T deg) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T fmod(const T val, const T mod) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T sqrt(const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T hypot(const T x, const T y) noexcept;

    template <typename T, typename F>
        requires stdm::floating_point<T>
            && stdm::invocable<F, T>
    [[nodiscard]] constexpr T newtonsMethod(const T guess,
        const stdm::size_t iters, const F& func) noexcept;
}

// Implementions

export namespace eqx
{
    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T abs(const T val) noexcept
    {
        if constexpr (stdm::unsigned_integral<T>)
        {
            return val;
        }
        else if (stdm::is_constant_evaluated())
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
            { x == y; }
            && (!stdm::floating_point<T>)
    [[nodiscard]] constexpr bool equals(const T& x, const T& y) noexcept
    {
        return x == y;
    }

    template <typename T>
    [[nodiscard]] constexpr bool equals(const stdm::pair<T, T>& x,
        const stdm::pair<T, T>& y) noexcept
    {
        return equals<T>(x.first, y.first) && equals<T>(x.second, y.second);
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y) noexcept
    {
        return eqx::equals<T>(x, y, eqx::c_FPT<T>);
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
        if (stdm::is_constant_evaluated())
        {
            return val >= eqx::c_Zero<T>;
        }
        else
        {
#ifdef _MSC_VER
            return !stdm::signbit(static_cast<double>(val));
#else
            return !stdm::signbit(val);
#endif // _MSC_VER
        }
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isNegative(const T val) noexcept
    {
        return !eqx::isPositive(val);
    }

    template <typename T>
        requires stdm::floating_point<T>
            || stdm::signed_integral<T>
    [[nodiscard]] constexpr T sign(const T val) noexcept
    {
        return isPositive(val) ? static_cast<T>(1) : static_cast<T>(-1);
    }

    template <typename T>
        requires stdm::unsigned_integral<T>
    [[nodiscard]] constexpr T sign([[maybe_unused]] const T val) noexcept
    {
        return static_cast<T>(1);
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
            && (!stdm::unsigned_integral<T>)
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept
    {
        return eqx::abs(y - x);
    }

    template <typename T>
        requires stdm::unsigned_integral<T>
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept
    {
        eqx::ENSURE_HARD(y >= x, "y Must Be Greater Than x!"sv);
        return eqx::abs(y - x);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T trunc(const T x) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            if constexpr (stdm::unsigned_integral<T>)
            {
                eqx::ENSURE_HARD(
                    x >= stdm::numeric_limits<stdm::uintmax_t>::lowest()
                        && x <= stdm::numeric_limits<stdm::uintmax_t>::max(),
                    "Constexpr Domain Violation!"sv);
                return static_cast<T>(static_cast<stdm::uintmax_t>(x));
            }
            else
            {

                eqx::ENSURE_HARD(
                    x >= stdm::numeric_limits<stdm::intmax_t>::lowest()
                        && x <= stdm::numeric_limits<stdm::intmax_t>::max(),
                    "Constexpr Domain Violation!"sv);
                return static_cast<T>(static_cast<stdm::intmax_t>(x));
            }
        }
        else
        {
            return static_cast<T>(stdm::trunc(x));
        }
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T floor(const T x) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            auto result = eqx::trunc(x);
            if (eqx::isPositive(x) || eqx::equals<T>(result, x))
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
            return static_cast<T>(stdm::floor(x));
        }
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T ceil(const T x) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            auto result = eqx::trunc(x);
            if (eqx::isNegative(x) || eqx::equals<T>(result, x))
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
            return static_cast<T>(stdm::ceil(x));
        }
    }

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr double factorial(const T val) noexcept
    {
        eqx::ENSURE_HARD(val <= static_cast<T>(170), "Factorial To Large!!!"sv);
        eqx::ENSURE_HARD(val >= eqx::c_Zero<T>, "Factorial Of Negative!!!"sv);
        auto iota = stdm::views::iota(1, static_cast<int>(val) + 1) |
            stdm::views::transform(eqx::staticCast<double, int>);
        return stdm::reduce(stdm::ranges::begin(iota), stdm::ranges::end(iota),
            1.0, stdm::multiplies<void>{});
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T pow(const T val, const T deg) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            auto result = 1.0;
            for (int i = 0; static_cast<T>(i) < deg; i++)
            {
                result *= static_cast<double>(val);
            }
            eqx::ENSURE_HARD(
                result <= static_cast<double>(stdm::numeric_limits<T>::max()),
                "Conversion Overflow!!!"sv);
            return static_cast<T>(result);
        }
        else
        {

            if constexpr (stdm::floating_point<T>)
            {
                return stdm::pow(val, deg);
            }
            else
            {
                auto result = stdm::pow(static_cast<double>(val),
                    static_cast<double>(deg));
                eqx::ENSURE_HARD(result
                    <= static_cast<double>(stdm::numeric_limits<T>::max()),
                    "Conversion Overflow!!!"sv);
                return static_cast<T>(result);
            }
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T fmod(const T val, const T mod) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            eqx::ENSURE_HARD(mod > eqx::c_Zero<T>,
                "Negative Mod!!!"sv)
            return val - eqx::trunc(val / mod) * mod;
        }
        else
        {
            return stdm::fmod(val, mod);
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T sqrt(const T val) noexcept
    {
        using namespace eqx::literals;
        if (stdm::is_constant_evaluated())
        {
            eqx::ENSURE_HARD(val >= eqx::c_Zero<T>,
                "Negative Square Root!!!"sv);
            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return newtonsMethod(
                (val + static_cast<T>(1.0)) / static_cast<T>(2.0),
                30_uz,
                [val](const T x)
                    { return static_cast<T>(0.5) * (x + (val / x)); });
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            return stdm::sqrt(val);
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T hypot(const T x, const T y) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            return eqx::sqrt(x * x + y * y);
        }
        else
        {
            return stdm::hypot(x, y);
        }
    }

    template <typename T, typename F>
        requires stdm::floating_point<T>
            && stdm::invocable<F, T>
    [[nodiscard]] constexpr T newtonsMethod(const T guess,
        const stdm::size_t iters, const F& func) noexcept
    {
        using namespace eqx::literals;
        auto x = guess;
        for (auto i = 0_uz; i < iters; i++)
        {
            x = func(x);
        }
        return x;
    }
}
