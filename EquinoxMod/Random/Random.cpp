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

export module Eqx.Lib.Random;

#include <Eqx/std.hpp>

import Eqx.Lib.Misc;

using namespace std::literals;

namespace eqx
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    auto rd = std::random_device{};
    auto eng = std::mt19937_64{rd()};
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
}

export namespace eqx
{
    template <typename T>
        requires std::integral<T>
    [[nodiscard]] inline T randomNumber(const T lb, const T ub) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] inline T randomNumber(const T lb, const T ub) noexcept;

    [[nodiscard]] inline unsigned int flipCoin() noexcept;

    [[nodiscard]] inline unsigned int rollDice(unsigned int sides) noexcept;

    [[nodiscard]] constexpr unsigned int generateSeed(
        const std::string_view timeMacro = "10:10:10"sv) noexcept;
}

// Implementations

export namespace eqx
{
    template <typename T>
        requires std::integral<T>
    [[nodiscard]] inline T randomNumber(const T lb, const T ub) noexcept
    {
        eqx::ENSURE_HARD(lb <= ub, "Upper Bound Less Than Lower Bound!!!"sv);
        return std::uniform_int_distribution<T>{lb, ub}(eng);
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] inline T randomNumber(const T lb, const T ub) noexcept
    {
        eqx::ENSURE_HARD(lb < ub, "Upper Bound Less Than Lower Bound!!!"sv);
        eqx::ENSURE_HARD(ub < std::numeric_limits<T>::max(),
            "Upper Bound Too Large!!!"sv);
        return std::uniform_real_distribution<T>{
            lb, std::nextafter(ub, std::numeric_limits<T>::max())}(eng);
    }

    [[nodiscard]] inline unsigned int flipCoin() noexcept
    {
        return randomNumber(0U, 1U);
    }

    [[nodiscard]] inline unsigned int rollDice(unsigned int sides) noexcept
    {
        eqx::ENSURE_HARD(sides >= 3, "Too Few Sides!!!"sv);
        return randomNumber(1U, sides);
    }


    [[nodiscard]] constexpr unsigned int generateSeed(
        const std::string_view timeMacro) noexcept
    {
        if (std::is_constant_evaluated())
        {
            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return static_cast<unsigned int>(timeMacro[0]) +
                static_cast<unsigned int>(timeMacro[1]) +
                static_cast<unsigned int>(timeMacro[2]) +
                static_cast<unsigned int>(timeMacro[3]) +
                static_cast<unsigned int>(timeMacro[4]) +
                static_cast<unsigned int>(timeMacro[5]) +
                static_cast<unsigned int>(timeMacro[6]) +
                static_cast<unsigned int>(timeMacro[7]);
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            return static_cast<unsigned int>(rd());
        }
    }
}
