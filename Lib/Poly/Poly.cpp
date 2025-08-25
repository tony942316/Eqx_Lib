export module Eqx.Lib.Poly;

import <Eqx/std.hpp>;
import Eqx.Lib.Point;

using namespace std::literals;

export namespace eqx::lib
{
    template <std::size_t S>
    class PolyF
    {
    public:
        PolyF() = default;
        PolyF(const PolyF&) = default;
        PolyF(PolyF&&) = default;
        PolyF& operator= (const PolyF&) = default;
        PolyF& operator= (PolyF&&) = default;
        ~PolyF() = default;

        explicit constexpr PolyF(
            std::initializer_list<eqx::lib::PointF>&& ps) noexcept
            :
            m_data()
        {
            assert(ps.size() == S);
            std::ranges::copy(ps, std::ranges::begin(m_data));
        }

        [[nodiscard]] constexpr
            std::pair<eqx::lib::PointF, eqx::lib::PointF>
            bounding_box() const noexcept
        {
            const auto [minx, maxx] = std::ranges::minmax(this->get_data(), {},
                &eqx::lib::PointF::get_x);
            const auto [miny, maxy] = std::ranges::minmax(this->get_data(), {},
                &eqx::lib::PointF::get_y);

            return std::pair<eqx::lib::PointF, eqx::lib::PointF>{
                eqx::lib::PointF{ minx.get_x(), miny.get_y() },
                eqx::lib::PointF{ maxx.get_x(), maxy.get_y() }};
        }

        [[nodiscard]] constexpr eqx::lib::PointF center() const noexcept
        {
            const auto [min, max] = this->bounding_box();
            return eqx::lib::PointF{
                std::midpoint(min.get_x(), max.get_x()),
                std::midpoint(min.get_y(), max.get_y()) };
        }

        template <std::size_t S2>
        [[nodiscard]] constexpr bool aabb(const PolyF<S2>& p) const noexcept
        {
            const auto [min1, max1] = this->bounding_box();
            const auto [min2, max2] = p.bounding_box();

            return !(max1.get_x() < min2.get_x()
                || max2.get_x() < min1.get_x()
                || max1.get_y() < min2.get_y()
                || max2.get_y() < min1.get_y());
        }

        constexpr void move(const eqx::lib::PointF& p) noexcept
        {
            this->trans(p - this->center());
        }

        constexpr void trans(const eqx::lib::PointF& p) noexcept
        {
            std::ranges::for_each(this->get_data(), [p]
                (eqx::lib::PointF& val) constexpr noexcept -> void
                {
                    val.trans(p);
                });
        }

        constexpr void rot(const float deg) noexcept
        {
            std::ranges::for_each(this->get_data(),
                [deg, pivot = this->center()]
                (eqx::lib::PointF& val) constexpr noexcept -> void
                {
                    val.rot(deg, pivot);
                });
        }

        [[nodiscard]] consteval std::size_t size() const noexcept
        {
            return S;
        }

        [[nodiscard]] inline std::string to_string() const noexcept
        {
            auto result = ""s;
            result.reserve(S * 15);
            std::ranges::for_each(this->get_data(), [&result]
                (const eqx::lib::PointF& p) noexcept -> void
                {
                    result += p.to_string();
                    result += '\n';
                });
            result.pop_back();
            return result;
        }

        [[nodiscard]] constexpr std::span<const eqx::lib::PointF, S>
            get_data() const noexcept
        {
            return this->m_data;
        }

    private:
        std::array<eqx::lib::PointF, S> m_data;
    };
}
