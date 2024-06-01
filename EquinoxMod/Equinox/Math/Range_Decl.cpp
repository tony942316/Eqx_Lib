export module Equinox.Math.Range:Decl;

import Eqx.Stdm;

export namespace eqx
{
    template <typename T>
    concept ArithmeticRange = stdm::ranges::range<T>
        && stdm::is_arithmetic_v<stdm::ranges::range_value_t<T>>;

    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double median(const T& range) noexcept;

    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double average(const T& range) noexcept;
}
