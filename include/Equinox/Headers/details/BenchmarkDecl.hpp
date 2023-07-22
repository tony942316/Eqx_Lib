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

#ifndef EQUINOX_DETAILS_BENCHMARKDECL_HPP
#define EQUINOX_DETAILS_BENCHMARKDECL_HPP

#include "Dependencies.hpp"

#include "../StopWatch.hpp"

namespace eqx
{
    class Benchmark
    {
    public:
        /**
         * Trivial Operation
         */
        Benchmark() = default;
        Benchmark(const Benchmark&) = default;
        Benchmark(Benchmark&&) = default;
        Benchmark& operator= (const Benchmark&) = default;
        Benchmark& operator= (Benchmark&&) = default;
        ~Benchmark() = default;

        /**
         * @brief Time How Long It Takes To Run The Function
         *
         * @param func Function To Be Invoked
         * @param args Arguments func Is Invoked On
         */
        template <typename Func, typename... Args>
            requires std::invocable<Func, Args&&...>
        void bench(Func& func, Args&&... args)
            noexcept(std::is_nothrow_invocable_v<Func, Args&&...>);

        /**
         * @brief Time How Long It Takes To Run The Function On Average
         *
         * @param runs The Number Of Times The Function Is Run
         * @param func Function To Be Invoked
         * @param args Arguments func Is Invoked On
         */
        template <typename Func, typename... Args>
            requires std::invocable<Func, Args&&...>
        void avgBench(unsigned int runs, Func& func, Args&&... args)
            noexcept(std::is_nothrow_invocable_v<Func, Args&&...>);

        /**
         * @brief Time How Long It Takes To Run The Function
         *
         * @param func Function To Be Invoked
         * @param args Arguments func Is Invoked On
         */
        template <typename Func, typename... Args>
            requires std::invocable<Func, Args&&...>
        static Benchmark runBench(Func& func, Args&&... args)
            noexcept(std::is_nothrow_invocable_v<Func, Args&&...>);

        /**
         * @brief Time How Long It Takes To Run The Function On Average
         *
         * @param runs The Number Of Times The Function Is Run
         * @param func Function To Be Invoked
         * @param args Arguments func Is Invoked On
         */
        template <typename Func, typename... Args>
            requires std::invocable<Func, Args&&...>
        static Benchmark runAvgBench(unsigned int runs, Func& func,
            Args&&... args)
                noexcept(std::is_nothrow_invocable_v<Func, Args&&...>);

        /**
         * @brief Get Result Of Last Benchmark In T Units
         *
         * @returns T Units Of Last Benchmark
         */
        template <typename T = std::chrono::milliseconds>
            requires TimeUnit<T>
        [[nodiscard]] long long getBench() const noexcept;

        /**
         * @brief Build A String Representing The Time It Took To Run
         *      The Function
         *
         * @returns std::string Of Form "Bench: X TimeUnits"
         */
        template <typename T = std::chrono::milliseconds>
            requires TimeUnit<T>
        [[nodiscard]] std::string toString() const;

    private:
        std::chrono::nanoseconds m_Bench;
    };

    /**
     * @brief Build A String Representing A eqx::Benchmark
     *
     * @returns std::string Of Form "Bench: X TimeUnits"
     */
    template <typename T = std::chrono::milliseconds>
        requires TimeUnit<T>
    [[nodiscard]] std::string toString(const Benchmark& benchmark);
}


#endif // EQUINOX_DETAILS_BENCHMARKDECL_HPP
