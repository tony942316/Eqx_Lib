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

#ifndef EQUINOX_SUPERENUM_HPP
#define EQUINOX_SUPERENUM_HPP

#include "details/Dependencies.hpp"

#include "UtilityMacros.hpp"

template <typename T>
    requires std::is_enum_v<T>
struct EnumPair
{
    consteval EnumPair() noexcept
        :
        m_Enum(static_cast<T>(0ULL)),
        m_String("")
    {
    }

    consteval EnumPair(T e, std::string_view s) noexcept
        :
        m_Enum(e),
        m_String(s)
    {
    }

    T m_Enum;
    std::string_view m_String;
};

namespace eqx
{
    /**
     * @brief Function For Use By EQX_SUPER_ENUM, NOT FOR EXTERNAL USE!
     */
    template <std::size_t N, typename EnumType, typename... Types>
    consteval std::array<EnumPair<EnumType>, N> P_makeArr(Types... args)
    {
        std::array<EnumPair<EnumType>, N> arr;
        std::array<std::string_view, N> arr2 = { args... };

        for (std::size_t i = 0ULL; i < arr.size(); i++)
        {
            arr.at(i).m_Enum = static_cast<EnumType>(i);
            arr.at(i).m_String = arr2.at(i);
        }

        return arr;
    }
}

template <typename T>
    requires std::is_enum_v<T>
constexpr bool operator== (EnumPair<T> lhs, EnumPair<T> rhs)
{
    return lhs.m_Enum == rhs.m_Enum;
}

template <typename T>
    requires std::is_enum_v<T>
constexpr bool operator!= (EnumPair<T> lhs, EnumPair<T> rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_SUPER_ENUM_TO_STRING(name) \
    [[nodiscard]] static constexpr \
        std::string_view name##ToString(name value) noexcept \
    { return name##Collection.at(static_cast<std::size_t>(value)).m_String; }

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_SUPER_ENUM_GET_ENUMS(name) \
    [[nodiscard]] static consteval \
        std::array<name, name##Collection.size()> get##name##Enums() \
    { \
        auto result = std::array<name, name##Collection.size()>(); \
        for (std::size_t i = 0ULL; i < name##Collection.size(); i++) \
        { \
            result.at(i) = name##Collection.at(i).m_Enum; \
        } \
        return result; \
    }

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_SUPER_ENUM_GET_STRINGS(name)\
    [[nodiscard]] static consteval \
        std::array<std::string_view, name##Collection.size()> \
        get##name##Strings() \
    { \
        auto result = \
            std::array<std::string_view, name##Collection.size()>(); \
        for (std::size_t i = 0ULL; i < name##Collection.size(); i++) \
        { \
            result.at(i) = name##Collection.at(i).m_String; \
        } \
        return result; \
    }

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_SUPER_ENUM_OSTREAM(name) \
    friend std::ostream& operator<< (std::ostream& oStream, name val) \
    { \
        oStream << name##ToString(val); \
        return oStream; \
    }

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_SUPER_ENUM_FULL_IMPLEMENTATION(name) \
    P_EQX_SUPER_ENUM_TO_STRING(name) \
    P_EQX_SUPER_ENUM_GET_ENUMS(name) \
    P_EQX_SUPER_ENUM_GET_STRINGS(name) \
    P_EQX_SUPER_ENUM_OSTREAM(name)

/**
 * @brief Create An enum class With Provided Values And A
 *      std::array<EnumPair, sizeof...(...)> name##Collection For Value
 *      And std::string_view Access, Also Provides consteval Functions
 *      To Convert Enum Values To String, Get A Collection Of All Enum Values,
 *      Get A Collection Of All Enum std::string_view, And Overloads
 *      operator<< To Allow Streaming Of Enums. The Functions Are
 *      Respectivly As Follows:
 *
 * @brief name##ToString(name val);
 * @brief get##name##Enums();
 * @brief get##name##Strings();
 * @brief friend std::ostream& operator<< (std::ostream& oStream, name val);
 *
 * @brief The EQX_SUPER_ENUM(name, ...) Macro Should Be Placed In A Class
 *      As Such
 *
 * @brief class SomeClass
 * @brief {
 * @brief public:
 * @brief       class declartions/implementations...
 * @brief       EQX_SUPER_ENUM(EnumName, Val1, Val2, etc...)
 * @brief       class declartions/implementations...
 * @brief private:
 * @brief       class declartions/implementations...
 * @brief       EQX_SUPER_ENUM(PrivateEnumName, Val1, Val2, etc...)
 * @brief       class declartions/implementations...
 * @brief };
 *
 *
 * @param name The Name Of The enum class
 * @param ... The Values Of The enum class
 *
 * @returns An enum class Of std::size_t With All The Provided Values, Aswell
 *      As A std::array<EnumPair, sizeof...(...)> Called name##Collection,
 *      The Array Provides The Values Of The Enum With A std::string_view
 *      Of The Enum Value
 */
#define EQX_SUPER_ENUM(name, ...) \
    enum class name : std::size_t \
        { __VA_ARGS__ }; \
    constexpr static inline auto name##Collection = \
        eqx::P_makeArr<EQX_COUNT_ARGS(__VA_ARGS__), name> \
        (EQX_STRING_ARGS(__VA_ARGS__)); \
    P_EQX_SUPER_ENUM_FULL_IMPLEMENTATION(name)

#endif // EQUINOX_SUPERENUM_HPP
