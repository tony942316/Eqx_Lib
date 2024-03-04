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

#ifndef EQUINOX_DETAILS_MATHEMATICSDECL_HPP
#define EQUINOX_DETAILS_MATHEMATICSDECL_HPP


#include "Dependencies.hpp"

#include "../Misc.hpp"

namespace eqx
{
    /**
     * @brief Type Accurate Zero
     */
    template <typename T>
        requires std::is_arithmetic_v<T>
    inline constexpr auto c_Zero = static_cast<T>(0);

    /**
     * @brief Take The Absolute Value Of A Number
     *      Equivilent To std::abs Except For This Is Constexpr (Pre-C++23)
     *
     * @param val Number To Take The Absolute Value Of
     *
     * @returns Absolute Value Of val
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr T abs(T val) noexcept;

    /**
     * @brief Check If Two Integer Types Are Equal
     * @brief T Must Be An Integer Type
     *
     * @param x, y Values To Be Checked
     *
     * @returns true If The Values Are Equal
     */
    template <typename T>
        requires Integer<T>
    [[nodiscard]] constexpr bool equals(T x, T y) noexcept;

    /**
     * @brief Check If Two Floating Point Types Are Equal Given Some Amount 
     *      Of Error
     * @brief T Must Be A Floating Point Type
     *
     * @param x, y Values To Be Checked
     * @param error Amount Of Inaccuracy Permissible
     *
     * @returns true If The Difference Is Less Than error
     */
    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool
        equals(T x, T y, T error = static_cast<T>(0.001f)) noexcept;

    /**
     * @brief Checks The Sign Of A Given Value
     * @brief T Must Be An Arithmetic Type
     *
     * @param val To Be Checked
     *
     * @returns 1, 0, And -1 For Positive, Zero, And Negative
     *      Values Respectively
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] int constexpr getSign(T val) noexcept;

    /**
     * @brief Check If A Value Is Positive, Note That 0 Is Not Positive
     * @brief T Must Be An Arithmetic Type
     *
     * @param val Value To Be Checked
     *
     * @returns true If The Value Is Positive
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] bool constexpr isPositive(T val) noexcept;

    /**
     * @brief Check If A Value Is Negative, Note That 0 Is Not Negative
     * @brief T Must Be An Arithmetic Type
     *
     * @param val Value To Be Checked
     *
     * @returns true If The Value Is Negative
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] bool constexpr isNegative(T val) noexcept;

    /**
     * @brief Check If Two Values Will Overflow By Addition
     * @brief T Must Be An Arithmetic Type
     *
     * @param x, y Values To Be Checked
     *
     * @returns true If Overflow Would Occur
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] bool constexpr willOverflowAddition(T x, T y) noexcept;

    /**
     * @brief Check If Two Values Will Overflow By Subtraction
     * @brief T Must Be An Arithmetic Type
     *
     * @param x, y Values To Be Checked
     *
     * @returns true If Overflow Would Occur
     */
    template <typename T>
        requires SignedArithmetic<T>
    [[nodiscard]] bool constexpr willOverflowSubtraction(T x, T y) noexcept;

    /**
     * @brief Check If Two Values Will Overflow By Subtraction
     * @brief T Must Be An Arithmetic Type
     *
     * @param x, y Values To Be Checked
     *
     * @returns true If Overflow Would Occur
     */
    template <typename T>
        requires UnsignedInteger<T>
    [[nodiscard]] bool constexpr willOverflowSubtraction(T x, T y) noexcept;

    /**
     * @brief Compute The Distance Between Two One Dimensional Points
     * @brief T Must Be An Arithmetic Type
     *
     * @param x1, x2 Values On A One Dimensional Plane
     *
     * @returns Distance Between Two One Dimensional Points
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr T distance(T x1, T x2) noexcept;

    /**
     * @brief Convert Degrees To Radians
     * @brief T Must Be An Arithmetic Type
     *
     * @param degrees Degrees To Be Converted
     *
     * @returns double Equal To The Radian Equivalent Of degrees
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] double constexpr degreesToRadians(T degrees) noexcept;

    /**
     * @brief Convert Radians To Degrees
     * @brief T Must Be An Arithmetic Type
     *
     * @param radians Radians To Be Converted
     *
     * @returns double Equal To The Degree Equivalent Of radians
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] double constexpr radiansToDegrees(T radians) noexcept;

    /**
     * @brief Compute Both Arccosine Values
     * @brief T Must Be An Arithmetic Type
     * @brief value Must Be In Interval [-1.0, 1.0]
     *
     * @param value Value To Be Computed
     *
     * @returns std::pair<double, double>, Values Are In Degrees
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] std::pair<double, double> arccos(T value) noexcept;

    /**
     * @brief Compute Both Arcsine Values
     * @brief T Must Be An Arithmetic Type
     * @brief value Must Be In Interval [-1.0, 1.0]
     *
     * @param value Value To Be Computed
     *
     * @returns std::pair<double, double>, Values Are In Degrees
     */
    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] std::pair<double, double> arcsin(T value) noexcept;
}

#endif // EQUINOX_DETAILS_MATHEMATICSDECL_HPP
