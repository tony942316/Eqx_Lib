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

#ifndef EQUINOX_DETAILS_STATICVECTORDECL_HPP
#define EQUINOX_DETAILS_STATICVECTORDECL_HPP

#include "Dependencies.hpp"

#include "../Misc.hpp"

namespace eqx
{
    /**
     * @brief std::array With A Vector Like Interface
     */
    template <class t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    class StaticVector
    {
    private:
        using t_This = StaticVector<t_Held, Capacity>;
        using t_Size = std::uint8_t;
        using t_Ref = t_Held&;
        using t_CRef = const t_Held&;
        using t_Point = t_Held*;
        using t_CPoint = const t_Held*;
        using t_Iter = std::array<t_Held, Capacity>::iterator;
        using t_CIter = std::array<t_Held, Capacity>::const_iterator;
        using t_RIter = std::array<t_Held, Capacity>::reverse_iterator;
        using t_CRIter = std::array<t_Held, Capacity>::const_reverse_iterator;

    public:
        using value_type = t_Held;
        using size_type = t_Size;
        using difference_type = std::array<t_Held, Capacity>::difference_type;
        using reference = t_Ref;
        using const_reference = t_CRef;
        using pointer = t_Point;
        using const_pointer = t_CPoint;
        using iterator = t_Iter;
        using const_iterator = t_CIter;
        using reverse_iterator = t_RIter;
        using const_reverse_iterator = t_CRIter;

        /**
         * @brief Default Initialization Note Language Limitations Force
         *      O(Capacity) Default Constructions
         */
        explicit constexpr StaticVector()
            noexcept(std::is_nothrow_default_constructible_v<t_Held>);

        /**
         * @brief Initialization With N Values
         *
         * @param args Values To Initialize
         */
        template <typename... Args>
            requires std::conjunction_v<
        std::is_constructible<t_Held, Args&&>...>
        explicit constexpr StaticVector(Args&&... args)
            noexcept(std::conjunction_v<
                std::is_nothrow_default_constructible<t_Held>,
                std::is_nothrow_invocable<decltype(&t_This::push_back<Args&&>),
                    t_This, Args&&>...>);

        constexpr StaticVector(const StaticVector&) = default;
        constexpr StaticVector(StaticVector&&) = default;
        constexpr StaticVector& operator= (const StaticVector&) = default;
        constexpr StaticVector& operator= (StaticVector&&) = default;
        constexpr ~StaticVector() = default;

        /**
         * @brief Get Nth Index Value
         *
         * @param index Nth Index From 0
         *
         * @returns Reference To Nth Index
         */
        [[nodiscard]] constexpr t_Ref at(t_Size index) noexcept;

        /**
         * @brief Get Nth Index Value
         *
         * @param index Nth Index From 0
         *
         * @returns Const Reference To Nth Index
         */
        [[nodiscard]] constexpr t_CRef at(t_Size index) const noexcept;

        /**
         * @brief Get Nth Index Value
         *
         * @param index Nth Index From 0
         *
         * @returns Reference To Nth Index
         */
        [[nodiscard]] constexpr t_Ref operator[] (t_Size index) noexcept;

        /**
         * @brief Get Nth Index Value
         *
         * @param index Nth Index From 0
         *
         * @returns Const Reference To Nth Index
         */
        [[nodiscard]] constexpr t_CRef operator[] (t_Size index)
            const noexcept;

        /**
         * @brief Get First Value
         *
         * @returns Reference To First Value
         */
        [[nodiscard]] constexpr t_Ref front() noexcept;

        /**
         * @brief Get First Value
         *
         * @returns Const Reference To First Value
         */
        [[nodiscard]] constexpr t_CRef front() const noexcept;

        /**
         * @brief Get Last Value
         *
         * @returns Reference To Last Value
         */
        [[nodiscard]] constexpr t_Ref back() noexcept;

        /**
         * @brief Get Last Value
         *
         * @returns Const Reference To Last Value
         */
        [[nodiscard]] constexpr t_CRef back() const noexcept;

        /**
         * @brief Get Iterator To First Value
         *
         * @returns Iterator To First Value
         */
        [[nodiscard]] constexpr t_Iter begin() noexcept;

        /**
         * @brief Get Const Iterator To First Value
         *
         * @returns Const Iterator To First Value
         */
        [[nodiscard]] constexpr t_CIter begin() const noexcept;

        /**
         * @brief Get Const Iterator To First Value
         *
         * @returns Const Iterator To First Value
         */
        [[nodiscard]] constexpr t_CIter cbegin() const noexcept;

        /**
         * @brief Get Iterator To Last Value
         *
         * @returns Iterator To Last Value
         */
        [[nodiscard]] constexpr t_Iter end() noexcept;

        /**
         * @brief Get Const Iterator To Last Value
         *
         * @returns Const Iterator To Last Value
         */
        [[nodiscard]] constexpr t_CIter end() const noexcept;

        /**
         * @brief Get Const Iterator To Last Value
         *
         * @returns Const Iterator To Last Value
         */
        [[nodiscard]] constexpr t_CIter cend() const noexcept;

        /**
         * @brief Get Reverse Iterator To First Value
         *
         * @returns Reverse Iterator To First Value
         */
        [[nodiscard]] constexpr t_RIter rbegin() noexcept;

        /**
         * @brief Get Const Reverse Iterator To First Value
         *
         * @returns Const Reverse Iterator To First Value
         */
        [[nodiscard]] constexpr t_CRIter rbegin() const noexcept;

        /**
         * @brief Get Const Reverse Iterator To First Value
         *
         * @returns Const Reverse Iterator To First Value
         */
        [[nodiscard]] constexpr t_CRIter crbegin() const noexcept;

        /**
         * @brief Get Reverse Iterator To Last Value
         *
         * @returns Reverse Iterator To Last Value
         */
        [[nodiscard]] constexpr t_RIter rend() noexcept;

        /**
         * @brief Get Const Reverse Iterator To Last Value
         *
         * @returns Const Reverse Iterator To Last Value
         */
        [[nodiscard]] constexpr t_CRIter rend() const noexcept;

        /**
         * @brief Get Const Reverse Iterator To Last Value
         *
         * @returns Const Reverse Iterator To Last Value
         */
        [[nodiscard]] constexpr t_CRIter crend() const noexcept;

        /**
         * @brief Check If There Are Any Values
         *
         * @returns true If There Are No Values
         */
        [[nodiscard]] constexpr bool empty() const noexcept;

        /**
         * @brief Get Current Size
         *
         * @returns Current Size
         */
        [[nodiscard]] constexpr t_Size size() const noexcept;

        /**
         * @brief Get Maximun Possible Capacity
         *
         * @returns Maximun Capacity
         */
        [[nodiscard]] constexpr t_Size max_size() const noexcept;

        /**
         * @brief Get Current Capacity
         *
         * @returns Current Capacity
         */
        [[nodiscard]] constexpr t_Size capacity() const noexcept;

        /**
         * @brief Remove All Values From The Vector
         */
        constexpr void clear() noexcept(std::is_nothrow_invocable_v<
            decltype(&t_This::resize), t_This, int>);

        /**
         * @brief Push Value Onto The Back Of The Vector
         *
         * @param arg Argument To Push
         */
        template <typename Arg>
            requires std::is_constructible_v<t_Held, Arg&&>
        constexpr void push_back(Arg&& arg)
            noexcept(std::is_nothrow_invocable_v<
                decltype(&t_This::emplace_back<Arg&&>), t_This, Arg&&>);

        /**
         * @brief Emplace Value Onto The Back Of The Vector
         *
         * @param args Arguments For The Constructor
         *
         * @returns Reference To Newly Constructed Object
         */
        template <typename... Args>
            requires std::is_constructible_v<t_Held, Args&&...>
        constexpr t_Ref emplace_back(Args&&... args)
            noexcept(std::is_nothrow_constructible_v<t_Held, Args&&...>);

        /**
         * @brief Destroy And Remove Last Element
         */
        constexpr void pop_back() noexcept(std::conjunction_v<
            std::is_nothrow_default_constructible<t_Held>,
            std::is_nothrow_destructible<t_Held>>);

        /**
         * @brief Change The Size Of The Vector
         *
         * @param size New Size Of The Vector
         */
        constexpr void resize(t_Size size)
            noexcept(std::is_nothrow_invocable_v<
                decltype(&t_This::pop_back), t_This>);

    private:
        std::array<t_Held, Capacity> m_Storage;
        t_Size m_CurSize;
    };
}

#endif // EQUINOX_DETAILS_STATICVECTORDECL_HPP
