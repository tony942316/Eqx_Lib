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

#ifndef EQUINOX_DETAILS_STOPWATCHDECL_HPP
#define EQUINOX_DETAILS_STOPWATCHDECL_HPP

#include "Dependencies.hpp"

namespace eqx
{
    namespace TimeTypes
    {
        using t_NS = std::chrono::nanoseconds;
        using t_US = std::chrono::microseconds;
        using t_MS = std::chrono::milliseconds;
        using t_S = std::chrono::seconds;
    }

    template <typename T>
    concept TimeUnit = std::is_same_v<T, std::chrono::nanoseconds> ||
        std::is_same_v<T, std::chrono::microseconds> ||
        std::is_same_v<T, std::chrono::milliseconds> ||
        std::is_same_v<T, std::chrono::seconds>;

    class StopWatch
    {
    public:
        /**
         * @brief Starts StopWatch On Construction
         */
        explicit inline StopWatch() noexcept;

        /**
         * Trivial Move And Copy Operation
         */
        StopWatch(const StopWatch&) = default;
        StopWatch(StopWatch&&) = default;
        StopWatch& operator= (const StopWatch&) = default;
        StopWatch& operator= (StopWatch&&) = default;
        ~StopWatch() = default;

        /**
         * @brief Set The Start Time Of The StopWatch And Reset The End Time
         */
        inline void start() noexcept;

        /**
         * @brief Set The End Time Of The StopWatch
         */
        inline void stop() noexcept;

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
        [[nodiscard]] inline double getSeconds() const noexcept;

        /**
         * @brief Calls this->stop Then 
         *      Gives Time Past In Seconds With Fine Precision
         *
         * @returns double 1500 Milliseconds Would Be 1.5 Seconds
         */
        [[nodiscard]] inline double readSeconds() noexcept;

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


    /**
     * @brief Gives The String Representation Of An eqx::StopWatch
     *
     * @param watch StopWatch To Process
     *
     * @returns std::string "{TimePast}ms"
     */
    template <typename T = std::chrono::milliseconds>
        requires TimeUnit<T>
    [[nodiscard]] std::string toString(const StopWatch& watch);
}

#endif // EQUINOX_DETAILS_STOPWATCHDECL_HPP
