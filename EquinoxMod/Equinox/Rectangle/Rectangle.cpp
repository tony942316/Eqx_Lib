module;

#include "Equinox/Macros.hpp"

export module Equinox.Rectangle;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Math.Core;
import Equinox.Point;

export namespace eqx
{
    /**
     * @brief Rectangle On The Cartesian Plane Stored As Top Left Coordinates
     *      X, Y And Width And Height, Note That The Rectangle Coordinates
     *      Act As If They Are In Screen Space i.e. The Height Of The
     *      Rectangle Is Directed Downwards
     */
    template <typename T>
        requires stdm::is_arithmetic_v<T>
    class Rectangle
    {
    public:
        /**
         * @brief Initalize With Values i.e. (x, y, w, h)
         *
         * @param x The x Value
         * @param y The y Value
         * @param w The Width
         * @param h The Height
         */
        explicit constexpr Rectangle(const T x, const T y, const T w,
            const T h) noexcept;

        /**
         * @brief Initalize With Corner Points
         *
         * @param topLeft The Top Left Point
         * @param bottomRight The Bottom Right Point
         */
        explicit constexpr Rectangle(const eqx::Point<T>& topLeft,
            const eqx::Point<T>& bottomRight) noexcept;

        /**
         * Trivial Type
         */
        Rectangle() = default;
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
        [[nodiscard]] stdm::string toString() const;

        T x, y, w, h;
    };

    /**
     * @brief Compares Two eqx::Rectangles To Each Other Within A
     *      Given Tolerance
     *
     * @param rect1, rect2 Rectangles Compared
     *
     * @returns true If Rectanges Are Equivalent
     */
    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Rectangle<T>& rect1,
        const Rectangle<T>& rect2, const T error = eqx::c_FPT<T>) noexcept;

    /**
     * @brief Compares Two eqx::Rectangles To Each Other
     *
     * @param rect1, rect2 Rectangles Compared
     *
     * @returns true If Rectanges Are Equivalent
     */
    template <typename T>
        requires stdm::integral<T>
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

// Implementations

export namespace eqx
{
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
