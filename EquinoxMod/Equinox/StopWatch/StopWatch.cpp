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

#include "Equinox/Macros.hpp"

export module Equinox.StopWatch;

export import :Decl;

import Eqx.Stdm;

export namespace eqx
{
    inline void StopWatch::start() noexcept
    {
        m_StartTime = stdm::chrono::steady_clock::now();
        m_EndTime = m_StartTime;
    }

    inline void StopWatch::stop() noexcept
    {
        m_EndTime = stdm::chrono::steady_clock::now();
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] T StopWatch::getDuration() const noexcept
    {
        return stdm::chrono::duration_cast<T>(m_EndTime - m_StartTime);
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
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return static_cast<double>(getTime<stdm::chrono::nanoseconds>()) / 1E9;
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    [[nodiscard]] inline double StopWatch::readSeconds() noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return static_cast<double>(readTime<stdm::chrono::nanoseconds>()) / 1E9;
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] stdm::string StopWatch::toString() const
    {
        return (stdm::stringstream{} << getDuration<T>()).str();
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] stdm::string toString(const StopWatch& watch)
    {
        return watch.toString<T>();
    }
}
