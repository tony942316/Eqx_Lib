// Point.cpp

export module Eqx.Lib.Point;

import <Eqx/std.hpp>;
import Eqx.Lib.Math;

using namespace std::literals;

export namespace eqx::lib
{
    template <typename T>
        requires std::floating_point<T>
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

        constexpr void inplace_negate() noexcept
        {
            this->set_xy(-this->get_x(), -this->get_y());
        }

        [[nodiscard]] constexpr Point<T> generate_negate() const noexcept
        {
            return Point<T>{ -this->get_x(), -this->get_y() };
        }

        constexpr void inplace_translate(const Point<T>& point) noexcept
        {
            this->set_xy(this->get_x() + point.get_x(),
                this->get_y() + point.get_y());
        }

        [[nodiscard]] constexpr Point<T> generate_translate(
            const Point<T>& point) const noexcept
        {
            return Point<T>{ this->get_x() + point.get_x(),
                this->get_y() + point.get_y() };
        }

        constexpr void inplace_rotate(const T radian) noexcept
        {
            this->rot(eqx::lib::Math::sin(radian),
                eqx::lib::Math::cos(radian));
        }

        constexpr void inplace_rotate(const T radian,
            const Point<T>& pivot) noexcept
        {
            this->rot(eqx::lib::Math::sin(radian), eqx::lib::Math::cos(radian),
                pivot);
        }

        constexpr void inplace_rotate(const T sin_val, const T cos_val) noexcept
        {
            this->set_xy(cos_val * this->get_x() - sin_val * this->get_y(),
                sin_val * this->get_x() + cos_val * this->get_y());
        }

        constexpr void inplace_rotate(const T sin_val, const T cos_val,
            const Point<T>& pivot) noexcept
        {
            this->trans(pivot.generate_negate());
            this->set_xy(cos_val * this->get_x() - sin_val * this->get_y(),
                sin_val * this->get_x() + cos_val * this->get_y());
            this->trans(pivot);
        }

        constexpr void inplace_scale(const T scaler) noexcept
        {
            this->set_xy(this->get_x() * scaler, this->get_y() * scaler);
        }

        [[nodiscard]] constexpr Point<T> generate_scale(
            const T scaler) const noexcept
        {
            return Point<T>{ this->get_x() * scaler, this->get_y() * scaler };
        }

        [[nodiscard]] constexpr 

        constexpr void set_x(const T x) noexcept
        {
            this->m_x = x;
        }

        constexpr void set_y(const T y) noexcept
        {
            this->m_y = y;
        }

        constexpr void set_xy(const T x, const T y) noexcept
        {
            this->set_x(x);
            this->set_y(y);
        }

        [[nodiscard]] constexpr T get_x() const noexcept
        {
            return this->m_x;
        }

        [[nodiscard]] constexpr T get_y() const noexcept
        {
            return this->m_y;
        }

        [[nodiscard]] inline std::string to_string() const noexcept
        {
            return std::format("({:.4f}, {:.4f})"sv, this->get_x(),
                this->get_y());
        }

        [[nodiscard]] static consteval Point<T> origin() noexcept
        {
            return Point<T>{ T{ 0 }, T{ 0 } };
        }

    private:
        T m_x;
        T m_y;
    }

    class PointF
    {
    public:

        [[nodiscard]] constexpr float operator* (const PointF& p) const noexcept
        {
            return this->get_x() * p.get_x() + this->get_y() * p.get_y();
        }

        [[nodiscard]] constexpr float operator^ (const PointF& p) const noexcept
        {
            return this->get_x() * p.get_y() - this->get_y() * p.get_x();
        }

        [[nodiscard]] constexpr PointF
            operator>> (const PointF& p) const noexcept
        {
            return (*this * p) / p.mag2()
        }

        constexpr void norm() noexcept
        {
            this->scale(1.0F / this->dist());
        }

        constexpr void proj(const PointF& p) noexcept
        {
            *this = p * (this->dot(p) / p.mag2());
        }

        [[nodiscard]] constexpr float sproj(const PointF& p) noexcept
        {
            return this->dot(p) / p.mag2();
        }

        [[nodiscard]] constexpr float dot(const PointF& p) const noexcept
        {
            return *this * p;
        }

        [[nodiscard]] constexpr float cross(const PointF& p) const noexcept
        {
            return *this ^ p;
        }

        [[nodiscard]] constexpr float dist(const PointF& p) const noexcept
        {
            return eqx::lib::Math::hypot(
                p.get_x() - this->get_x(),
                p.get_y() - this->get_y());
        }

        [[nodiscard]] constexpr float mag() const noexcept
        {
            return eqx::lib::Math::hypot(this->get_x(), this->get_y());
        }

        [[nodiscard]] constexpr float dist2(const PointF& p) const noexcept
        {
            return eqx::lib::Math::hypot2(
                p.get_x() - this->get_x(),
                p.get_y() - this->get_y());
        }

        [[nodiscard]] constexpr float mag2() const noexcept
        {
            return eqx::lib::Math::hypot2(this->get_x(), this->get_y());
        }

    private:
        float m_x, m_y;
    };
}
