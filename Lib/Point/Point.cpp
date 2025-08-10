export module Eqx.Lib.Point;

import <Eqx/std.hpp>;
import Eqx.Lib.Math;

using namespace std::literals;

export namespace eqx::lib
{
    template <typename T>
    class Point
    {
    public:
        Point() = default;
        Point(const Point&) = default;
        Point(Point&&) = default;
        Point& operator= (const Point&) = default;
        Point& operator= (Point&&) = default;
        ~Point() = default;

        explicit constexpr Point(const T x, const T y) noexcept
            :
            m_x(x),
            m_y(y)
        {
        }

        constexpr void trans(const Point<T>& p) noexcept
        {
            this->set_xy(this->get_x() + p.get_x(), this->get_y() + p.get_y());
        }

        [[nodiscard]] constexpr T dist(const Point<T>& p) const noexcept
        {
            return eqx::lib::Math::hypot<T>(
                p.get_x() - this->get_x(),
                p.get_y() - this->get_y());
        }

        [[nodiscard]] constexpr T dist2(const Point<T>& p) const noexcept
        {
            return eqx::lib::Math::hypot2<T>(
                p.get_x() - this->get_x(),
                p.get_y() - this->get_y());
        }

        [[nodiscard]] constexpr T get_x() const noexcept
        {
            return m_x;
        }

        [[nodiscard]] constexpr T get_y() const noexcept
        {
            return m_y;
        }

        constexpr void set_x(const T x) noexcept
        {
            m_x = x;
        }

        constexpr void set_y(const T y) noexcept
        {
            m_y = y;
        }

        constexpr void set_xy(const T x, const T y) noexcept
        {
            this->set_x(x);
            this->set_y(y);
        }

        [[nodiscard]] constexpr std::string to_string() const noexcept
        {
            return std::format("({}, {})"sv, this->get_x(), this->get_y());
        }

    private:
        T m_x;
        T m_y;
    };
}
