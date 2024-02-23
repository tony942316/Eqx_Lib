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

#ifndef EQUINOX_DETAILS_MISCDECL_HPP
#define EQUINOX_DETAILS_MISCDECL_HPP

#include "Dependencies.hpp"

#include "../UtilityMacros.hpp"

namespace eqx
{
    /**
     * @brief Type Accurate nullptr
     */
    template <typename T>
    inline constexpr auto nullp = static_cast<T*>(nullptr);

    /**
     * @brief Constrain T To Be A signed Integer Type, Note Unlike
     *      std::is_integeral The bool And char Types Are Not Included
     */
    template <typename T>
    concept SignedInteger =
        std::is_same_v<std::remove_cvref_t<T>, signed short> ||
        std::is_same_v<std::remove_cvref_t<T>, signed int> ||
        std::is_same_v<std::remove_cvref_t<T>, signed long> ||
        std::is_same_v<std::remove_cvref_t<T>, signed long long>;

    /**
     * @brief Constrain T To Be An unsigned Integer Type, Note Unlike
     *      std::is_integeral The bool And char Types Are Not Included
     */
    template <typename T>
    concept UnsignedInteger =
        std::is_same_v<std::remove_cvref_t<T>, unsigned short> ||
        std::is_same_v<std::remove_cvref_t<T>, unsigned int> ||
        std::is_same_v<std::remove_cvref_t<T>, unsigned long> ||
        std::is_same_v<std::remove_cvref_t<T>, unsigned long long>;

    /**
     * @brief Constrain T To Be An Integer Type, Note Unlike std::is_integeral
     *      The bool And char Types Are Not Included
     */
    template <typename T>
    concept Integer = SignedInteger<T> || UnsignedInteger<T>;

    /**
     * brief Constrain T To Be A signed Arithmetic Type, Note Unlike
     *      std::is_arithmetic The bool And char Types Are Not Included
     */
    template <typename T>
    concept SignedArithmetic = SignedInteger<T> || std::floating_point<T>;

    /**
     * brief Constrain T To Be An unsigned Arithmetic Type, Note Unlike
     *      std::is_arithmetic The bool And char Types Are Not Included
     */
    template <typename T>
    concept UnsignedArithmetic = UnsignedInteger<T> || std::floating_point<T>;

    /**
     * @brief Constrain T To Be An Arithmetic Type, Note Unlike
     *      std::is_arithmetic The bool And char Types Are Not Included
     */
    template <typename T>
    concept Arithmetic = SignedArithmetic<T> || UnsignedArithmetic<T>;

    /**
     * @brief Constrain T To Be Convertable To A String
     */
    template <typename T>
    concept Stringable = requires(const T& val)
    {
        std::to_string(val);
    };

    /**
     * @brief Constrain T To Be A String Type
     */
    template <typename T>
    concept StringType =
        std::is_same<std::remove_cvref_t<T>, std::string>::value ||
        std::is_same<std::remove_cvref_t<T>, std::wstring>::value ||
        std::is_same<std::remove_cvref_t<T>, std::u8string>::value ||
        std::is_same<std::remove_cvref_t<T>, std::u16string>::value ||
        std::is_same<std::remove_cvref_t<T>, std::u32string>::value ||
        std::is_same<std::remove_cvref_t<T>, std::string_view>::value ||
        std::is_same<std::remove_cvref_t<T>, std::wstring_view>::value ||
        std::is_same<std::remove_cvref_t<T>, std::u8string_view>::value ||
        std::is_same<std::remove_cvref_t<T>, std::u16string_view>::value ||
        std::is_same<std::remove_cvref_t<T>, std::u32string_view>::value;

    /**
     * @brief Constrain T To Be A Const Collection
     */
    template <typename T>
    concept ConstCollection = !StringType<T> &&
        requires(const T& val)
        {
            std::ranges::cbegin(val);
            std::ranges::cend(val);
            std::ranges::distance(val);
        };

    /**
     * @brief Convert A const char* To A std::string
     *
     * @param cstring Value To Be Converted
     *
     * @returns Value Converted To std::string
     */
    [[nodiscard]] inline std::string toString(const char* cstring);

    /**
     * @brief Convert A Value To A std::string
     *
     * @param val Value To Be Converted, Must Be eqx::Stringable Compliant
     *
     * @returns Value Converted To std::string
     */
    template <typename T>
        requires Stringable<T>
    [[nodiscard]] std::string toString(const T& val);

    /**
     * @brief Convert A Value To A std::string
     *
     * @param val Value To Be Converted, Must Be eqx::stringType Compliant
     *
     * @returns Value Converted To std::string
     */
    template <typename T>
        requires StringType<T>
    [[nodiscard]] std::string toString(const T& val);

    /**
     * @brief Convert A std::pair To A std::string Of Form
     *      "(p.first, p.second)"
     *
     * @param val Pair To Be Converted
     *
     * @returns Pair Converted To std::string
     */
    template <typename T, typename U>
    [[nodiscard]] std::string toString(const std::pair<T, U>& val);

    /**
     * @brief Convert A Collection To A std::string Of Form
     *      "{ val[0], val[1], val[2], ... }"
     *
     * @param val Collection To Be Converted, Must Be eqx::constCollection
     *      Compliant
     *
     * @returns Collection Converted To std::string
     */
    template <typename T>
        requires ConstCollection<T>
    [[nodiscard]] std::string toString(const T& val);

    /**
     * @brief Convert The Characters Of A String To Lower Case
     *
     * @param str String To Be Converted
     *
     * @returns std::string Which Is The Converted String
     */
    [[nodiscard]] std::string toLower(std::string_view str) noexcept;

    /**
     * @brief Parse String With A Delimiter
     *
     * @returns std::vector<std::string> Of The Seperated Messages
     */
    [[nodiscard]] inline std::vector<std::string>
        parseString(const std::string_view str, const std::string_view c);

    namespace pairPrint
    {
        /**
         * @brief Allow std::pair To Be Streamed In The Form
         *      "(p.first, p.second)"
         */
        template <typename T, typename U>
        std::ostream& operator<< (std::ostream& os, std::pair<T, U> p);
    }

    namespace literals
    {
        using namespace std::literals;

        /**
         * @brief std::size_t Literal
         */
        consteval std::size_t operator""_size (unsigned long long x) noexcept;

        /**
         * @brief short Literal
         */
        consteval short operator""_short (unsigned long long x) noexcept;

        /**
         * @brief unsigned short Literal
         */
        consteval unsigned short operator""_ushort (unsigned long long x)
            noexcept;

        /**
         * @brief 8 Byte Integer Literal
         */
        consteval std::int8_t operator""_i8 (unsigned long long x) noexcept;

        /**
         * @brief 16 Byte Integer Literal
         */
        consteval std::int16_t operator""_i16 (unsigned long long x) noexcept;

        /**
         * @brief 32 Byte Integer Literal
         */
        consteval std::int32_t operator""_i32 (unsigned long long x) noexcept;

        /**
         * @brief 64 Byte Integer Literal
         */
        consteval std::int64_t operator""_i64 (unsigned long long x) noexcept;

        /**
         * @brief 8 Byte Unsigned Integer Literal
         */
        consteval std::uint8_t operator""_u8 (unsigned long long x) noexcept;

        /**
         * @brief 16 Byte Unsigned Integer Literal
         */
        consteval std::uint16_t operator""_u16 (unsigned long long x) noexcept;

        /**
         * @brief 32 Byte Unsigned Integer Literal
         */
        consteval std::uint32_t operator""_u32 (unsigned long long x) noexcept;

        /**
         * @brief 64 Byte Unsigned Integer Literal
         */
        consteval std::uint64_t operator""_u64 (unsigned long long x) noexcept;

        /**
         * @brief KiloBytes Literal Conversion
         */
        consteval unsigned long long operator""_KB(unsigned long long x)
            noexcept;
    }

    /**
     * @brief Print A String To A Stream
     *
     * @param msg Message To Be Printed
     * @param out Stream To Print To
     */
    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
    inline void print(const T& msg, std::ostream& out = std::cout)
        noexcept;

    /**
     * @brief Print A String To A Stream With A '\n'
     *
     * @param msg Message To Be Printed
     * @param out Stream To Print To
     */
    template <typename T>
        requires requires(const T& val) { eqx::toString(val); }
    inline void println(const T& msg, std::ostream& out = std::cout)
        noexcept;

    /**
     * @brief Checks If A Boolean Expression Is True, If Not Then Print
     *      A Message To std::cerr And Call std::abort(), Note You Can
     *      Turn Off All Asserts By Defining EQX_NO_ASSERTS
     *
     * @param expr Expression To Be Checked
     * @param msg Message To Print To std::cerr
     * @param loc Location In Source Default Is Call Site
     */
    constexpr void runtimeAssert(bool expr, std::string_view msg = "",
        const std::source_location& loc = std::source_location::current())
        noexcept;

    /**
     * @brief Wrapper Function Around new
     *
     * @param args Arguments To Pass To T Constructor
     *
     * @returns T Pointer To Heap Memory
     */
    template <typename T, typename... Args>
        requires requires(Args&&... args)
            {  new T(std::forward<Args>(args)...); }
    [[nodiscard]] inline T* newAlloc(Args&&... args) noexcept;

    /**
     * @brief Wrapper Function Around delete
     *
     * @param ptr Pointer To Delete
     */
    template <typename T>
        requires requires(T* ptr) { delete ptr; }
    inline void deleteDealloc(T* ptr) noexcept;
}

#endif // EQUINOX_DETAILS_MISCDECL_HPP
