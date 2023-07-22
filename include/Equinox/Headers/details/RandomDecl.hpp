/*
 * Copyright (C) 2023 Anthony H. Grasso
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

#ifndef EQUINOX_DETAILS_RANDOMDECL_HPP
#define EQUINOX_DETAILS_RANDOMDECL_HPP

#include "Dependencies.hpp"

#include "../Misc.hpp"
#include "../Mathematics.hpp"

namespace eqx
{
    class Random
    {
    public:
        /**
         * Pure Static Class Is Not Meant To Be Constructed Or Copied
         */
        Random() = delete;
        Random(const Random&) = delete;
        Random(Random&&) = delete;
        Random& operator= (const Random&) = delete;
        Random& operator= (Random&&) = delete;
        ~Random() = delete;

        /**
         * @brief Simulate A Coin Flip
         *
         * @returns Either 1 Or 0
         */
        [[nodiscard]] static inline unsigned int flipCoin();

        /**
         * @brief Generate A Random Integral Type Number
         *
         * @param lowerBound Lowest Possible Value
         * @param upperBound Highest Possible Value
         *
         * @returns Random Integral Type Number
         *      In Range [lowerBound, upperBound]
         */
        template <typename T>
            requires std::integral<T>
        [[nodiscard]] static T randomNumber(T lowerBound, T upperBound);

        /**
         * @brief Generate A Random Floating Point Type Number
         * @brief Note That For Ranges Where lowerBound Is Negative And upperBound
         *      Positive There Is A Bias For The Generation Of (T)0.0, The P(0) Is
         *      Exactly 2/N Where N Is The Number Of Possible Generated Values.
         *      The Bias Is Sufficiently Small For The Typical Cases, However In
         *      The Case of [-e, e] Where e = std::numeric_limits<T>::denorm_min()
         *      (T)0.0 Has A 50% Probablility Of Generation. For Cases As Such It
         *      Is Recommended To Use Integral Types.
         *
         * @param lowerBound Lowest Possible Value
         * @param upperBound Highest Possible Value
         *
         * @returns Random Floating Point Type Number
         *      In Range [lowerBound, upperBound]
         */
        template <typename T>
            requires std::floating_point<T>
        [[nodiscard]] static T randomNumber(T lowerBound, T upperBound);

        /**
         * @brief Simulate A Dice Roll
         *
         * @param sides Number Of Sides On The Dice
         *
         * @returns An Unsigned Int In Range [1, sides]
         */
        [[nodiscard]] static inline unsigned int
            rollDice(unsigned int sides = 6U);

        /**
         * @brief Generate A Random Seed
         *
         * @returns Seed
         */
        [[nodiscard]] static inline unsigned int generateSeed();
    };
}

#endif // EQUINOX_DETAILS_RANDOMDECL_HPP
