export module Equinox.Math.Trig:Decl;

import Eqx.Stdm;
import Equinox.Math.Modulator;

export namespace eqx
{
    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> degreesToRadians(
        const eqx::Degrees<T> degrees) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Degrees<T> radiansToDegrees(
        const eqx::Radians<T> radians) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T sin(const eqx::Radians<T> radians) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T cos(const eqx::Radians<T> radians) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T tan(const eqx::Radians<T> radians) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> asin(const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> acos(const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> atan(const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> atan2(const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr stdm::pair<eqx::Radians<T>, eqx::Radians<T>> arcsin(
        const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr stdm::pair<eqx::Radians<T>, eqx::Radians<T>> arccos(
        const T val) noexcept;
}
