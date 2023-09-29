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

namespace eqx
{
    class SuperEnum
    {
    public:
        SuperEnum() = delete;
        SuperEnum(const SuperEnum&) = delete;
        SuperEnum(SuperEnum&&) = delete;
        SuperEnum& operator= (const SuperEnum&) = delete;
        SuperEnum& operator= (SuperEnum&&) = delete;
        ~SuperEnum() = delete;

        template <std::size_t N, typename EnumType, typename... Types>
        [[nodiscard]] static consteval
            std::array<std::pair<EnumType, std::string_view>, N>
            makeArr(Types... args) noexcept;
    private:
    };
}

namespace eqx
{
    template <std::size_t N, typename EnumType, typename... Types>
    [[nodiscard]] consteval
        std::array<std::pair<EnumType, std::string_view>, N>
        SuperEnum::makeArr(Types... args) noexcept
    {
        auto result = std::array<std::pair<EnumType, std::string_view>, N>();
        auto strs = std::array<std::string_view, N>({ args... });

        std::ranges::for_each(std::views::iota(0, static_cast<int>(N)),
            [&result, &strs](int index)
            {
                result.at(static_cast<std::size_t>(index)) = std::make_pair(
                    static_cast<EnumType>(index),
                    strs.at(static_cast<std::size_t>(index)));
            });

        return result;
    }
}

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_SUPER_ENUM_TO_STRING(name) \
    [[nodiscard]] static constexpr \
        std::string_view name##ToString(name value) noexcept \
    { \
        return p_##name##Collection.at( \
            static_cast<std::size_t>(value)).second; \
    }

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_SUPER_ENUM_GET_ENUMS(name) \
    [[nodiscard]] static consteval \
        std::array<name, std::ranges::size(p_##name##Collection)> \
        get##name##Enums() noexcept \
    { \
        auto result = \
            std::array<name, std::ranges::size(p_##name##Collection)>(); \
        std::ranges::transform(p_##name##Collection, \
            std::ranges::begin(result), \
            [](const std::pair<name, std::string_view>& val) \
            { \
                return val.first; \
            }); \
        return result; \
    }

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_SUPER_ENUM_GET_STRINGS(name) \
    [[nodiscard]] static consteval \
        std::array<std::string_view, std::ranges::size(p_##name##Collection)> \
        get##name##Strings() noexcept \
    { \
        auto result = \
            std::array<std::string_view, \
            std::ranges::size(p_##name##Collection)>(); \
        std::ranges::transform(p_##name##Collection, \
            std::ranges::begin(result), \
            [](const std::pair<name, std::string_view>& val) \
            { \
                return val.second; \
            }); \
        return result; \
    }

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_CLASS_SUPER_ENUM_OSTREAM(name) \
    inline friend std::ostream& \
        operator<< (std::ostream& oStream, name val) noexcept \
    { \
        oStream << name##ToString(val); \
        return oStream; \
    }

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_SUPER_ENUM_OSTREAM(name) \
    inline std::ostream& operator<< (std::ostream& oStream, name val) noexcept \
    { \
        oStream << name##ToString(val); \
        return oStream; \
    }

/**
 * @brief Macro For Use By Other Macros In The SuperEnum Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_CLASS_SUPER_ENUM_FULL_IMPLEMENTATION(name) \
    P_EQX_SUPER_ENUM_TO_STRING(name) \
    P_EQX_SUPER_ENUM_GET_ENUMS(name) \
    P_EQX_SUPER_ENUM_GET_STRINGS(name) \
    P_EQX_CLASS_SUPER_ENUM_OSTREAM(name)

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
 *
 */
#define EQX_CLASS_SUPER_ENUM(name, ...) \
    enum class name : std::size_t \
        { __VA_ARGS__ }; \
    static inline constexpr auto p_##name##Collection = \
        eqx::SuperEnum::makeArr<EQX_COUNT_ARGS(__VA_ARGS__), name> \
        (EQX_STRING_ARGS(__VA_ARGS__)); \
    P_EQX_CLASS_SUPER_ENUM_FULL_IMPLEMENTATION(name)

/**
 *
 */
#define EQX_SUPER_ENUM(name, ...) \
    enum class name : std::size_t \
        { __VA_ARGS__ }; \
    inline constexpr auto p_##name##Collection = \
        eqx::SuperEnum::makeArr<EQX_COUNT_ARGS(__VA_ARGS__), name> \
        (EQX_STRING_ARGS(__VA_ARGS__)); \
    P_EQX_SUPER_ENUM_FULL_IMPLEMENTATION(name)

#endif // EQUINOX_SUPERENUM_HPP
