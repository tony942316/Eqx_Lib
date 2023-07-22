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

#ifndef EQUINOX_DETAILS_STOPWATCHIMPL_IPP
#define EQUINOX_DETAILS_STOPWATCHIMPL_IPP

#include "StopWatchDecl.hpp"

namespace eqx
{
    inline StopWatch::StopWatch() noexcept
    {
        start();
    }

    inline void StopWatch::start() noexcept
    {
        m_StartTime = std::chrono::steady_clock::now();
        m_EndTime = m_StartTime;
    }

    inline void StopWatch::stop() noexcept
    {
        m_EndTime = std::chrono::steady_clock::now();
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] T StopWatch::getDuration() const noexcept
    {
        return std::chrono::duration_cast<T>(m_EndTime - m_StartTime);
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] long long StopWatch::getTime() const noexcept
    {
        return getDuration<T>().count();
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] long long StopWatch::readTime() noexcept
    {
        stop();
        return getTime<T>();
    }

    [[nodiscard]] inline double StopWatch::getSeconds() const noexcept
    {
        return static_cast<double>(getTime<std::chrono::nanoseconds>()) / 1E9;
    }

    [[nodiscard]] inline double StopWatch::readSeconds() noexcept
    {
        return static_cast<double>(readTime<std::chrono::nanoseconds>()) / 1E9;
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] std::string StopWatch::toString() const
    {
        return (std::stringstream() << getDuration<T>()).str();
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] std::string toString(const StopWatch& watch)
    {
        return watch.toString<T>();
    }
}

#endif // EQUINOX_DETAILS_STOPWATCHIMPL_IPP
