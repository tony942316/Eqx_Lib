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
            requires std::floating_point<T> || std::signed_integral<T>
        [[nodiscard]] static constexpr T abs(const T x) noexcept
        {
            return x < T{ 0 } ? -x : x;
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T trunc(const T x) noexcept
        {
            if (abs(x) < static_cast<T>(
                std::numeric_limits<long long>::max())) [[likely]]
            {
                return static_cast<T>(static_cast<long long>(x));
            }
            else
            {
                assert(false && "Panic!");
                return x;
            }
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T floor(const T x) noexcept
        {
            if (signbit(x) == true)
            {
                if (near(x, trunc(x), static_cast<T>(1E-7))) [[unlikely]]
                {
                    return trunc(x);
                }
                else [[likely]]
                {
                    return trunc(x) - T{ 1 };
                }
            }
            else
            {
                return trunc(x);
            }
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
            return sqrt(static_cast<float>(x));
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr T hypot2(const T x, const T y) noexcept
        {
            return (x * x) + (y * y);
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T hypot(const T x, const T y) noexcept
        {
            return sqrt(hypot2(x, y));
        }

        template <typename T>
            requires std::integral<T>
        [[nodiscard]] static constexpr T hypot(const T x, const T y) noexcept
        {
            return sqrt(hypot2(static_cast<double>(x), static_cast<double>(y)));
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T to_radians(const T x) noexcept
        {
            return x * (std::numbers::pi_v<T> / T{ 180 });
        }

        template <typename T>
            requires std::integral<T>
        [[nodiscard]] static constexpr double to_radians(const T x) noexcept
        {
            return to_radians(static_cast<double>(x));
        }

        template <typename T>
            requires std::is_arithmetic_v<T>
        [[nodiscard]] static constexpr float to_radiansf(const T x) noexcept
        {
            return to_radians(static_cast<float>(x));
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T sin(const T x) noexcept
        {
            if (x < T{ 0 })
            {
                return -sin(-x);
            }
            else
            {
                const auto n = floor(x / (T{ 2 } * std::numbers::pi_v<T>));
                auto A = x - (n * T{ 2 } * std::numbers::pi_v<T>);
                auto ident = T{ 1 };

                if (A > std::numbers::pi_v<T>)
                {
                    ident = T{ -1 };
                    A -= std::numbers::pi_v<T>;
                }

                return ident * (((T{ 16 } * A) * (std::numbers::pi_v<T> - A))
                    / ((T{ 5 } * std::numbers::pi_v<T> * std::numbers::pi_v<T>)
                    - ((T{ 4 } * A) * (std::numbers::pi_v<T> - A))));
            }
        }

        template <typename T>
            requires std::integral<T>
        [[nodiscard]] static constexpr double sin(const T x) noexcept
        {
            return sin(static_cast<double>(x));
        }

        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static constexpr T cos(const T x) noexcept
        {
            return sin(x + (std::numbers::pi_v<T> / T{ 2 }));
        }

        template <typename T>
            requires std::integral<T>
        [[nodiscard]] static constexpr double cos(const T x) noexcept
        {
            return cos(static_cast<double>(x));
        }

    private:
    };
}
