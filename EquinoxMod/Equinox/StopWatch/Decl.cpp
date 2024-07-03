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

export module Equinox.StopWatch:Decl;

import Eqx.Stdm;

export namespace eqx
{
    namespace TimeTypes
    {
        using t_NS = stdm::chrono::nanoseconds;
        using t_US = stdm::chrono::microseconds;
        using t_MS = stdm::chrono::milliseconds;
        using t_S = stdm::chrono::seconds;
    }

    template <typename T>
    concept TimeUnit = stdm::is_same_v<T, stdm::chrono::nanoseconds>
        || stdm::is_same_v<T, stdm::chrono::microseconds>
        || stdm::is_same_v<T, stdm::chrono::milliseconds>
        || stdm::is_same_v<T, stdm::chrono::seconds>;

    class StopWatch
    {
    public:
        /**
         * @brief Does NOT Start StopWatch On Construction
         */
        explicit consteval StopWatch() noexcept = default;

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
        template <typename T = stdm::chrono::milliseconds>
            requires TimeUnit<T>
        [[nodiscard]] T getDuration() const noexcept;

        /**
         * @brief Gives The Time Between The Last this->start Call And
         *      this->stop Call In Milliseconds (Or T If Defined)
         *
         * @returns long long Representing The Milliseconds (Or T) Past Between
         *      The Last this->start Call And this->stop Call
         */
        template <typename T = stdm::chrono::milliseconds>
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
        template <typename T = stdm::chrono::milliseconds>
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
        template <typename T = stdm::chrono::milliseconds>
            requires TimeUnit<T>
        [[nodiscard]] stdm::string toString() const;

    private:
        stdm::chrono::steady_clock::time_point m_StartTime, m_EndTime;
    };

    /**
     * @brief Gives The String Representation Of An eqx::StopWatch
     *
     * @param watch StopWatch To Process
     *
     * @returns std::string "{TimePast}ms"
     */
    template <typename T = stdm::chrono::milliseconds>
        requires TimeUnit<T>
    [[nodiscard]] stdm::string toString(const StopWatch& watch);
}
