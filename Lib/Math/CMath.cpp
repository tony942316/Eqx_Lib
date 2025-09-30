// CMath.cpp

export module Eqx.Lib.CMath;

import <Eqx/std.hpp>;

import Eqx.Lib.Math;

export namespace eqx::lib
{
    class CMath
    {
    public:
        CMath() = delete;
        CMath(const CMath&)= delete;
        CMath(CMath&&) = delete;
        CMath& operator= (const CMath&) = delete;
        CMath& operator= (CMath&&) = delete;
        ~CMath() = delete;

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr
            std::conditional_t<std::integral<T>, double, T> sqrt(
            const T x) noexcept
        {
            if (std::is_constant_evaluated())
            {
                return eqx::lib::Math::sqrt<T>(x);
            }
            else
            {
                assert(x >= T{ 0 } && "Can't take negative sqrt!");
                return std::sqrt(x);
            }
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr float sqrtf(const T x) noexcept
        {
            if (std::is_constant_evaluated())
            {
                return eqx::lib::Math::sqrtf<T>(x);
            }
            else
            {
                assert(x >= T{ 0 } && "Can't take negative sqrt!");
                return std::sqrtf(x);
            }
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr
            std::conditional_t<std::integral<T>, double, T> hypot(const T x,
            const T y) noexcept
        {
            if (std::is_constant_evaluated())
            {
                return eqx::lib::Math::hypot<T>(x, y);
            }
            else
            {
                return std::hypot(x, y);
            }
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr
            std::conditional_t<std::integral<T>, double, T> sin(
            const T x) noexcept
        {
            if (std::is_constant_evaluated())
            {
                return eqx::lib::Math::sin<T>(x);
            }
            else
            {
                return std::sin(x);
            }
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr
            std::conditional_t<std::integral<T>, double, T> cos(
            const T x) noexcept
        {
            if (std::is_constant_evaluated())
            {
                return eqx::lib::Math::cos<T>(x);
            }
            else
            {
                return std::cos(x);
            }
        }
    };
}
