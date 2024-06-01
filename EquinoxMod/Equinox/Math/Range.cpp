module;

#include <Equinox/Macros.hpp>

export module Equinox.Math.Range;

export import :Decl;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Math.Core;

export namespace eqx
{
    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double median(const T& range) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        eqx::ENSURE_HARD(stdm::ranges::is_sorted(range),
            "Range Is Not Sorted!!!"sv);
        const auto len = stdm::ranges::size(range);
        if (eqx::isOdd(len))
        {
            return static_cast<double>(range.at((len - 1) / 2));
        }
        else
        {
            return static_cast<double>(
                range.at(len / 2) + range.at((len / 2) - 1)) / 2.0;
        }
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double average(const T& range) noexcept
    {
        using E = stdm::ranges::range_value_t<T>;
        return static_cast<double>(stdm::reduce(stdm::ranges::begin(range),
            stdm::ranges::end(range), eqx::c_Zero<E>, stdm::plus<void>{}))
            / static_cast<double>(stdm::ranges::size(range));
    }
}
