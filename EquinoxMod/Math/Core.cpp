/*
 * Copyright (C) 2024 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

export module Eqx.Lib.Math.Core;

import <Eqx/std.hpp>;

import <Eqx/Lib/Macros.hpp>;
import Eqx.Lib.Misc;

export namespace eqx
{
    template <typename T>
        requires requires() { static_cast<T>(0); }
    constexpr auto c_Zero = static_cast<T>(0);

    template <typename T>
        requires std::floating_point<T>
    constexpr auto c_FPT = static_cast<T>(0.00001);

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T abs(const T val) noexcept;

    template <typename T>
        requires requires(const T& x, const T& y)
            { x == y; }
            && (!std::floating_point<T>)
    [[nodiscard]] constexpr bool equals(const T& x, const T& y) noexcept;

    template <typename T>
    [[nodiscard]] constexpr bool equals(const std::pair<T, T>& x,
        const std::pair<T, T>& y) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y,
        const T error) noexcept;

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isPositive(const T val) noexcept;

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isNegative(const T val) noexcept;

    template <typename T>
        requires std::floating_point<T>
            || std::signed_integral<T>
    [[nodiscard]] constexpr T sign(const T val) noexcept;

    template <typename T>
        requires std::unsigned_integral<T>
    [[nodiscard]] constexpr T sign([[maybe_unused]] const T val) noexcept;

    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr bool isEven(const T val) noexcept;

    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr bool isOdd(const T val) noexcept;

    template <typename T>
        requires std::is_arithmetic_v<T>
            && (!std::unsigned_integral<T>)
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept;

    template <typename T>
        requires std::unsigned_integral<T>
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept;

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T trunc(const T x) noexcept;

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T floor(const T x) noexcept;

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T ceil(const T x) noexcept;

    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr double factorial(const T val) noexcept;

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T pow(const T val, const T deg) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T fmod(const T val, const T mod) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T sqrt(const T val) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T hypot(const T x, const T y) noexcept;

    template <typename T, typename F>
        requires std::floating_point<T>
            && std::invocable<F, T>
    [[nodiscard]] constexpr T newtonsMethod(const T guess,
        const std::size_t iters, const F& func) noexcept;
}

// Implementions

export namespace eqx
{
    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T abs(const T val) noexcept
    {
        if constexpr (std::unsigned_integral<T>)
        {
            return val;
        }
        else if (std::is_constant_evaluated())
        {
            return val < eqx::c_Zero<T> ? -val : val;
        }
        else
        {
            return std::abs(val);
        }
    }

    template <typename T>
        requires requires(const T& x, const T& y)
            { x == y; }
            && (!std::floating_point<T>)
    [[nodiscard]] constexpr bool equals(const T& x, const T& y) noexcept
    {
        return x == y;
    }

    template <typename T>
    [[nodiscard]] constexpr bool equals(const std::pair<T, T>& x,
        const std::pair<T, T>& y) noexcept
    {
        return equals<T>(x.first, y.first) && equals<T>(x.second, y.second);
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y) noexcept
    {
        return eqx::equals<T>(x, y, eqx::c_FPT<T>);
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const T x, const T y,
        const T error) noexcept
    {
        return eqx::abs(x - y) < error;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isPositive(const T val) noexcept
    {
        if (std::is_constant_evaluated())
        {
            return val >= eqx::c_Zero<T>;
        }
        else
        {
#ifdef _MSC_VER
            return !std::signbit(static_cast<double>(val));
#else
            return !std::signbit(val);
#endif // _MSC_VER
        }
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool isNegative(const T val) noexcept
    {
        return !eqx::isPositive(val);
    }

    template <typename T>
        requires std::floating_point<T>
            || std::signed_integral<T>
    [[nodiscard]] constexpr T sign(const T val) noexcept
    {
        return isPositive(val) ? static_cast<T>(1) : static_cast<T>(-1);
    }

    template <typename T>
        requires std::unsigned_integral<T>
    [[nodiscard]] constexpr T sign([[maybe_unused]] const T val) noexcept
    {
        return static_cast<T>(1);
    }

    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr bool isEven(const T val) noexcept
    {
        return val % 2 == 0;
    }

    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr bool isOdd(const T val) noexcept
    {
        return !isEven(val);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
            && (!std::unsigned_integral<T>)
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept
    {
        return eqx::abs(y - x);
    }

    template <typename T>
        requires std::unsigned_integral<T>
    [[nodiscard]] constexpr T distance(const T x, const T y) noexcept
    {
        eqx::ENSURE_HARD(y >= x, "y Must Be Greater Than x!"sv);
        return eqx::abs(y - x);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T trunc(const T x) noexcept
    {
        if (std::is_constant_evaluated())
        {
            if constexpr (std::unsigned_integral<T>)
            {
                eqx::ENSURE_HARD(
                    x >= std::numeric_limits<std::uintmax_t>::lowest()
                        && x <= std::numeric_limits<std::uintmax_t>::max(),
                    "Constexpr Domain Violation!"sv);
                return static_cast<T>(static_cast<std::uintmax_t>(x));
            }
            else
            {

                eqx::ENSURE_HARD(
                    x >= std::numeric_limits<std::intmax_t>::lowest()
                        && x <= std::numeric_limits<std::intmax_t>::max(),
                    "Constexpr Domain Violation!"sv);
                return static_cast<T>(static_cast<std::intmax_t>(x));
            }
        }
        else
        {
            return static_cast<T>(std::trunc(x));
        }
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T floor(const T x) noexcept
    {
        if (std::is_constant_evaluated())
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
            return static_cast<T>(std::floor(x));
        }
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T ceil(const T x) noexcept
    {
        if (std::is_constant_evaluated())
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
            return static_cast<T>(std::ceil(x));
        }
    }

    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr double factorial(const T val) noexcept
    {
        eqx::ENSURE_HARD(val <= static_cast<T>(170), "Factorial To Large!!!"sv);
        eqx::ENSURE_HARD(val >= eqx::c_Zero<T>, "Factorial Of Negative!!!"sv);
        auto iota = std::views::iota(1, static_cast<int>(val) + 1) |
            std::views::transform(eqx::staticCast<double, int>);
        return std::reduce(std::ranges::begin(iota), std::ranges::end(iota),
            1.0, std::multiplies<void>{});
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T pow(const T val, const T deg) noexcept
    {
        if (std::is_constant_evaluated())
        {
            auto result = 1.0;
            for (int i = 0; static_cast<T>(i) < deg; i++)
            {
                result *= static_cast<double>(val);
            }
            eqx::ENSURE_HARD(
                result <= static_cast<double>(std::numeric_limits<T>::max()),
                "Conversion Overflow!!!"sv);
            return static_cast<T>(result);
        }
        else
        {

            if constexpr (std::floating_point<T>)
            {
                return std::pow(val, deg);
            }
            else
            {
                auto result = std::pow(static_cast<double>(val),
                    static_cast<double>(deg));
                eqx::ENSURE_HARD(result
                    <= static_cast<double>(std::numeric_limits<T>::max()),
                    "Conversion Overflow!!!"sv);
                return static_cast<T>(result);
            }
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T fmod(const T val, const T mod) noexcept
    {
        if (std::is_constant_evaluated())
        {
            eqx::ENSURE_HARD(mod > eqx::c_Zero<T>,
                "Negative Mod!!!"sv)
            return val - eqx::trunc(val / mod) * mod;
        }
        else
        {
            return std::fmod(val, mod);
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T sqrt(const T val) noexcept
    {
        using namespace eqx::literals;
        if (std::is_constant_evaluated())
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
            return std::sqrt(val);
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T hypot(const T x, const T y) noexcept
    {
        if (std::is_constant_evaluated())
        {
            return eqx::sqrt(x * x + y * y);
        }
        else
        {
            return std::hypot(x, y);
        }
    }

    template <typename T, typename F>
        requires std::floating_point<T>
            && std::invocable<F, T>
    [[nodiscard]] constexpr T newtonsMethod(const T guess,
        const std::size_t iters, const F& func) noexcept
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
