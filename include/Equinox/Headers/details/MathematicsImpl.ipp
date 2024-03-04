/*
 * Copyright (C) 2023 Anthony H. Grasso
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

#ifndef EQUINOX_DETAILS_MATHEMATICSIMPL_IPP
#define EQUINOX_DETAILS_MATHEMATICSIMPL_IPP

#include "MathematicsDecl.hpp"

namespace eqx
{
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr T abs(T val) noexcept
    {
        return val < c_Zero<T> ? val * static_cast<T>(-1) : val;
    }

    template <typename T>
        requires Integer<T>
    [[nodiscard]] constexpr bool equals(T x, T y) noexcept
    {
        return x == y;
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(T x, T y, T error) noexcept
    {
        return abs(x - y) < error;
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] int constexpr getSign(T val) noexcept
    {
        if (val > c_Zero<T>)
        {
            return 1;
        }
        else if (val < c_Zero<T>)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] bool constexpr isPositive(T val) noexcept
    {
        return getSign(val) == 1;
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] bool constexpr isNegative(T val) noexcept
    {
        return getSign(val) == -1;
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] bool constexpr willOverflowAddition(T x, T y) noexcept
    {
        if (x >= c_Zero<T> && y >= c_Zero<T>)
        {
            return (std::numeric_limits<T>::max() - x) < y;
        }
        else if (x <= c_Zero<T> && y <= c_Zero<T>)
        {
            return (std::numeric_limits<T>::lowest() - x) > y;
        }
        else
        {
            return false;
        }
    }

    template <typename T>
        requires SignedArithmetic<T>
    [[nodiscard]] bool constexpr willOverflowSubtraction(T x, T y) noexcept
    {
        if (y == std::numeric_limits<T>::lowest() && SignedInteger<T>)
        {
            return true;
        }
        else
        {
            return willOverflowAddition(x, -y);
        }
    }

    template <typename T>
        requires UnsignedInteger<T>
    [[nodiscard]] bool constexpr willOverflowSubtraction(T x, T y) noexcept
    {
        return y > x;
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr T distance(T x1, T x2) noexcept
    {
        if (x2 > x1)
        {
            std::swap(x1, x2);
        }

        runtimeAssert(!willOverflowSubtraction(x1, x2),
            "Arithmetic Overflow!");

        return abs(x1 - x2);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] double constexpr degreesToRadians(T degrees) noexcept
    {
        return static_cast<double>(degrees) * (std::numbers::pi / 180.0);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] double constexpr radiansToDegrees(T radians) noexcept
    {
        return static_cast<double>(radians) * (180.0 / std::numbers::pi);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] std::pair<double, double> arccos(T value) noexcept
    {
        runtimeAssert(value >= -1.0 && value <= 1.0, "Domain Error!");

        std::pair<double, double> result;
        result.first = radiansToDegrees(std::acos(value));
        result.second = 360.0 - result.first;
        return result;
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] std::pair<double, double> arcsin(T value) noexcept
    {
        runtimeAssert(value >= -1.0 && value <= 1.0, "Domain Error!");

        std::pair<double, double> result;
        result.first = radiansToDegrees(std::asin(value));
        result.second = 180.0 - result.first;
        result.first = result.first >= 0.0 ?
            result.first : 360.0 + result.first;
        return result;
    }
}

#endif // EQUINOX_DETAILS_MATHEMATICSIMPL_IPP
