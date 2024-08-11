/*
 * Copyright (C) 2024 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

module;

#include <Equinox/Macros.hpp>

export module Equinox.Math.Range;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Math.Core;

export namespace eqx
{
    template <typename T>
    concept ArithmeticRange = std::ranges::range<T>
        && std::is_arithmetic_v<std::ranges::range_value_t<T>>;

    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double median(const T& range) noexcept;

    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double average(const T& range) noexcept;
}

// Implementations

export namespace eqx
{
    template <typename T>
        requires eqx::ArithmeticRange<T>
    [[nodiscard]] constexpr double median(const T& range) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        eqx::ENSURE_HARD(std::ranges::is_sorted(range),
            "Range Is Not Sorted!!!"sv);
        const auto len = std::ranges::size(range);
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
        using E = std::ranges::range_value_t<T>;
        return static_cast<double>(std::reduce(std::ranges::begin(range),
            std::ranges::end(range), eqx::c_Zero<E>, std::plus<void>{}))
            / static_cast<double>(std::ranges::size(range));
    }
}
