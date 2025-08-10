export module Eqx.Lib.Poly;

import <Eqx/std.hpp>;
import Eqx.Lib.Point;

using namespace std::literals;

export namespace eqx::lib
{
    template <typename T, std::size_t S>
    class Poly
    {
    public:
        Poly() = default;
        Poly(const Poly&) = default;
        Poly(Poly&&) = default;
        Poly& operator= (const Poly&) = default;
        Poly& operator= (Poly&&) = default;
        ~Poly() = default;

        explicit constexpr Poly(
            std::initializer_list<eqx::lib::Point<T>>&& ps) noexcept
            :
            m_data()
        {
            std::ranges::copy(ps, std::ranges::begin(m_data));
        }

        template <std::size_t S2>
        [[nodiscard]] constexpr bool aabb(const Poly<T, S2>& p) const noexcept
        {
            auto maxx1 = T{0};
            auto maxy1 = T{0};
            auto minx1 = std::numeric_limits<T>::max();
            auto miny1 = std::numeric_limits<T>::max();

            std::ranges::for_each(this->m_data,
                [&maxx1, &maxy1, &minx1, &miny1]
                (const eqx::lib::Point<T>& p) noexcept -> void
                {
                    maxx1 = std::ranges::max(maxx1, p.get_x());
                    maxy1 = std::ranges::max(maxy1, p.get_y());
                    minx1 = std::ranges::min(minx1, p.get_x());
                    miny1 = std::ranges::min(miny1, p.get_y());
                });

            auto maxx2 = T{0};
            auto maxy2 = T{0};
            auto minx2 = std::numeric_limits<T>::max();
            auto miny2 = std::numeric_limits<T>::max();

            std::ranges::for_each(p.m_data,
                [&maxx2, &maxy2, &minx2, &miny2]
                (const eqx::lib::Point<T>& p) noexcept -> void
                {
                    maxx2 = std::ranges::max(maxx2, p.get_x());
                    maxy2 = std::ranges::max(maxy2, p.get_y());
                    minx2 = std::ranges::min(minx2, p.get_x());
                    miny2 = std::ranges::min(miny2, p.get_y());
                });

            return !(maxx1 < minx2 || maxx2 < minx1 || maxy1 < miny2 || maxy2 < miny1);
        }

        constexpr void trans(const eqx::lib::Point<T>& p) noexcept
        {
            std::ranges::for_each(m_data, [&p]
                (const eqx::lib::Point<T>& val) noexcept -> void
                {
                    val.trans(p);
                });
        }

        [[nodiscard]] constexpr std::size_t size() const noexcept
        {
            return S;
        }

        [[nodiscard]] constexpr std::string to_string() const noexcept
        {
            auto result = ""s;
            result.reserve(S * 15);
            std::ranges::for_each(m_data, [&result]
                (const eqx::lib::Point<T>& p) noexcept -> void
                {
                    result += p.to_string();
                    result += '\n';
                });
            result.pop_back();
            return result;
        }

        std::array<eqx::lib::Point<T>, S> m_data;
    private:
    };
}
