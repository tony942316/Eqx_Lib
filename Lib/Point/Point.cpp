export module Eqx.Lib.Point;

import <Eqx/std.hpp>;
import Eqx.Lib.Math;

using namespace std::literals;

export namespace eqx::lib
{
    class PointF
    {
    public:
        PointF() = default;
        PointF(const PointF&) = default;
        PointF(PointF&&) = default;
        PointF& operator= (const PointF&) = default;
        PointF& operator= (PointF&&) = default;
        ~PointF() = default;

        explicit constexpr PointF(const float x, const float y) noexcept
            :
            m_x(x),
            m_y(y)
        {
        }

        [[nodiscard]] constexpr PointF operator+ () const noexcept
        {
            return *this;
        }

        [[nodiscard]] constexpr PointF operator- () const noexcept
        {
            return PointF{ -this->get_x(), -this->get_y() };
        }

        [[nodiscard]] constexpr PointF
            operator+ (const PointF& p) const noexcept
        {
            return PointF{ this->get_x() + p.get_x(),
                this->get_y() + p.get_y() };
        }

        [[nodiscard]] constexpr PointF
            operator- (const PointF& p) const noexcept
        {
            return *this + -p;
        }

        [[nodiscard]] constexpr PointF operator* (const float x) const noexcept
        {
            return PointF{ this->get_x() * x, this->get_y() * x };
        }

        [[nodiscard]] constexpr PointF operator/ (const float x) const noexcept
        {
            return *this * (1.0F / x);
        }

        constexpr void neg() noexcept
        {
            this->set_xy(-this->get_x(), -this->get_y());
        }

        constexpr void trans(const PointF& p) noexcept
        {
            this->set_xy(this->get_x() + p.get_x(), this->get_y() + p.get_y());
        }

        constexpr void rot(const float rad,
            const PointF& pivot = PointF::origin()) noexcept
        {
            this->rot(eqx::lib::Math::sin(rad), eqx::lib::Math::cos(rad),
                pivot);
        }

        constexpr void rot(const float s, const float c,
            const PointF& pivot = PointF::origin()) noexcept
        {
            this->trans(-pivot);
            this->set_xy(c * this->get_x() - s * this->get_y(),
                s * this->get_x() + c * this->get_y());
            this->trans(pivot);
        }

        constexpr void scale(const float x) noexcept
        {
            this->set_xy(this->get_x() * x, this->get_y() * x);
        }

        constexpr void norm() noexcept
        {
            this->scale(1.0F / this->dist());
        }

        [[nodiscard]] constexpr float dist(const PointF& p) const noexcept
        {
            return eqx::lib::Math::hypot(
                p.get_x() - this->get_x(),
                p.get_y() - this->get_y());
        }

        [[nodiscard]] constexpr float dist() const noexcept
        {
            return eqx::lib::Math::hypot(this->get_x(), this->get_y());
        }

        [[nodiscard]] constexpr float dist2(const PointF& p) const noexcept
        {
            return eqx::lib::Math::hypot2(
                p.get_x() - this->get_x(),
                p.get_y() - this->get_y());
        }

        [[nodiscard]] constexpr float dist2() const noexcept
        {
            return eqx::lib::Math::hypot2(this->get_x(), this->get_y());
        }

        [[nodiscard]] constexpr float get_x() const noexcept
        {
            return this->m_x;
        }

        [[nodiscard]] constexpr float get_y() const noexcept
        {
            return this->m_y;
        }

        constexpr void set_x(const float x) noexcept
        {
            this->m_x = x;
        }

        constexpr void set_y(const float y) noexcept
        {
            this->m_y = y;
        }

        constexpr void set_xy(const float x, const float y) noexcept
        {
            this->set_x(x);
            this->set_y(y);
        }

        [[nodiscard]] inline std::string to_string() const noexcept
        {

            return std::format("({:.4f}, {:.4f})"sv, this->get_x(),
                this->get_y());
        }

        [[nodiscard]] static consteval PointF origin() noexcept
        {
            return PointF{ 0.0F, 0.0F };
        }

    private:
        float m_x, m_y;
    };
}
