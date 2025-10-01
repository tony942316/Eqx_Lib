export module Eqx.Lib.Polygon;

import <Eqx/std.hpp>;
import Eqx.Lib.Point;

using namespace std::literals;

export namespace eqx::lib
{
    template <typename T, std::size_t S>
    class Polygon
    {
    public:
        Polygon() = default;
        Polygon(const Polygon&) = default;
        Polygon(Polygon&&) = default;
        Polygon& operator= (const Polygon&) = default;
        Polygon& operator= (Polygon&&) = default;
        ~Polygon() = default;

        explicit constexpr Polygon(
            std::initializer_list<eqx::lib::Point<T>>&& ps) noexcept
            :
            m_data()
        {
            assert(ps.size() == S);
            std::ranges::copy(ps, std::ranges::begin(this->m_data));
        }

        [[nodiscard]] constexpr
            std::pair<eqx::lib::Point<T>, eqx::lib::Point<T>>
            bounding_box() const noexcept
        {
            const auto [minx, maxx] = std::ranges::minmax(this->get_data(), {},
                &eqx::lib::Point<T>::get_x);
            const auto [miny, maxy] = std::ranges::minmax(this->get_data(), {},
                &eqx::lib::Point<T>::get_y);

            return std::pair<eqx::lib::Point<T>, eqx::lib::Point<T>>{
                eqx::lib::Point<T>{ minx.get_x(), miny.get_y() },
                eqx::lib::Point<T>{ maxx.get_x(), maxy.get_y() }};
        }

        [[nodiscard]] constexpr eqx::lib::Point<T> center() const noexcept
        {
            const auto [min, max] = this->bounding_box();
            return eqx::lib::Point<T>{
                std::midpoint(min.get_x(), max.get_x()),
                std::midpoint(min.get_y(), max.get_y()) };
        }

        template <std::size_t S2>
        [[nodiscard]] constexpr bool aabb(
            const Polygon<T, S2>& p) const noexcept
        {
            const auto [min1, max1] = this->bounding_box();
            const auto [min2, max2] = p.bounding_box();

            return !(max1.get_x() < min2.get_x()
                || max2.get_x() < min1.get_x()
                || max1.get_y() < min2.get_y()
                || max2.get_y() < min1.get_y());
        }

        constexpr void translate(const eqx::lib::Point<T>& p) noexcept
        {
            std::ranges::for_each(this->m_data, [p]
                (eqx::lib::Point<T>& val) noexcept -> void
                {
                    val.translate(p);
                });
        }

        constexpr void move(const eqx::lib::Point<T>& p) noexcept
        {
            this->translate(eqx::lib::Point<T>::translate(p,
                eqx::lib::Point<T>::negate(this->center())));
        }

        constexpr void rotate(const T radians) noexcept
        {
            std::ranges::for_each(this->m_data,
                [radians, pivot = this->center()]
                (eqx::lib::Point<T>& val) noexcept -> void
                {
                    val.rotate(radians, pivot);
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
                (const eqx::lib::Point<T>& p) noexcept -> void
                {
                    result += p.to_string();
                    result += '\n';
                });
            result.pop_back();
            return result;
        }

        [[nodiscard]] constexpr std::span<const eqx::lib::Point<T>, S>
            get_data() const noexcept
        {
            return this->m_data;
        }

    private:
        std::array<eqx::lib::Point<T>, S> m_data;
    };
}
