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

#ifndef EQUINOX_DETAILS_POINTIMPL_IPP
#define EQUINOX_DETAILS_POINTIMPL_IPP

#include "PointDecl.hpp"

namespace eqx
{
    template <typename T>
        requires Arithmetic<T>
    constexpr Point<T>::Point() noexcept
        :
        Point(zero<T>, zero<T>)
    {
    }

    template <typename T>
        requires Arithmetic<T>
    constexpr Point<T>::Point(T x, T y) noexcept
        :
        x(x),
        y(y)
    {
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T>
        Point<T>::operator+ (const Point<T>& other) const noexcept
    {
        return Point<T>(x + other.x, y + other.y);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T>
        Point<T>::operator- (const Point<T>& other) const noexcept
    {
        return Point<T>(x - other.x, y - other.y);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T> Point<T>::operator* (T scaler)
        const noexcept
    {
        return Point<T>(x * scaler, y * scaler);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T> Point<T>::operator/ (T scaler)
        const noexcept
    {
        runtimeAssert(scaler != 0.0, "Division By Zero");
        return Point<T>(x / scaler, y / scaler);
    }

    template <typename T>
        requires Arithmetic<T>
    constexpr Point<T>& Point<T>::operator+= (const Point<T>& other) noexcept
    {
        return *this = *this + other;
    }

    template <typename T>
        requires Arithmetic<T>
    constexpr Point<T>& Point<T>::operator-= (const Point<T>& other) noexcept
    {
        return *this = *this - other;
    }

    template <typename T>
        requires Arithmetic<T>
    constexpr Point<T>& Point<T>::operator*= (T scaler) noexcept
    {
        return *this = *this * scaler;
    }

    template <typename T>
        requires Arithmetic<T>
    constexpr Point<T>& Point<T>::operator/= (T scaler) noexcept
    {
        return *this = *this / scaler;
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr bool Point<T>::operator== (const Point<T>& other)
        const noexcept
    {
        return equals(x, other.x) && equals(y, other.y);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr bool Point<T>::operator!= (const Point<T>& other)
        const noexcept
    {
        return !(*this == other);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] T Point<T>::distanceTo(const Point<T>& other) const noexcept
    {
        runtimeAssert(errno == 0, "Previous errno Failure Detected!");

        const auto dx = static_cast<double>(distance(x, other.x));
        const auto dy = static_cast<double>(distance(y, other.y));
        const auto result = std::hypot(dx, dy);

        runtimeAssert(errno != ERANGE, "errno == ERANGE!");

        return static_cast<T>(result);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] std::string Point<T>::toString() const
    {
        return (std::stringstream() << "(" << eqx::toString(x) <<
            ", " << eqx::toString(y) << ")").str();
    }

    template <typename T>
    [[nodiscard]] std::string toString(const Point<T>& point)
    {
        return point.toString();
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Point<T>& point1,
        const Point<T>& point2, double error) noexcept
    {
        return equals(point1.x, point2.x, error) &&
            equals(point1.y, point2.y, error);
    }

    template <typename T>
        requires Integer<T>
    [[nodiscard]] constexpr bool equals(const Point<T>& point1,
        const Point<T>& point2) noexcept
    {
        return point1 == point2;
    }

    template <typename T>
    [[nodiscard]] T distance(const Point<T>& point1,
        const Point<T>& point2) noexcept
    {
        return point1.distanceTo(point2);
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] Point<T> normalize(const Point<T>& point) noexcept
    {
        if (point == Point<T>())
        {
            return Point<T>();
        }
        else
        {
            return point / distance(Point<T>(), point);
        }
    }

    template <typename T>
    [[nodiscard]] double angle(const Point<T>& point) noexcept
    {
        const auto normPoint = normalize(point);
        const auto sinVals = arcsin(normPoint.y);
        const auto cosVals = arccos(normPoint.x);

        auto correctValue = equals(sinVals.first, cosVals.first) ||
            equals(sinVals.second, cosVals.second) ?
            sinVals.first : sinVals.second;

        return correctValue;
    }

    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr T coordToIndex(const Point<T>& coord, T rowLength)
        noexcept
    {
        runtimeAssert(isPositive(rowLength), "rowLength Must Be Positive");
        runtimeAssert(!isNegative(coord.x) && !isNegative(coord.y),
            "Point Can't Have Negative Values");
        runtimeAssert(coord.x < rowLength, "x Can't Be Larger Than rowLength");
        return coord.x + coord.y * rowLength;
    }

    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr Point<T> indexToCoord(T index, T rowLength)
        noexcept
    {
        runtimeAssert(isPositive(rowLength), "rowLength Must Be Positive");
        runtimeAssert(!isNegative(index), "index Can't Be Negative");
        return Point<T>(index % rowLength, index / rowLength);
    }
}

#endif // EQUINOX_DETAILS_POINTIMPL_IPP
