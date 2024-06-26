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

module;

#include "Equinox/Macros.hpp"

export module Equinox.Point;

export import :Decl;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Math.Core;
import Equinox.Math.Modulator;
import Equinox.Math.Trig;

export namespace eqx
{
    template <typename T>
        requires stdm::is_arithmetic_v<T>
    consteval Point<T>::Point() noexcept
        :
        Point(eqx::c_Zero<T>, eqx::c_Zero<T>)
    {
    }

    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    template <typename T>
        requires stdm::is_arithmetic_v<T>
    constexpr Point<T>::Point(T x, T y) noexcept
        :
        x(x),
        y(y)
    {
    }
    // NOLINTEND(bugprone-easily-swappable-parameters)

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T>
        Point<T>::operator+ (const Point<T>& other) const noexcept
    {
        return Point<T>(x + other.x, y + other.y);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T>
        Point<T>::operator- (const Point<T>& other) const noexcept
    {
        return Point<T>(x - other.x, y - other.y);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Point<T>::operator* (T scaler)
        const noexcept
    {
        return Point<T>(x * scaler, y * scaler);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Point<T>::operator/ (T scaler)
        const noexcept
    {
        eqx::ENSURE_HARD(scaler != 0.0, "Division By Zero");
        return Point<T>(x / scaler, y / scaler);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    constexpr Point<T>& Point<T>::operator+= (const Point<T>& other) noexcept
    {
        return *this = *this + other;
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    constexpr Point<T>& Point<T>::operator-= (const Point<T>& other) noexcept
    {
        return *this = *this - other;
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    constexpr Point<T>& Point<T>::operator*= (T scaler) noexcept
    {
        return *this = *this * scaler;
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    constexpr Point<T>& Point<T>::operator/= (T scaler) noexcept
    {
        return *this = *this / scaler;
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool Point<T>::operator== (const Point<T>& other)
        const noexcept
    {
        return equals(x, other.x) && equals(y, other.y);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool Point<T>::operator!= (const Point<T>& other)
        const noexcept
    {
        return !(*this == other);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr T Point<T>::distanceTo(const Point<T>& other)
        const noexcept
    {
        const auto dx = static_cast<double>(distance(x, other.x));
        const auto dy = static_cast<double>(distance(y, other.y));
        const auto result = eqx::hypot(dx, dy);

        return static_cast<T>(result);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] stdm::string Point<T>::toString() const
    {
        return (stdm::stringstream() << "(" << eqx::toString(x) <<
            ", " << eqx::toString(y) << ")").str();
    }

    template <typename T>
    [[nodiscard]] stdm::string toString(const Point<T>& point)
    {
        return point.toString();
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Point<T>& point1,
        const Point<T>& point2, const T error) noexcept
    {
        return equals(point1.x, point2.x, error) &&
            equals(point1.y, point2.y, error);
    }

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr bool equals(const Point<T>& point1,
        const Point<T>& point2) noexcept
    {
        return point1 == point2;
    }

    template <typename T>
    [[nodiscard]] constexpr T distance(const Point<T>& point1,
        const Point<T>& point2) noexcept
    {
        return point1.distanceTo(point2);
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr Point<T> normalize(const Point<T>& point) noexcept
    {
        eqx::ENSURE_HARD(point != Point<T>{});
        return point / distance(Point<T>{}, point);
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> angle(
        const Point<T>& point) noexcept
    {
        return eqx::atan2(point.x, point.y);
    }

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr T coordToIndex(const Point<T>& coord, T rowLength)
        noexcept
    {
        eqx::ENSURE_HARD(isPositive(rowLength), "rowLength Must Be Positive");
        eqx::ENSURE_HARD(!isNegative(coord.x) && !isNegative(coord.y),
            "Point Can't Have Negative Values");
        eqx::ENSURE_HARD(coord.x < rowLength, "x Can't Be Larger Than rowLength");
        return coord.x + coord.y * rowLength;
    }

    template <typename T>
        requires stdm::integral<T>
    [[nodiscard]] constexpr Point<T> indexToCoord(T index, T rowLength)
        noexcept
    {
        eqx::ENSURE_HARD(isPositive(rowLength), "rowLength Must Be Positive");
        eqx::ENSURE_HARD(!isNegative(index), "index Can't Be Negative");
        return Point<T>(index % rowLength, index / rowLength);
    }
}
