export module Eqx.Lib.Math;

import <Eqx/std.hpp>;

import Eqx.Lib.CT_Math;

export namespace eqx::lib
{
    class Math
    {
    public:
        Math() = delete;
        Math(const Math&)= delete;
        Math(Math&&) = delete;
        Math& operator= (const Math&) = delete;
        Math& operator= (Math&&) = delete;
        ~Math() = delete;

        template <typename T>
        [[nodiscard]] static constexpr
            std::conditional_t<std::integral<T>, double, T> sqrt(
            const T x) noexcept
        {
            if (std::is_constant_evaluated())
            {
                eqx::lib::CT_Math::sqrt<T>(x);
            }
            else
            {
                assert(x > -1 && "Can't take negative sqrt!");
                return std::sqrt(x);
            }
        }

        template <typename T>
        [[nodiscard]] static constexpr T hypot2(const T x, const T y) noexcept
        {
            return (x * x) + (y * y);
        }

        template <typename T>
        [[nodiscard]] static constexpr
            std::conditional_t<std::integral<T>, double, T> hypot(const T x,
            const T y) noexcept
        {
            if (std::is_constant_evaluated())
            {
                return eqx::lib::Math::sqrt<T>(eqx::lib::Math::hypot2<T>(x, y));
            }
            else
            {
                return std::hypot(x, y);
            }
        }
    };
}
