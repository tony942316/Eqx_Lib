export module Equinox.Math.Modulator;

import Eqx.Stdm;
import Equinox.Math.Core;

namespace eqx
{
    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_Pi6 = std::numbers::pi_v<T> / static_cast<T>(6.0);

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_Pi4 = std::numbers::pi_v<T> / static_cast<T>(4.0);

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_Pi3 = std::numbers::pi_v<T> / static_cast<T>(3.0);

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_Pi2 = std::numbers::pi_v<T> / static_cast<T>(2.0);

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_2Pi3 = static_cast<T>(2.0) * c_Pi3<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_3Pi4 = static_cast<T>(3.0) * c_Pi4<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_5Pi6 = static_cast<T>(5.0) * c_Pi6<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_7Pi6 = static_cast<T>(7.0) * c_Pi6<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_5Pi4 = static_cast<T>(5.0) * c_Pi4<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_4Pi3 = static_cast<T>(4.0) * c_Pi3<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_3Pi2 = static_cast<T>(3.0) * c_Pi2<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_5Pi3 = static_cast<T>(5.0) * c_Pi3<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_7Pi4 = static_cast<T>(7.0) * c_Pi4<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_11Pi6 = static_cast<T>(11.0) * c_Pi6<T>;

    export template <typename T>
        requires std::floating_point<T>
    constexpr auto c_2Pi = static_cast<T>(2.0) * std::numbers::pi_v<T>;

    template <typename T, T mod>
        requires std::floating_point<T>
    class Modulator
    {
    public:
        explicit constexpr Modulator(const T val) noexcept;

        [[nodiscard]] constexpr bool operator== (
            const Modulator<T, mod>& other) const noexcept;

        [[nodiscard]] constexpr T get() const noexcept;

    private:
        T m_Value;
    };

    export template <typename T>
    using Radians = Modulator<T, eqx::c_2Pi<T>>;

    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
    export template <typename T>
    using Degrees = Modulator<T, static_cast<T>(360.0)>;
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

    export template <typename T, T mod>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Modulator<T, mod>& lhs,
        const Modulator<T, mod>& rhs) noexcept;
}

export namespace eqx::literals
{
    consteval Radians<float> operator""_radF (const long double val) noexcept;

    consteval Radians<double> operator""_rad (const long double val) noexcept;

    consteval Radians<long double> operator""_radL (
        const long double val) noexcept;

    consteval Degrees<float> operator""_degF (const long double val) noexcept;

    consteval Degrees<double> operator""_deg (const long double val) noexcept;

    consteval Degrees<long double> operator""_degL (
        const long double val) noexcept;
}

// Implementations

export namespace eqx
{

    template <typename T, T mod>
        requires std::floating_point<T>
    constexpr Modulator<T, mod>::Modulator(const T val) noexcept
        :
        m_Value(eqx::isNegative(val)
            ? eqx::fmod(mod + eqx::fmod(val, mod), mod)
            : eqx::fmod(val, mod))
    {
    }

    template <typename T, T mod>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool Modulator<T, mod>::operator== (
        const Modulator<T, mod>& other) const noexcept
    {
        return equals(*this, other);
    }

    template <typename T, T mod>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T Modulator<T, mod>::get() const noexcept
    {
        return m_Value;
    }

    template <typename T, T mod>
        requires std::floating_point<T>
    [[nodiscard]] constexpr bool equals(const Modulator<T, mod>& lhs,
        const Modulator<T, mod>& rhs) noexcept
    {
        auto upperTolerance = Modulator<T, mod>{lhs.get() + eqx::c_FPT<T>};
        auto lowerTolerance = Modulator<T, mod>{lhs.get() - eqx::c_FPT<T>};
        return eqx::equals<T>(lhs.get(), rhs.get())
            || eqx::equals<T>(upperTolerance.get(), rhs.get())
            || eqx::equals<T>(lowerTolerance.get(), rhs.get());
    }
}

export namespace eqx::literals
{
    consteval Radians<float> operator""_radF (const long double val) noexcept
    {
        return Radians<float>{static_cast<float>(val)};
    }

    consteval Radians<double> operator""_rad (const long double val) noexcept
    {
        return Radians<double>{static_cast<double>(val)};
    }

    consteval Radians<long double> operator""_radL (
        const long double val) noexcept
    {
        return Radians<long double>{val};
    }

    consteval Degrees<float> operator""_degF (const long double val) noexcept
    {
        return Degrees<float>{static_cast<float>(val)};
    }

    consteval Degrees<double> operator""_deg (const long double val) noexcept
    {
        return Degrees<double>{static_cast<double>(val)};
    }

    consteval Degrees<long double> operator""_degL (
        const long double val) noexcept
    {
        return Degrees<long double>{val};
    }
}
