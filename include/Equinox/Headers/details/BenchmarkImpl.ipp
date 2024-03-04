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

#ifndef EQUINOX_DETAILS_BENCHMARKIMPL_IPP
#define EQUINOX_DETAILS_BENCHMARKIMPL_IPP

#include "BenchmarkDecl.hpp"

namespace eqx
{
    template <typename Func, typename... Args>
        requires std::invocable<Func, Args&&...>
    void Benchmark::bench(Func& func, Args&&... args)
        noexcept(std::is_nothrow_invocable_v<Func, Args&&...>)
    {
        auto timer = StopWatch();
        timer.start();
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        timer.stop();
        m_Bench = timer.getDuration<std::chrono::nanoseconds>();
    }

    template <typename Func, typename... Args>
        requires std::invocable<Func, Args&&...>
    void Benchmark::avgBench(unsigned int runs, Func& func, Args&&... args)
        noexcept(std::is_nothrow_invocable_v<Func, Args&&...>)
    {
        // Note mutating functions and args may pose issues...
        auto timer = StopWatch();
        timer.start();
        for (unsigned int i = 0U; i < runs; i++)
        {
            std::invoke(func, std::forward<Args>(args)...);
        }
        timer.stop();
        m_Bench = static_cast<std::chrono::nanoseconds>(
            timer.getTime<std::chrono::nanoseconds>() / runs);
    }

    template <typename Func, typename... Args>
        requires std::invocable<Func, Args&&...>
    Benchmark Benchmark::runBench(Func& func, Args&&... args)
        noexcept(std::is_nothrow_invocable_v<Func, Args&&...>)
    {
        auto result = Benchmark();
        result.bench(std::forward<Func>(func), std::forward<Args>(args)...);
        return result;
    }

    template <typename Func, typename... Args>
        requires std::invocable<Func, Args&&...>
    Benchmark Benchmark::runAvgBench(unsigned int runs, Func& func,
        Args&&... args)
            noexcept(std::is_nothrow_invocable_v<Func, Args&&...>)
    {
        auto result = Benchmark();
        result.avgBench(runs, std::forward<Func>(func),
            std::forward<Args>(args)...);
        return result;
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] long long Benchmark::getBench() const noexcept
    {
        return std::chrono::duration_cast<T>(m_Bench).count();
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] std::string Benchmark::toString() const
    {
        return (std::stringstream() << "Bench: " <<
            std::chrono::duration_cast<T>(m_Bench)).str();
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] std::string toString(const Benchmark& benchmark)
    {
        return benchmark.toString<T>();
    }
}

#endif // EQUINOX_DETAILS_BENCHMARKIMPL_IPP
