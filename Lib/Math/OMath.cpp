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
            requires std::floating_point<T>
        [[nodiscard]] static constexpr bool approx(const T x,
            const T y) noexcept
        {
            return approx(x, y, static_cast<T>(0.0001L));
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr bool approx(const T x, const T y,
            const T e) noexcept
        {
            return (x + e > y) && (x - e < y);
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T to_radians(const T x) noexcept
        {
            return x * (std::numbers::pi_v<T> / T{180.0});
        }

        template <typename T>
            requires std::integral<T>
        [[nodiscard]] static constexpr double to_radians(const T x) noexcept
        {
            return to_radians(static_cast<double>(x));
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr
            std::conditional_t<std::integral<T>, double, T> sqrt(
            const T x) noexcept
        {
            if (std::is_constant_evaluated())
            {
                return eqx::lib::CT_Math::sqrt<T>(x);
            }
            else
            {
                assert(x >= T{0} && "Can't take negative sqrt!");
                return std::sqrt(x);
            }
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr float sqrtf(const T x) noexcept
        {
            if (std::is_constant_evaluated())
            {
                return eqx::lib::CT_Math::sqrtf<T>(x);
            }
            else
            {
                assert(x >= T{0} && "Can't take negative sqrt!");
                return std::sqrtf(x);
            }
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr T hypot2(const T x, const T y) noexcept
        {
            return (x * x) + (y * y);
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
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

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr
            std::conditional_t<std::integral<T>, double, T> sin(
            const T x) noexcept
        {
            if (std::is_constant_evaluated())
            {
                return eqx::lib::CT_Math::sin<T>(x);
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
                return eqx::lib::CT_Math::cos<T>(x);
            }
            else
            {
                return std::cos(x);
            }
        }
    };
}
