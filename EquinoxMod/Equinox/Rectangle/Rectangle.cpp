module;

#include "Equinox/Macros.hpp"

export module Equinox.Rectangle;

export import :Decl;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Math.Core;
import Equinox.Point;

export namespace eqx
{
    template <typename T>
        requires stdm::is_arithmetic_v<T>
    consteval Rectangle<T>::Rectangle() noexcept
        :
        Rectangle(c_Zero<T>, c_Zero<T>, c_Zero<T>, c_Zero<T>)
    {
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    constexpr Rectangle<T>::Rectangle(const T x, const T y, const T w,
        const T h) noexcept
        :
        x(x),
        y(y),
        w(w),
        h(h)
    {
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    constexpr Rectangle<T>::Rectangle(const eqx::Point<T>& topLeft,
        const eqx::Point<T>& bottomRight) noexcept
        :
        Rectangle(topLeft.x, topLeft.y,
            distance(topLeft.x, bottomRight.x),
            distance(topLeft.y, bottomRight.y))
    {
        using namespace eqx::literals;
        eqx::ENSURE_HARD(topLeft.x < bottomRight.x
            && topLeft.y > bottomRight.y , "Invalid Bottom Right Point!"sv);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool
        Rectangle<T>::operator== (const Rectangle<T>& other) const noexcept
    {
        return equals(x, other.x)
            && equals(y, other.y)
            && equals(w, other.w)
            && equals(h, other.h);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr bool
        Rectangle<T>::operator!= (const Rectangle<T>& other) const noexcept
    {
        return !(*this == other);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    constexpr void Rectangle<T>::setLocation(const eqx::Point<T>& point)
        noexcept
    {
        x = point.x;
        y = point.y;
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getLocation() const noexcept
    {
        return getTopLeftPoint();
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getTopLeftPoint()
        const noexcept
    {
        return Point<T>(x, y);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getTopRightPoint()
        const noexcept
    {
        return Point<T>(x + w, y);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getBottomLeftPoint()
        const noexcept
    {
        return Point<T>(x, y - h);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getBottomRightPoint()
        const noexcept
    {
        return Point<T>(x + w, y - h);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T> Rectangle<T>::getCenterPoint()
        const noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto dx = static_cast<T>(w * 0.5);
        auto dy = static_cast<T>(h * 0.5);
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        return Point<T>(x + dx, y - dy);
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] constexpr Point<T>
        Rectangle<T>::getEmplaceCenter(const Rectangle<T>& other)
            const noexcept
    {
        eqx::ENSURE_HARD(other.w < w && other.h < h,
            "Other Rectangle Is Wider Or Taller Than Source!");

        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return eqx::Point<T>(static_cast<T>(x + 0.5 * (w - other.w)),
            static_cast<T>(y - 0.5 * (h - other.h)));
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires stdm::is_arithmetic_v<T>
    [[nodiscard]] stdm::string Rectangle<T>::toString() const
    {
        return (stdm::stringstream() << "(" << eqx::toString(x) <<
            ", " << eqx::toString(y) << ", " << eqx::toString(w) <<
            ", " << eqx::toString(h) << ")").str();
    }

    template <typename T>
    [[nodiscard]] stdm::string toString(const Rectangle<T>& rect)
    {
        return rect.toString();
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2, const T error) noexcept
    {
        return equals(rect1.x, rect2.x, error) &&
            equals(rect1.y, rect2.y, error) &&
            equals(rect1.w, rect2.w, error) &&
            equals(rect1.h, rect2.h, error);
    }

    template <typename T>
        requires stdm::integral<T>
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
            point.y < rect.getBottomLeftPoint().y ||
            point.y > rect.getTopLeftPoint().y)
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
            rect1.getBottomLeftPoint().y > rect2.getTopLeftPoint().y ||
            rect1.getTopLeftPoint().y < rect2.getBottomLeftPoint().y)
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
            point.y <= rect.getBottomLeftPoint().y ||
            point.y >= rect.getTopLeftPoint().y)
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
            rect1.getBottomLeftPoint().y >= rect2.getTopLeftPoint().y ||
            rect1.getTopLeftPoint().y <= rect2.getBottomLeftPoint().y)
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
