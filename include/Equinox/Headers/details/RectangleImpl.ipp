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

#ifndef EQUINOX_DETAILS_RECTANGLEIMPL_IPP
#define EQUINOX_DETAILS_RECTANGLEIMPL_IPP

#include "RectangleDecl.hpp"

namespace eqx
{
    template <typename T>
        requires Arithmetic<T>
    constexpr Rectangle<T>::Rectangle() noexcept
        :
        Rectangle(zero<T>, zero<T>, zero<T>, zero<T>)
    {
    }

    template <typename T>
        requires Arithmetic<T>
    constexpr Rectangle<T>::Rectangle(T x, T y, T w, T h) noexcept
        :
        x(x),
        y(y),
        w(w),
        h(h)
    {
    }

    template <typename T>
        requires Arithmetic<T>
    constexpr Rectangle<T>::Rectangle(const eqx::Point<T>& topLeft,
        const eqx::Point<T>& bottomRight) noexcept
        :
        Rectangle(topLeft.x, topLeft.y,
            distance(topLeft.x, bottomRight.x),
            distance(topLeft.y, bottomRight.y))
    {
        eqx::runtimeAssert(topLeft.x < bottomRight.x &&
            topLeft.y > bottomRight.y , "Invalid Bottom Right Point!");
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr bool
        Rectangle<T>::operator== (const Rectangle<T>& other) const noexcept
    {
        return equals(x, other.x) &&
            equals(y, other.y) &&
            equals(w, other.w) &&
            equals(h, other.h);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr bool
        Rectangle<T>::operator!= (const Rectangle<T>& other) const noexcept
    {
        return !(*this == other);
    }

    template <typename T>
        requires Arithmetic<T>
    constexpr void Rectangle<T>::setLocation(const eqx::Point<T>& point)
        noexcept
    {
        x = point.x;
        y = point.y;
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getLocation() const noexcept
    {
        return getTopLeftPoint();
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getTopLeftPoint()
        const noexcept
    {
        return Point<T>(x, y);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getTopRightPoint()
        const noexcept
    {
        return Point<T>(x + w, y);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getBottomLeftPoint()
        const noexcept
    {
        return Point<T>(x, y + h);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getBottomRightPoint()
        const noexcept
    {
        return Point<T>(x + w, y + h);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getCenterPoint()
        const noexcept
    {
        auto dx = static_cast<T>(w * 0.5);
        auto dy = static_cast<T>(h * 0.5);
        return Point<T>(x + dx, y + dy);
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] constexpr Point<T>
        Rectangle<T>::getEmplaceCenter(const Rectangle<T>& other)
            const noexcept
    {
        runtimeAssert(other.w < w && other.h < h,
            "Other Rectangle Is Wider Or Taller Than Source!");

        return eqx::Point<T>(static_cast<T>(x + 0.5 * (w - other.w)),
            static_cast<T>(y + 0.5 * (h - other.h)));
    }

    template <typename T>
        requires Arithmetic<T>
    [[nodiscard]] std::string Rectangle<T>::toString() const
    {
        return (std::stringstream() << "(" << eqx::toString(x) <<
            ", " << eqx::toString(y) << ", " << eqx::toString(w) <<
            ", " << eqx::toString(h) << ")").str();
    }

    template <typename T>
    [[nodiscard]] std::string toString(const Rectangle<T>& rect)
    {
        return rect.toString();
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2, double error) noexcept
    {
        return equals(rect1.x, rect2.x, error) &&
            equals(rect1.y, rect2.y, error) &&
            equals(rect1.w, rect2.w, error) &&
            equals(rect1.h, rect2.h, error);
    }

    template <typename T>
        requires Integer<T>
    [[nodiscard]] constexpr bool equals(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2) noexcept
    {
        return rect1 == rect2;
    }

    template <typename T>
    [[nodiscard]] constexpr bool intersect(const Rectangle<T>& rect,
        const Point<T>& point) noexcept
    {
        if (point.x < rect.getTopLeftPoint().x ||
                point.x > rect.getTopRightPoint().x ||
                point.y > rect.getBottomLeftPoint().y ||
                point.y < rect.getTopLeftPoint().y)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    template <typename T>
    [[nodiscard]] constexpr bool intersect(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2) noexcept
    {
        if (rect1.getBottomRightPoint().x < rect2.getBottomLeftPoint().x ||
            rect1.getBottomLeftPoint().x > rect2.getBottomRightPoint().x ||
            rect1.getBottomLeftPoint().y < rect2.getTopLeftPoint().y ||
            rect1.getTopLeftPoint().y > rect2.getBottomLeftPoint().y)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    template <typename T>
    [[nodiscard]] constexpr bool intersectExclusive(const Rectangle<T>& rect,
        const Point<T>& point) noexcept
    {
        if (point.x <= rect.getTopLeftPoint().x ||
            point.x >= rect.getTopRightPoint().x ||
            point.y >= rect.getBottomLeftPoint().y ||
            point.y <= rect.getTopLeftPoint().y)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    template <typename T>
    [[nodiscard]] constexpr bool intersectExclusive(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2) noexcept
    {
        if (rect1.getBottomRightPoint().x <= rect2.getBottomLeftPoint().x ||
            rect1.getBottomLeftPoint().x >= rect2.getBottomRightPoint().x ||
            rect1.getBottomLeftPoint().y <= rect2.getTopLeftPoint().y ||
            rect1.getTopLeftPoint().y >= rect2.getBottomLeftPoint().y)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    template <typename T>
    constexpr void emplaceCenter(const Rectangle<T>& source,
        Rectangle<T>& toMove) noexcept
    {
        toMove.setLocation(source.getEmplaceCenter(toMove));
    }
}

#endif // EQUINOX_DETAILS_RECTANGLEIMPL_IPP
