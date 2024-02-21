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

#ifndef EQUINOX_DETAILS_UNIQUERESOURCEIMPL_IPP
#define EQUINOX_DETAILS_UNIQUERESOURCEIMPL_IPP

#include "UniqueResourceDecl.hpp"

namespace eqx
{
    template <class t_Resource, class t_Destructor>
    consteval
        UniqueResource<t_Resource, t_Destructor>::UniqueResource() noexcept
        :
        m_Init(false),
        m_Resource(),
        m_Destructor()
    {
    }

    template <class t_Resource, class t_Destructor>
    template <typename t_Constructor, typename... t_Args>
    constexpr
        UniqueResource<t_Resource, t_Destructor>::UniqueResource(
            t_Destructor&& destructor,
            const t_Constructor& constructor,
            t_Args&&... args) noexcept
        :
        m_Init(false),
        m_Resource(),
        m_Destructor()
    {
        init(std::forward<t_Destructor>(destructor), constructor,
            std::forward<t_Args>(args)...);
    }

    template <class t_Resource, class t_Destructor>
    template <typename... t_Args>
    constexpr UniqueResource<t_Resource, t_Destructor>::UniqueResource(
        t_Args&&... args) noexcept
    {
        init(std::forward<t_Args>(args)...);
    }

    template <class t_Resource, class t_Destructor>
    constexpr UniqueResource<t_Resource, t_Destructor>::UniqueResource(
        UniqueResource&& other) noexcept
        :
        m_Init(false),
        m_Resource(),
        m_Destructor()
    {
        swap(other);
    }

    template <class t_Resource, class t_Destructor>
    constexpr UniqueResource<t_Resource, t_Destructor>&
        UniqueResource<t_Resource, t_Destructor>::operator= (
            UniqueResource&& other) noexcept
    {
        eqx::runtimeAssert(this != &other,
            "UniqueResource::operator= (&&) this == &other !!!");

        swap(other);
        return *this;
    }

    template <class t_Resource, class t_Destructor>
    constexpr
        UniqueResource<t_Resource, t_Destructor>::~UniqueResource() noexcept
    {
        if (m_Init == true)
        {
            free();
        }
    }

    template <class t_Resource, class t_Destructor>
    [[nodiscard]] constexpr std::remove_pointer_t<t_Resource>&
        UniqueResource<t_Resource, t_Destructor>::operator* () noexcept
    {
        if constexpr (std::is_pointer_v<t_Resource>)
        {
            eqx::runtimeAssert(m_Resource != nullptr, "nullptr Dereference!");
            return *m_Resource;
        }
        else
        {
            return get();
        }
    }

    template <class t_Resource, class t_Destructor>
    [[nodiscard]] constexpr const std::remove_pointer_t<t_Resource>&
        UniqueResource<t_Resource, t_Destructor>::operator* () const noexcept
    {
        if constexpr (std::is_pointer_v<t_Resource>)
        {
            eqx::runtimeAssert(m_Resource != nullptr, "nullptr Dereference!");
            return *m_Resource;
        }
        else
        {
            return get();
        }
    }

    template <class t_Resource, class t_Destructor>
    [[nodiscard]] constexpr t_Resource
        UniqueResource<t_Resource, t_Destructor>::operator-> () noexcept
    {
        return get();
    }

    template <class t_Resource, class t_Destructor>
    [[nodiscard]] constexpr const t_Resource
        UniqueResource<t_Resource, t_Destructor>::operator-> () const noexcept
    {
        return get();
    }

    template <class t_Resource, class t_Destructor>
    template <typename t_Constructor, typename... t_Args>
    constexpr void UniqueResource<t_Resource, t_Destructor>::init(
        t_Destructor&& destructor,
        const t_Constructor& constructor,
        t_Args&&... args) noexcept
    {
        if (m_Init == true)
        {
            free();
        }

        m_Init = true;
        m_Resource = std::invoke(constructor, std::forward<t_Args>(args)...);
        m_Destructor = std::forward<t_Destructor>(destructor);
    }

    template <class t_Resource, class t_Destructor>
    template <typename... t_Args>
    constexpr void UniqueResource<t_Resource, t_Destructor>::init(
        t_Args&&... args) noexcept
    {
        init(deleteDealloc<std::remove_pointer_t<t_Resource>>,
            newAlloc<std::remove_pointer_t<t_Resource>, t_Args...>,
            std::forward<t_Args>(args)...);
    }

    template <class t_Resource, class t_Destructor>
    constexpr void UniqueResource<t_Resource, t_Destructor>::free() noexcept
    {
        eqx::runtimeAssert(m_Init, "Init Never Called!");
        std::invoke(m_Destructor, m_Resource);

        m_Init = false;
        m_Resource = t_Resource();
    }

    template <class t_Resource, class t_Destructor>
    constexpr void UniqueResource<t_Resource, t_Destructor>::swap(
        UniqueResource& other) noexcept
    {
        std::swap(m_Init, other.m_Init);
        std::swap(m_Resource, other.m_Resource);
        std::swap(m_Destructor, other.m_Destructor);
    }

    template <class t_Resource, class t_Destructor>
    [[nodiscard]] constexpr t_Resource&
        UniqueResource<t_Resource, t_Destructor>::get() noexcept
    {
        return m_Resource;
    }

    template <class t_Resource, class t_Destructor>
    [[nodiscard]] constexpr const t_Resource&
        UniqueResource<t_Resource, t_Destructor>::get() const noexcept
    {
        return m_Resource;
    }
}

#endif // EQUINOX_DETAILS_UNIQUERESOURCEIMPL_IPP
