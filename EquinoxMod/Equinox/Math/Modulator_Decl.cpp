export module Equinox.Math.Modulator:Decl;

import Eqx.Stdm;

namespace eqx
{
    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_Pi6 = stdm::numbers::pi_v<T> / static_cast<T>(6.0);

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_Pi4 = stdm::numbers::pi_v<T> / static_cast<T>(4.0);

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_Pi3 = stdm::numbers::pi_v<T> / static_cast<T>(3.0);

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_Pi2 = stdm::numbers::pi_v<T> / static_cast<T>(2.0);

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_2Pi3 = static_cast<T>(2.0) * c_Pi3<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_3Pi4 = static_cast<T>(3.0) * c_Pi4<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_5Pi6 = static_cast<T>(5.0) * c_Pi6<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_7Pi6 = static_cast<T>(7.0) * c_Pi6<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_5Pi4 = static_cast<T>(5.0) * c_Pi4<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_4Pi3 = static_cast<T>(4.0) * c_Pi3<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_3Pi2 = static_cast<T>(3.0) * c_Pi2<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_5Pi3 = static_cast<T>(5.0) * c_Pi3<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_7Pi4 = static_cast<T>(7.0) * c_Pi4<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_11Pi6 = static_cast<T>(11.0) * c_Pi6<T>;

    export template <typename T>
        requires stdm::floating_point<T>
    inline constexpr auto c_2Pi = static_cast<T>(2.0) * stdm::numbers::pi_v<T>;

    template <typename T, T mod>
        requires stdm::floating_point<T>
    class Modulator
    {
    public:
        explicit constexpr Modulator(const T val) noexcept;

        constexpr bool operator== (
            const Modulator<T, mod>& other) const noexcept;

        constexpr T get() const noexcept;

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
        requires stdm::floating_point<T>
    constexpr bool equals(const Modulator<T, mod>& lhs,
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
