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

#ifndef EQUINOX_DETAILS_RECTANGLEDECL_HPP
#define EQUINOX_DETAILS_RECTANGLEDECL_HPP

#include "Dependencies.hpp"

#include "../Misc.hpp"
#include "../Point.hpp"
#include "../Mathematics.hpp"

namespace eqx
{
    /**
     * @brief Rectangle On The Cartesian Plane Stored As Top Left Coordinates
     *      X, Y And Width And Height, Note That The Rectangle Coordinates
     *      Act As If They Are In Screen Space i.e. The Height Of The
     *      Rectangle Is Directed Downwards
     */
    template <typename T>
        requires Arithmetic<T>
    class Rectangle
    {
    public:
        /**
         * @brief Initialized With Zeros i.e. ((T)0, ...)
         */
        explicit consteval Rectangle() noexcept;

        /**
         * @brief Initalize With Values i.e. (x, y, w, h)
         *
         * @param x The x Value
         * @param y The y Value
         * @param w The Width
         * @param h The Height
         */
        explicit constexpr Rectangle(T x, T y, T w, T h) noexcept;

        /**
         * @brief Initalize With Corner Points
         *
         * @param topLeft The Top Left Point
         * @param bottomRight The Bottom Right Point
         */
        explicit constexpr Rectangle(const eqx::Point<T>& topLeft,
            const eqx::Point<T>& bottomRight) noexcept;

        /**
         * Trivial Move And Copy Operation
         */
        Rectangle(const Rectangle&) = default;
        Rectangle(Rectangle&&) = default;
        Rectangle& operator= (const Rectangle&) = default;
        Rectangle& operator= (Rectangle&&) = default;
        ~Rectangle() = default;

        /**
         * @brief eqx::equals(x, other.x) && eqx::equals(y, other.y) &&
         *      eqx::equals(w, other.w) && eqx::equals(h, other.h)
         *
         * @param other The Same Type Rectangle We Compare Against
         *
         * @returns true If Rectanges Are Equivalent
         */
        [[nodiscard]] constexpr bool operator== (const Rectangle<T>& other)
            const noexcept;

        /**
         * @brief !(*this == other)
         *
         * @param other The Same Type Rectangle We Compare Against
         *
         * @returns true If Rectangles Are Not Equivalent
         */
        [[nodiscard]] constexpr bool operator!= (const Rectangle<T>& other)
            const noexcept;

        /**
         * @brief x = point.x, y = point.y
         *
         * @param point Location To Set Our Rectangle
         */
        constexpr void setLocation(const eqx::Point<T>& point)
            noexcept;

        /**
         * @brief Create A Point At (X, Y), Note That This Is An
         *      Alias For GetTopLeftPoint()
         *
         * @returns eqx::Point<T> Representing The Top Left Point
         */
        [[nodiscard]] constexpr Point<T> getLocation() const noexcept;

        /**
         * @brief Create A Point At (X, Y), The Top Left Point
         *
         * @returns eqx::Point<T> Representing The Top Left Point
         */
        [[nodiscard]] constexpr Point<T> getTopLeftPoint() const noexcept;

        /**
         * @brief Create A Point At (X + W, Y), The Top Right Point
         *
         * @returns eqx::Point<T> Representing The Top Right Point
         */
        [[nodiscard]] constexpr Point<T> getTopRightPoint() const noexcept;

        /**
         * @brief Create A Point At (X, Y + H), The Bottom Left Point
         *
         * @returns eqx::Point<T> Representing The Bottom Left Point
         */
        [[nodiscard]] constexpr Point<T> getBottomLeftPoint() const noexcept;

        /**
         * @brief Create A Point At (X + W, Y + H), The Bottom Right Point
         *
         * @returns eqx::Point<T> Representing The Bottom Right Point
         */
        [[nodiscard]] constexpr Point<T> getBottomRightPoint() const noexcept;

        /**
         * @brief Create A Point At (X + 0.5 * W, Y + 0.5 * H),
         *      The Center point
         *
         * @returns eqx::Point<T> Representing The Center Point
         */
        [[nodiscard]] constexpr Point<T> getCenterPoint() const noexcept;

        /**
         * @brief Create A Point Where other Rectangle Is Perfectly Centered
         *
         * @param other Square To Center
         *
         * @returns eqx::Point<T> Representing Where The other Rectangle
         *      Would Need To Be Located To Center It
         */
        [[nodiscard]] constexpr Point<T>
            getEmplaceCenter(const Rectangle<T>& other) const noexcept;

        /**
         * @brief Creates Printable String Of Form "(x, y, w, h)"
         *
         * @returns "(x, y, w, h)"
         */
        [[nodiscard]] std::string toString() const;

        T x, y, w, h;
    };

    /**
     * @brief Convert An eqx::Rectangle To A std::string Of Form
     *      "(rect.x, rect.y, rect.w, rect.h)"
     *
     * @param rect Rectangle To Be Converted
     *
     * @returns Rectangle Converted To A std::string
     */
    template <typename T>
    [[nodiscard]] std::string toString(const Rectangle<T>& rect);

    /**
     * @brief Compares Two eqx::Rectangles To Each Other Within A
     *      Given Tolerance
     *
     * @param rect1, rect2 Rectangles Compared
     *
     * @returns true If Rectanges Are Equivalent
     */
    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2, double error = 0.001) noexcept;

    /**
     * @brief Compares Two eqx::Rectangles To Each Other
     *
     * @param rect1, rect2 Rectangles Compared
     *
     * @returns true If Rectanges Are Equivalent
     */
    template <typename T>
        requires Integer<T>
    [[nodiscard]] constexpr bool equals(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2) noexcept;

    /**
     * @brief Determine If A Point Is Contained Inside A Rectangle (Inclusive)
     *
     * @param rect The Rectangle
     * @param point The Point
     *
     * @returns true If point Is Contained By rect
     */
    template <typename T>
    [[nodiscard]] constexpr bool intersect(const Rectangle<T>& rect,
        const Point<T>& point) noexcept;

    /**
     * @brief Determine If Two Rectangles Overlap (Inclusive)
     *
     * @param rect1 The First Rectangle
     * @param rect2 The Second Rectangle
     *
     * @returns true If There Is Any Overlap Between rect1 And rect2
     */
    template <typename T>
    [[nodiscard]] constexpr bool intersect(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2) noexcept;

    /**
     * @brief Determine If A Point Is Contained Inside A Rectangle (Exclusive)
     *
     * @param rect The Rectangle
     * @param point The Point
     *
     * @returns true If point Is Contained By rect
     */
    template <typename T>
    [[nodiscard]] constexpr bool intersectExclusive(const Rectangle<T>& rect,
        const Point<T>& point) noexcept;

    /**
     * @brief Determine If Two Rectangles Overlap (Exclusive)
     *
     * @param rect1 The First Rectangle
     * @param rect2 The Second Rectangle
     *
     * @returns true If There Is Any Overlap Between rect1 And rect2
     */
    template <typename T>
    [[nodiscard]] constexpr bool intersectExclusive(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2) noexcept;

    /**
     * @brief Move A Rectangle To Be Centered In Another Rectangle
     *
     * @param source Larger Rectangle To Place Smaller Rectangle In
     * @param toMove Rectangle Centered In The source Rectangle
     */
    template <typename T>
    constexpr void emplaceCenter(const Rectangle<T>& source,
        Rectangle<T>& toMove) noexcept;
}

/**
 * @brief std::hash Overload For Hashed Containers
 */
template <typename T>
struct std::hash<eqx::Rectangle<T>>
{
    [[nodiscard]] std::size_t operator() (const eqx::Rectangle<T>& rect)
        const noexcept
    {
        return std::hash<T>()(rect.x) ^ std::hash<T>()(rect.y) ^
            std::hash<T>()(rect.w) ^ std::hash<T>()(rect.h);
    }
};

/**
 * @brief Shorter Names
 */
namespace eqx::rects
{
    using Rectf = eqx::Rectangle<float>;
    using Rectd = eqx::Rectangle<double>;
    using Recti = eqx::Rectangle<int>;
}

#endif // EQUINOX_DETAILS_RECTANGLEDECL_HPP
