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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_RANDOMTESTERIMPL_IPP
#define PROVINGGROUNDS_TESTS_DETAILS_RANDOMTESTERIMPL_IPP

#include "RandomTesterDecl.hpp"

inline void RandomTester::test()
{
    std::cout << "Testing Random..." << std::endl;
    testRandomNumber();
    testFlipCoin();
    testRollDice();
    testGenerateSeed();
    UnitTester::printStatus();
    UnitTester::clear();
}

inline void RandomTester::testRandomNumber()
{
    constexpr auto runs = 1'000'000;
    auto randNum = 0;
    auto randNumDouble = 0.0;
    auto distInit = [](int lb, int ub)
    {
        auto dist = std::unordered_map<int, std::size_t>();
        dist.reserve(static_cast<std::size_t>(std::abs(ub - lb)));
        for (int i = lb; i <= ub; i++)
        {
            dist[i] = 0ULL;
        }
        return dist;
    };
    auto testDist = [](const std::unordered_map<int, std::size_t>& dist)
    {
        std::ranges::for_each(dist,
            [&dist](const auto& x)
            {
                const auto exp =(static_cast<double>(runs) /
                     static_cast<double>(dist.size()));
                const auto deviation = static_cast<double>(x.second) / exp;
                UnitTester::test(deviation, 0.9, UnitTesterFunctions::GTE);
                UnitTester::test(deviation, 1.1, UnitTesterFunctions::LTE);
            });
    };

    auto dist = distInit(0, 100);
    auto dist2 = distInit(-100, 0);
    auto dist3 = distInit(-100, 100);

    for (int i = 0; i < runs; i++)
    {
        randNum = eqx::Random::randomNumber(0, 100);
        dist.at(randNum)++;
        UnitTester::test(randNum, 0, UnitTesterFunctions::GTE);
        UnitTester::test(randNum, 100, UnitTesterFunctions::LTE);

        randNum = eqx::Random::randomNumber(-100, 0);
        dist2.at(randNum)++;
        UnitTester::test(randNum, -100, UnitTesterFunctions::GTE);
        UnitTester::test(randNum, 0, UnitTesterFunctions::LTE);

        randNum = eqx::Random::randomNumber(-100, 100);
        dist3.at(randNum)++;
        UnitTester::test(randNum, -100, UnitTesterFunctions::GTE);
        UnitTester::test(randNum, 100, UnitTesterFunctions::LTE);

        randNumDouble = eqx::Random::randomNumber(0.0, 1.0);
        UnitTester::test(randNumDouble, 0.0, UnitTesterFunctions::GTE);
        UnitTester::test(randNumDouble, 1.0, UnitTesterFunctions::LTE);

        randNumDouble = eqx::Random::randomNumber(-1.0, 0.0);
        UnitTester::test(randNumDouble, -1.0, UnitTesterFunctions::GTE);
        UnitTester::test(randNumDouble, 0.0, UnitTesterFunctions::LTE);

        randNumDouble = eqx::Random::randomNumber(-1.0, 1.0);
        UnitTester::test(randNumDouble, -1.0, UnitTesterFunctions::GTE);
        UnitTester::test(randNumDouble, 1.0, UnitTesterFunctions::LTE);

        randNumDouble = eqx::Random::randomNumber(0.0,
            std::numeric_limits<double>::max());
        UnitTester::test(randNumDouble, 0.0, UnitTesterFunctions::GTE);
        UnitTester::test(randNumDouble, std::numeric_limits<double>::max(),
            UnitTesterFunctions::LTE);

        randNumDouble = eqx::Random::randomNumber(
            std::numeric_limits<double>::lowest(), 0.0);
        UnitTester::test(randNumDouble, std::numeric_limits<double>::lowest(),
            UnitTesterFunctions::GTE);
        UnitTester::test(randNumDouble, 0.0, UnitTesterFunctions::LTE);

        randNumDouble = eqx::Random::randomNumber(
            std::numeric_limits<double>::lowest(),
            std::numeric_limits<double>::max());
        UnitTester::test(randNumDouble, std::numeric_limits<double>::lowest(),
            UnitTesterFunctions::GTE);
        UnitTester::test(randNumDouble, std::numeric_limits<double>::max(),
            UnitTesterFunctions::LTE);
    }

    testDist(dist);
    testDist(dist2);
    testDist(dist3);
}

inline void RandomTester::testFlipCoin()
{
    constexpr auto runs = 1'000'000;
    auto randCoin = 0U;
    auto heads = 0U;
    auto tails = 0U;

    for (int i = 0; i < runs; i++)
    {
        randCoin = eqx::Random::flipCoin();
        randCoin == 1U ? heads++ : tails++;
        UnitTester::test(randCoin, 0U, UnitTesterFunctions::GTE);
        UnitTester::test(randCoin, 1U, UnitTesterFunctions::LTE);
    }

    constexpr auto expected = runs / 2.0;
    auto deviation = heads / expected;
    UnitTester::test(deviation, 0.9, UnitTesterFunctions::GTE);
    UnitTester::test(deviation, 1.1, UnitTesterFunctions::LTE);
    deviation = tails / expected;
    UnitTester::test(deviation, 0.9, UnitTesterFunctions::GTE);
    UnitTester::test(deviation, 1.1, UnitTesterFunctions::LTE);
}

inline void RandomTester::testRollDice()
{
    constexpr auto runs = 1'000'000;
    auto randNum = 0U;

    for (int i = 0; i < runs; i++)
    {
        randNum = eqx::Random::rollDice();
        UnitTester::test(randNum, 1U, UnitTesterFunctions::GTE);
        UnitTester::test(randNum, 6U, UnitTesterFunctions::LTE);

        randNum = eqx::Random::rollDice(20U);
        UnitTester::test(randNum, 1U, UnitTesterFunctions::GTE);
        UnitTester::test(randNum, 20U, UnitTesterFunctions::LTE);

        randNum = eqx::Random::rollDice(50U);
        UnitTester::test(randNum, 1U, UnitTesterFunctions::GTE);
        UnitTester::test(randNum, 50U, UnitTesterFunctions::LTE);

        randNum = eqx::Random::rollDice(100U);
        UnitTester::test(randNum, 1U, UnitTesterFunctions::GTE);
        UnitTester::test(randNum, 100U, UnitTesterFunctions::LTE);
    }
}

inline void RandomTester::testGenerateSeed()
{
    constexpr auto runs = 1'000'000;
    auto seed = 0U;
    auto dist = std::unordered_map<unsigned int, std::size_t>();
    dist.reserve(runs);

    for (int i = 0; i < runs; i++)
    {
        seed = eqx::Random::generateSeed();
        if (dist.contains(seed))
        {
            dist.at(seed)++;
        }
        else
        {
            dist[seed] = 1U;
        }
    }

    auto collisions = 0ULL;
    constexpr auto expectedVariance = 1ULL;
    std::ranges::for_each(dist,
        [expectedVariance, &collisions](const auto& x)
        {
            if (x.second > 1U)
            {
                auto count = x.second - 1U;
                collisions += count;
                const auto deviation = count - expectedVariance;
                UnitTester::test(deviation, 3ULL, UnitTesterFunctions::LTE);
            }
        });

    const auto totalVariance = static_cast<double>(collisions) / 
        static_cast<double>(runs);
    UnitTester::test(totalVariance, 0.001, UnitTesterFunctions::LTE);
}

#endif // PROVINGGROUNDS_TESTS_DETAILS_RANDOMTESTERIMPL_IPP
