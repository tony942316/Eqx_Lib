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

#ifndef EQUINOX_DETAILS_UNIQUERESOURCEDECL_HPP
#define EQUINOX_DETAILS_UNIQUERESOURCEDECL_HPP

#include "Dependencies.hpp"

#include "../Misc.hpp"

namespace eqx
{
    /**
     * @brief Scoped Resource Management
     */
    template <class t_Resource,
        class t_Destructor = decltype(&deleteDealloc<std::remove_pointer_t<t_Resource>>)>
    class UniqueResource
    {
    public:
        /**
         * @brief Default Initialization
         */
        explicit constexpr UniqueResource() noexcept;

        /**
         * @brief Initialize With Constructor And Arguments
         *
         * @param destructor Function Called To Deallocate Resource
         * @param constructor Function Called To Allocate Resource
         * @param args Arguments To Forward To constructor
         */
        template <typename t_Constructor, typename... t_Args>
        explicit constexpr UniqueResource(t_Destructor&& destructor,
            const t_Constructor& constructor,
            t_Args&&... args) noexcept;

        /**
         * @brief Initialize With new And Arguments
         *
         * @param args Arguments To Forward To new
         */
        template <typename... t_Args>
        explicit constexpr UniqueResource(t_Args&&... args) noexcept;

        /**
         * @brief Move Construction Performs A Swap
         *
         * @param other UniqueResource To Move From
         */
        constexpr UniqueResource(UniqueResource&& other) noexcept;

        /**
         * @brief Move Assignment Performs A Swap
         *
         * @param other UniqueResource To Move From
         */
        constexpr UniqueResource& operator= (UniqueResource&& other) noexcept;

        /**
         * @brief Deallocate Resource
         */
        constexpr ~UniqueResource() noexcept;

        /**
         * @brief Move Only Type
         */
        UniqueResource(const UniqueResource&) = delete;
        UniqueResource& operator= (const UniqueResource&) = delete;

        /**
         * @brief Allocate Resource With Constructor And Arguments
         *
         * @param destructor Function Called To Deallocate Resource
         * @param constructor Function Called To Allocate Resource
         * @param args Arguments To Forward To constructor
         */
        template <typename t_Constructor, typename... t_Args>
        constexpr void init(t_Destructor&& destructor, const t_Constructor& constructor,
            t_Args&&... args) noexcept;

        /**
         * @brief Allocate Resource With new And Arguments
         *
         * @param args Arguments To Forward To new
         */
        template <typename... t_Args>
        constexpr void init(t_Args&&... args) noexcept;

        /**
         * @brief Deallocate Resource
         */
        constexpr void free() noexcept;

        /**
         * @brief Swap Resources
         *
         * @param other UniqueResource To Swap With
         */
        constexpr void swap(UniqueResource& other) noexcept;

        /**
         * @brief Get Underlying Resource
         *
         * @returns Reference To Resource
         */
        constexpr t_Resource& get() noexcept;

        /**
         * @brief Get Underlying Resource
         *
         * @returns Const Reference To Resource
         */
        constexpr const t_Resource& get() const noexcept;

    private:
        bool m_Init;

        t_Resource m_Resource;
        t_Destructor m_Destructor;
    };

    /**
     * @brief Alias For Default UniqueResource Which Wraps new And delete
     */
    template <typename T>
    using UniquePointer = UniqueResource<T*>;
}

#endif // EQUINOX_DETAILS_UNIQUERESOURCEDECL_HPP
