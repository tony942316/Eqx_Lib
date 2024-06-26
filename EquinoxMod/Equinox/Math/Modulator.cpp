export module Equinox.Math.Modulator;

export import :Decl;

import Eqx.Stdm;
import Equinox.Math.Core;

namespace eqx
{
    template <typename T, T mod>
        requires stdm::floating_point<T>
    constexpr Modulator<T, mod>::Modulator(const T val) noexcept
        :
        m_Value(eqx::isNegative(val)
            ? eqx::fmod(mod + eqx::fmod(val, mod), mod)
            : eqx::fmod(val, mod))
    {
    }

    template <typename T, T mod>
        requires stdm::floating_point<T>
    constexpr T Modulator<T, mod>::get() const noexcept
    {
        return m_Value;
    }

    template <typename T, T mod>
        requires stdm::floating_point<T>
    constexpr bool Modulator<T, mod>::operator== (
        const Modulator<T, mod>& other) const noexcept
    {
        return equals(*this, other);
    }

    template <typename T, T mod>
        requires stdm::floating_point<T>
    constexpr bool equals(const Modulator<T, mod>& lhs,
        const Modulator<T, mod>& rhs) noexcept
    {
        auto upperTolerance = Modulator<T, mod>{lhs.get() + eqx::c_FPT<T>};
        auto lowerTolerance = Modulator<T, mod>{lhs.get() - eqx::c_FPT<T>};
        return eqx::equals<T>(lhs.get(), rhs.get())
            || eqx::equals<T>(upperTolerance.get(), rhs.get())
            || eqx::equals<T>(lowerTolerance.get(), rhs.get());
    }
}

namespace eqx::literals
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
