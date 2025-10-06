// Point.cpp

export module Eqx.Lib.Point;

import <Eqx/std.hpp>;
import Eqx.Lib.Math;
import Eqx.Lib.CMath;

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

        constexpr void negate() noexcept
        {
            this->set_xy(-this->get_x(), -this->get_y());
        }

        constexpr void translate(const Point<T>& point) noexcept
        {
            this->set_xy(this->get_x() + point.get_x(),
                this->get_y() + point.get_y());
        }

        constexpr void rotate(const T radian) noexcept
        {
            this->rotate(eqx::lib::CMath::sin(radian),
                eqx::lib::CMath::cos(radian));
        }

        constexpr void rotate(const T radian,
            const Point<T>& pivot) noexcept
        {
            this->rotate(eqx::lib::CMath::sin(radian),
                eqx::lib::CMath::cos(radian), pivot);
        }

        constexpr void rotate(const T sin_val, const T cos_val) noexcept
        {
            this->set_xy(cos_val * this->get_x() - sin_val * this->get_y(),
                sin_val * this->get_x() + cos_val * this->get_y());
        }

        constexpr void rotate(const T sin_val, const T cos_val,
            const Point<T>& pivot) noexcept
        {
            this->translate(negate(pivot));
            this->rotate(sin_val, cos_val);
            this->translate(pivot);
        }

        constexpr void scale(const T scaler) noexcept
        {
            this->set_xy(this->get_x() * scaler, this->get_y() * scaler);
        }

        [[nodiscard]] constexpr T magnitude() const noexcept
        {
            return eqx::lib::CMath::hypot(this->get_x(), this->get_y());
        }

        [[nodiscard]] constexpr T magnitude2() const noexcept
        {
            return eqx::lib::Math::hypot2(this->get_x(), this->get_y());
        }

        constexpr void normalize() noexcept
        {
            this->scale(T{ 1 } / this->magnitude());
            assert(eqx::lib::Math::near(this->magnitude2(), T{ 1 }));
        }

        [[nodiscard]] constexpr T distance(const Point<T>& p) const noexcept
        {
            return eqx::lib::CMath::hypot(p.get_x() - this->get_x(),
                p.get_y() - this->get_y());
        }

        [[nodiscard]] constexpr T distance2(const Point<T>& p) const noexcept
        {
            return eqx::lib::Math::hypot2(p.get_x() - this->get_x(),
                p.get_y() - this->get_y());
        }

        constexpr void lerp(const Point<T>& p, const T t) noexcept
        {
            this->set_xy(std::lerp(this->get_x(), p.get_x(), t),
                std::lerp(this->get_y(), p.get_y(), t));
        }

        constexpr void midpoint(const Point<T>& p) noexcept
        {
            this->set_xy(std::midpoint(this->get_x(), p.get_x()),
                std::midpoint(this->get_y(), p.get_y()));
        }

        [[nodiscard]] constexpr T dot(const Point<T>& p) const noexcept
        {
            return this->get_x() * p.get_x() + this->get_y() * p.get_y();
        }

        [[nodiscard]] constexpr T cross(const Point<T>& p) const noexcept
        {
            return this->get_x() * p.get_y() - this->get_y() * p.get_x();
        }

        [[nodiscard]] constexpr T component(const Point<T>& p) const noexcept
        {
            return this->dot(p) / p.magnitude();
        }

        constexpr void projection(const Point<T>& p) noexcept
        {
            *this = projection(*this, p);
        }

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

        [[nodiscard]] static constexpr Point<T> negate(
            const Point<T>& p) noexcept
        {
            return Point<T>{ -p.get_x(), -p.get_y() };
        }

        [[nodiscard]] static constexpr Point<T> translate(
            const Point<T>& p1, const Point<T>& p2) noexcept
        {
            return Point<T>{ p1.get_x() + p2.get_x(), p1.get_y() + p2.get_y() };
        }

        [[nodiscard]] static constexpr Point<T> rotate(
            const Point<T>& p, const T radian) noexcept
        {
            return rotate(p, eqx::lib::CMath::sin(radian),
                eqx::lib::CMath::cos(radian));
        }

        [[nodiscard]] static constexpr Point<T> rotate(
            const Point<T>& p, const T radian, const Point<T>& pivot) noexcept
        {
            return rotate(p, eqx::lib::CMath::sin(radian),
                eqx::lib::CMath::cos(radian), pivot);
        }

        [[nodiscard]] static constexpr Point<T> rotate(
            const Point<T>& p, const T sin_val, const T cos_val) noexcept
        {
            return Point<T>{ cos_val * p.get_x() - sin_val * p.get_y(),
                sin_val * p.get_x() + cos_val * p.get_y() };
        }

        [[nodiscard]] static constexpr Point<T> rotate(
            const Point<T>& p1, const T sin_val, const T cos_val,
            const Point<T>& pivot) noexcept
        {
            return translate(rotate(
                    translate(p1, negate(pivot)), sin_val, cos_val), pivot);
        }

        [[nodiscard]] static constexpr Point<T> scale(const Point<T>& p1,
            const T scaler) noexcept
        {
            return Point<T>{ p1.get_x() * scaler, p1.get_y() * scaler };
        }

        [[nodiscard]] static constexpr T magnitude(const Point<T>& p1) noexcept
        {
            return p1.magnitude();
        }

        [[nodiscard]] static constexpr T magnitude2(const Point<T>& p1) noexcept
        {
            return p1.magnitude2();
        }

        [[nodiscard]] static constexpr Point<T> normalize(
            const Point<T>& p1) noexcept
        {
            return scale(p1, T{ 1 } / magnitude(p1));
        }

        [[nodiscard]] static constexpr T distance(const Point<T>& p1,
            const Point<T>& p2) noexcept
        {
            return p1.distance(p2);
        }

        [[nodiscard]] static constexpr T distance2(const Point<T>& p1,
            const Point<T>& p2) noexcept
        {
            return p1.distance2(p2);
        }

        [[nodiscard]] static constexpr Point<T> lerp(const Point<T>& p1,
            const Point<T> p2, const T t) noexcept
        {
            return Point<T>{ std::lerp(p1.get_x(), p2.get_x(), t),
                std::lerp(p1.get_y(), p2.get_y(), t) };
        }

        [[nodiscard]] static constexpr Point<T> midpoint(const Point<T>& p1,
            const Point<T> p2) noexcept
        {
            return Point<T>{ std::midpoint(p1.get_x(), p2.get_x()),
                std::midpoint(p1.get_y(), p2.get_y()) };
        }

        [[nodiscard]] static constexpr T dot(const Point<T>& p1,
            const Point<T>& p2) noexcept
        {
            return p1.dot(p2);
        }

        [[nodiscard]] static constexpr T cross(const Point<T>& p1,
            const Point<T>& p2) noexcept
        {
            return p1.cross(p2);
        }

        [[nodiscard]] static constexpr T component(const Point<T>& p1,
            const Point<T>& p2) noexcept
        {
            return p1.component(p2);
        }

        [[nodiscard]] static constexpr Point<T> projection(const Point<T>& p1,
            const Point<T>& p2) noexcept
        {
            return scale(p2, dot(p1, p2) / magnitude2(p2));
        }

        [[nodiscard]] static consteval Point<T> origin() noexcept
        {
            return Point<T>{ T{ 0 }, T{ 0 } };
        }

    private:
        T m_x;
        T m_y;
    };
}
