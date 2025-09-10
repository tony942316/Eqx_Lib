export module Eqx.Lib.Math;

import <Eqx/std.hpp>;

export namespace eqx::lib
{
    class Math
    {
    public:
        Math() = delete;
        Math(const Math&) = delete;
        Math(Math&&) = delete;
        Math& operator= (const Math&) = delete;
        Math& operator= (Math&&) = delete;
        ~Math() = delete;

        template <typename T>
            requires std::floating_point<T>
        static inline constexpr auto c_fpt = static_cast<T>(0.001F);

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr bool signbit(const T x) noexcept
        {
            return x < T{ 0 } ? true : false;
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr T abs(const T x) noexcept
        {
            return x < T{ 0 } ? -x : x;
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr bool near(const T x, const T y,
            const T eps = c_fpt<T>) noexcept
        {
            return abs(x - y) <= std::ranges::max(eps,
                std::ranges::max(abs(x), abs(y)) * static_cast<T>(0.000001F));
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T sqrt(const T x) noexcept
        {
            assert(x >= T{ 0 } && "Can't take negative sqrt!");

            if (near(x, T{ 0 }, static_cast<T>(1E-20F))) [[unlikely]]
            {
                return T{ 0 };
            }
            else [[likely]]
            {
                auto y = x;
                auto scale = T{ 1 };

                while (y > T{ 4 })
                {
                    y *= static_cast<T>(0.25F);
                    scale *= T{ 2 };
                }

                while (y < static_cast<T>(0.25F))
                {
                    y *= T{ 4 };
                    scale *= static_cast<T>(0.5F);
                }

                auto guess = T{ 1 };

                for (auto i = 0; i < 4; ++i)
                {
                    guess = static_cast<T>(0.5F) * (guess + (y / guess));
                }

                return guess * scale;
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
