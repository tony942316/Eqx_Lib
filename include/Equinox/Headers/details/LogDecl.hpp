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

#ifndef EQUINOX_DETAILS_LOGDECL_HPP
#define EQUINOX_DETAILS_LOGDECL_HPP

#include "Dependencies.hpp"

#include "../SuperEnum.hpp"
#include "../Misc.hpp"

namespace eqx
{
    /**
     * @brief Logs Errors And Warnings To A Stream And A File
     */
    class Log
    {
    public:
        /**
         * Pure Static Class Is Not Meant To Be Constructed Or Copied
         */
        Log() = delete;
        Log(const Log&) = delete;
        Log(Log&&) = delete;
        Log& operator= (const Log&) = delete;
        Log& operator= (Log&&) = delete;
        ~Log() = delete;

        /**
         * @brief Severity Of A Log
         */
        EQX_SUPER_ENUM(Level,
            All,
            Info,
            Warning,
            Error,
            None );

        /**
         * @brief Type Of A Log
         */
        EQX_SUPER_ENUM(Type,
            None,
            Info,
            RuntimeWarning,
            RuntimeError,
            OverflowError,
            UnreachableCodeError );

        /**
         * @brief Activate The Logger
         *
         * @param outStream Stream To Write Logs To
         * @param outFile File Name To Write Logs To
         */
        static inline void init(std::ostream* outStream = &std::clog,
            std::string_view outFile = "Log.txt");

        /**
         * @brief Check If init Has Been Called
         */
        [[nodiscard]] static inline bool isInit() noexcept;

        /**
         * @brief Log A Message To The Active Stream And File
         *
         * @param level Level Of The Log
         * @param msg Message Of The Log
         * @param type Type Of The Log
         * @param loc Current Location In Source
         */
        static inline void log(Level level, std::string_view msg,
            Type type = Type::None,
            const std::source_location& loc = std::source_location::current());

        /**
         * @brief Set Level Of Logs To Be Output i.e.
         *      warning Will Output warnings And errors But Not info
         *
         * @param level Cutoff i.e. all -> info -> warning -> error -> none
         */
        static inline void setLevel(Level level) noexcept;

        /**
         * @brief Set The Stream Logs Are Written To
         *
         * @param stream The New Output Stream
         */
        static inline void setOutputStream(std::ostream* stream) noexcept;

        /**
         * @brief Set The File Logs Are Written To
         *
         * @param file The Path Of The New File
         */
        static inline void setOutputFile(std::string_view file);

        /**
         * @brief Clears The Last Error Message And Type
         */
        static inline void clear() noexcept;

        /**
         * @brief Get Current Log Level
         *
         * @returns Current Log Level
         */
        [[nodiscard]] static inline Level getCurrentLogLevel() noexcept;

        /**
         * @brief Get Type Of Last Log
         *
         * @returns Last Log Type
         */
        [[nodiscard]] static inline Type getLastLogType() noexcept;

        /**
         * @brief Get Message Of Last Log
         *
         * @returns Last Message String
         */
        [[nodiscard]] static inline std::string_view
            getLastLogMessage() noexcept;

        /**
         * @brief Build String With eqx::Log Formatting i.e.
         *      "{SourceLocation}[{Log::Level}]: {Message}"
         *
         * @param loc Location Of The Log
         * @param level Level Of The Log
         * @param msg Message Of The Log
         *
         * @returns Formatted String
         */
        [[nodiscard]] static inline std::string
            getFormattedString(const std::source_location& loc, Level level,
            std::string_view msg = "");

        /**
         * @brief Get Log Levels That Log Properly i.e.
         *      eqx::Log::all Is Not Meant To Be Logged
         *
         * @returns std::vector Of Loggable Levels
         */
        [[nodiscard]] static constexpr std::array<Log::Level, 3ULL>
            getLoggableLevels() noexcept;

    private:
        constinit static inline auto s_OutputStream = nullp<std::ostream>;
        constinit static inline auto s_LogFile = nullp<std::ofstream>;
        constinit static inline auto s_LogLevel = Level::None;
        constinit static inline auto s_LastErrorType = Type::None;
        constinit static inline auto s_LastMessage = nullp<std::string>;
        constinit static inline auto s_IsInit = false;
    };
}

#endif // EQUINOX_DETAILS_LOGDECL_HPP
