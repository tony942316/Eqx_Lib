export module Equinox.Math.Trig:Decl;

import Eqx.Stdm;

export namespace eqx
{
    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T degreesToRadians(const T degrees) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T radiansToDegrees(const T radians) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T angAbs(const T radians) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T sin(const T radians) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T cos(const T radians) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T asin(const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T acos(const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr stdm::pair<T, T> arcsin(const T val) noexcept;

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr stdm::pair<T, T> arccos(const T val) noexcept;
}
