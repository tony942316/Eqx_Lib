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
        [[nodiscard]] static constexpr
            std::conditional_t<std::integral<T>, double, T> sqrt(
            const T x) noexcept
        {
            assert(x > -1 && "Can't take negative sqrt!");
            if (x == 0)
            {
                return 0;
            }
            else
            {
                auto guess = x > 1 ?
                    std::conditional_t<std::integral<T>, double, T>{x}
                    : std::conditional_t<std::integral<T>, double, T>{1.0};

                for (int i = 0; i < 20; ++i)
                    guess = 0.5f * (guess + (x / guess));

                return guess;
            }
        }

    private:
    };
}
