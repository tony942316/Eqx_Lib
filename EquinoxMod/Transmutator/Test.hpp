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

#ifndef EQX_POINT_123
#define EQX_POINT_123

#include <stdh.hpp>


#include "Equinox/Macros.hpp"









namespace eqx
{
    /**
     * @brief Point On The Cartesian Plane i.e. (X, Y), Note T
     *      Must Be An Arithmetic Type
     */
    template <typename T>
        requires std::is_arithmetic_v<T>
    class Point
    {
    public:
        /**
         * @brief Initialize With Values i.e. (x, y)
         *
         * @param x The x Value
         * @param y The y Value
         */
        explicit constexpr Point(const T x, const T y) noexcept;

        /**
         * Trivial Type
         */
        Point() = default;
        Point(const Point&) = default;
        Point(Point&&) = default;
        Point& operator= (const Point&) = default;
        Point& operator= (Point&&) = default;
        ~Point() = default;

        /**
         * @brief x + other.x, y + other.y
         *
         * @param other The Same Type Point We Add From
         *
         * @returns Resulting Point
         */
        [[nodiscard]] constexpr Point<T> operator+ (const Point<T>& other)
            const noexcept;

        /**
         * @brief x - other.x, y - other.y
         *
         * @param other The Same Type Point We Subtract From
         *
         * @returns Resulting Point
         */
        [[nodiscard]] constexpr Point<T> operator- (const Point<T>& other)
            const noexcept;

        /**
         * @brief x * other.x, y * other.y
         *
         * @param scaler The Scaler We Multiply By
         *
         * @returns Resulting Point
         */
        [[nodiscard]] constexpr Point<T> operator* (T scaler)
            const noexcept;

        /**
         * @brief x / other.x, y / other.y
         *
         * @param scaler The Scaler We Divide By
         *
         * @returns Resulting Point
         */
        [[nodiscard]] constexpr Point<T> operator/ (T scaler)
            const noexcept;

        /**
         * @brief x += other.x, y += other.y
         *
         * @param other The Same Type Point We Add From
         *
         * @returns *this
         */
        constexpr Point<T>& operator+= (const Point<T>& other) noexcept;

        /**
         * @brief x -= other.x, y -= other.y
         *
         * @param other The Same Type Point We Subtract From
         *
         * @returns *this
         */
        constexpr Point<T>& operator-= (const Point<T>& other) noexcept;

        /**
         * @brief x * other.x, y * other.y
         *
         * @param scaler The Scaler We Multiply By
         *
         * @returns *this
         */
        constexpr Point<T>& operator*= (T scaler) noexcept;

        /**
         * @brief x / other.x, y / other.y
         *
         * @param scaler The Scaler We Divide By
         *
         * @returns *this
         */
        constexpr Point<T>& operator/= (T scaler) noexcept;

        /**
         * @brief eqx::equals(x, other.x), eqx::equals(y, other.y)
         *
         * @param other The Same Type Point We Compare Against
         *
         * @returns true If Points Are Equivalent
         */
        [[nodiscard]] constexpr bool operator== (const Point<T>& other)
            const noexcept;

        /**
         * @brief !(*this == other)
         *
         * @param other The Same Type Point We Compare Against
         *
         * @returns true If Points Are Not Equivalent
         */
        [[nodiscard]] constexpr bool operator!= (const Point<T>& other)
            const noexcept;

        /**
         * @brief Computes The Distance From This Point To other
         *
         * @param other Point To Where The Distance Is Calculated
         *
         * @returns Distance Between This Point And other
         */
        [[nodiscard]] constexpr T distanceTo(const Point<T>& other)
            const noexcept;

        /**
         * @brief Creates Printable String Of Form "(x, y)"
         *
         * @returns "(x, y)"
         */
        [[nodiscard]] std::string toString() const;

        // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
        T x, y;
        // NOLINTEND(misc-non-private-member-variables-in-classes)
    };

    /**
     * @brief point1 == point2
     *
     * @param point1 First Point
     * @param point2 Second Point
     *
     * @returns true If Points Are Equivalent
     */
    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Point<T>& point1,
        const Point<T>& point2, const T error = eqx::c_FPT<T>) noexcept;

    /**
     * @brief point1 == point2
     *
     * @param point1 First Point
     * @param point2 Second Point
     *
     * @returns true If Points Are Equivalent
     */
    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr bool equals(const Point<T>& point1,
        const Point<T>& point2) noexcept;

    /**
     * @brief Computes The Distance Between Two Points
     *
     * @param point1 First Point
     * @param point2 Second Point
     *
     * @returns Distance Between The Points
     */
    template <typename T>
    [[nodiscard]] constexpr T distance(const Point<T>& point1,
            const Point<T>& point2) noexcept;

    /**
     * @brief Normalize A Point As If It Were A Vector From The Origin (0, 0),
     *      Note T Must Be A std::floating_point
     *
     * @param point Point To Be Normalized
     *
     * @returns Normalized Point
     */
    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr Point<T> normalize(const Point<T>& point) noexcept;

    /**
     * @brief Compute The Angle Of A Point In Degrees, Counter Clockwise
     *      From The Origin (0, 0)
     *
     * @param point Point The Angle Is Computed From
     *
     * @returns Angle In Degrees
     */
    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> angle(
        const Point<T>& point) noexcept;

    /**
     * @brief Convert A Point Into An Array Index
     *
     * @param coord Point To Convert
     * @param rowLength Stride Of A Row In The Array
     *
     * @returns An Index Representing The Point
     */
    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr T coordToIndex(const Point<T>& coord, T rowLength)
        noexcept;

    /**
     * @brief Convert An Array Index Into A 2-D Coordinate
     *
     * @param index Index To Convert
     * @param rowLength Stride Of A Row In The Array
     *
     * @returns A Point Representing The Index
     */
    template <typename T>
        requires std::integral<T>
    [[nodiscard]] constexpr Point<T> indexToCoord(T index, T rowLength)
        noexcept;

    template <typename T>
        requires std::floating_point<T>
    constexpr auto c_Origin = eqx::Point<T>();
}

// Implementations

namespace eqx
{
    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Point<T>::Point(T x, T y) noexcept
        :
        x(x),
        y(y)
    {
    }
    // NOLINTEND(bugprone-easily-swappable-parameters)

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T>
        Point<T>::operator+ (const Point<T>& other) const noexcept
    {
        return Point<T>(x + other.x, y + other.y);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T>
        Point<T>::operator- (const Point<T>& other) const noexcept
    {
        return Point<T>(x - other.x, y - other.y);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Point<T>::operator* (T scaler)
        const noexcept
    {
        return Point<T>(x * scaler, y * scaler);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Point<T>::operator/ (T scaler)
        const noexcept
    {
        eqx::ENSURE_HARD(scaler != 0.0, "Division By Zero");
        return Point<T>(x / scaler, y / scaler);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Point<T>& Point<T>::operator+= (const Point<T>& other) noexcept
    {
        return *this = *this + other;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Point<T>& Point<T>::operator-= (const Point<T>& other) noexcept
    {
        return *this = *this - other;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Point<T>& Point<T>::operator*= (T scaler) noexcept
    {
        return *this = *this * scaler;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Point<T>& Point<T>::operator/= (T scaler) noexcept
    {
        return *this = *this / scaler;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool Point<T>::operator== (const Point<T>& other)
        const noexcept
    {
        return equals(x, other.x) && equals(y, other.y);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool Point<T>::operator!= (const Point<T>& other)
        const noexcept
    {
        return !(*this == other);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr T Point<T>::distanceTo(const Point<T>& other)
        const noexcept
    {
        const auto dx = static_cast<double>(distance(x, other.x));
        const auto dy = static_cast<double>(distance(y, other.y));
        const auto result = eqx::hypot(dx, dy);

        return static_cast<T>(result);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] std::string Point<T>::toString() const
    {
        return "("s + eqx::toString(x) + ", "s + eqx::toString(y) + ")"s;
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Point<T>& point1,
        const Point<T>& point2, const T error) noexcept
    {
        return equals(point1.x, point2.x, error) &&
            equals(point1.y, point2.y, error);
    }

    template <typename T>
        requires std::integral<T>
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
        requires std::floating_point<T>
    [[nodiscard]] constexpr Point<T> normalize(const Point<T>& point) noexcept
    {
        eqx::ENSURE_HARD(point != Point<T>{});
        return point / distance(Point<T>{}, point);
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> angle(
        const Point<T>& point) noexcept
    {
        return eqx::atan2(point.x, point.y);
    }

    template <typename T>
        requires std::integral<T>
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
        requires std::integral<T>
    [[nodiscard]] constexpr Point<T> indexToCoord(T index, T rowLength)
        noexcept
    {
        eqx::ENSURE_HARD(isPositive(rowLength), "rowLength Must Be Positive");
        eqx::ENSURE_HARD(!isNegative(index), "index Can't Be Negative");
        return Point<T>(index % rowLength, index / rowLength);
    }
}

#endif 