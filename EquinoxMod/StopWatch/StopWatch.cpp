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

import Eqx.Stdm;

export namespace eqx
{
    namespace TimeTypes
    {
        using t_NS = std::chrono::nanoseconds;
        using t_US = std::chrono::microseconds;
        using t_MS = std::chrono::milliseconds;
        using t_S = std::chrono::seconds;
    }

    template <typename T>
    concept TimeUnit = std::is_same_v<T, std::chrono::nanoseconds>
        || std::is_same_v<T, std::chrono::microseconds>
        || std::is_same_v<T, std::chrono::milliseconds>
        || std::is_same_v<T, std::chrono::seconds>;

    class StopWatch
    {
    public:
        /**
         * Trivial Type
         */
        StopWatch() = default;
        StopWatch(const StopWatch&) = default;
        StopWatch(StopWatch&&) = default;
        StopWatch& operator= (const StopWatch&) = default;
        StopWatch& operator= (StopWatch&&) = default;
        ~StopWatch() = default;

        /**
         * @brief Set The Start Time Of The StopWatch And Reset The End Time
         */
        void start() noexcept;

        /**
         * @brief Set The End Time Of The StopWatch
         */
        void stop() noexcept;

        /**
         * @brief Gives The std::chrono::duration<T> Between The Last
         *      this->start Call And this->stop
         *
         * @returns std::chrono::duration<T> Between The Last this->start()
         *      Call And this->stop Call
         */
        template <typename T = std::chrono::milliseconds>
            requires TimeUnit<T>
        [[nodiscard]] T getDuration() const noexcept;

        /**
         * @brief Gives The Time Between The Last this->start Call And
         *      this->stop Call In Milliseconds (Or T If Defined)
         *
         * @returns long long Representing The Milliseconds (Or T) Past Between
         *      The Last this->start Call And this->stop Call
         */
        template <typename T = std::chrono::milliseconds>
            requires TimeUnit<T>
        [[nodiscard]] long long getTime() const noexcept;

        /**
         * @brief Gives The Time Between The Last this->start Call And
         *      The Current Time In Milliseconds (Or T If Defined), Note That
         *      this->stop Is Called
         *
         * @returns long long Representing The Milliseconds (Or T) Past Between
         *      The Last this->start Call And The Current Time
         */
        template <typename T = std::chrono::milliseconds>
            requires TimeUnit<T>
        [[nodiscard]] long long readTime() noexcept;

        /**
         * @brief Gives Time Past In Seconds With Fine Precision
         *
         * @returns double 1500 Milliseconds Would Be 1.5 Seconds
         */
        [[nodiscard]] double getSeconds() const noexcept;

        /**
         * @brief Calls this->stop Then
         *      Gives Time Past In Seconds With Fine Precision
         *
         * @returns double 1500 Milliseconds Would Be 1.5 Seconds
         */
        [[nodiscard]] double readSeconds() noexcept;

        /**
         * @brief Gives The String Representation Of The Current Duration
         *
         * @returns std::string "{TimePast}ms"
         */
        template <typename T = std::chrono::milliseconds>
            requires TimeUnit<T>
        [[nodiscard]] std::string toString() const;

    private:
        std::chrono::steady_clock::time_point m_StartTime, m_EndTime;
    };
}

// Implementations

export namespace eqx
{
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
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return static_cast<double>(getTime<std::chrono::nanoseconds>()) / 1E9;
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    [[nodiscard]] inline double StopWatch::readSeconds() noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return static_cast<double>(readTime<std::chrono::nanoseconds>()) / 1E9;
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires TimeUnit<T>
    [[nodiscard]] std::string StopWatch::toString() const
    {
        return (std::stringstream{} << getDuration<T>()).str();
    }
}
