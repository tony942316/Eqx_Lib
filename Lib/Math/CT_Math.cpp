export module Eqx.Lib.CT_Math;

import <Eqx/std.hpp>;

export namespace eqx::lib
{
    class CT_Math
    {
    public:
        CT_Math() = delete;
        CT_Math(const CT_Math&) = delete;
        CT_Math(CT_Math&&) = delete;
        CT_Math& operator= (const CT_Math&) = delete;
        CT_Math& operator= (CT_Math&&) = delete;
        ~CT_Math() = delete;

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T sqrt(const T x) noexcept
        {
            assert(x >= T{0.0} && "Can't take negative sqrt!");

            if (T{0.0} < (x + static_cast<T>(0.0001))
                && T{0.0} > (x - static_cast<T>(0.0001))) [[unlikely]]
            {
                return T{0.0};
            }
            else [[likely]]
            {
                auto guess = std::ranges::max(x, T{1.0});

                for (auto i = 0; i < 20; ++i)
                    guess = T{0.5} * (guess + (x / guess));

                return guess;
            }
        }

        template <typename T>
            requires std::integral<T>
        [[nodiscard]] static constexpr double sqrt(const T x) noexcept
        {
            return sqrt(static_cast<double>(x));
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr float sqrtf(const T x) noexcept
        {
            if constexpr (std::same_as<std::remove_cvref<T>, float>)
            {
                return sqrt(x);
            }
            else
            {
                return sqrt(static_cast<float>(x));
            }
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T sin(const T x) noexcept
        {
            return ((T{16.0} * x) * (std::numbers::pi_v<T> - x))
                / ((T{5.0} * std::numbers::pi_v<T> * std::numbers::pi_v<T>)
                - ((T{4.0} * x) * (std::numbers::pi_v<T> - x)));
        }

        template <typename T>
            requires std::integral<T>
        [[nodiscard]] static constexpr double sin(const T x) noexcept
        {
            return sin(static_cast<double>(x));
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr float sinf(const T x) noexcept
        {
            if constexpr (std::same_as<std::remove_cvref<T>, float>)
            {
                return sin(x);
            }
            else
            {
                return sin(static_cast<float>(x));
            }
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T cos(const T x) noexcept
        {
            return sin(x + (std::numbers::pi_v<T> / T{2.0}));
        }

        template <typename T>
            requires std::integral<T>
        [[nodiscard]] static constexpr double cos(const T x) noexcept
        {
            return cos(static_cast<double>(x));
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr float cosf(const T x) noexcept
        {
            if constexpr (std::same_as<std::remove_cvref<T>, float>)
            {
                return cos(x);
            }
            else
            {
                return cos(static_cast<float>(x));
            }
        }

    private:
    };
}
