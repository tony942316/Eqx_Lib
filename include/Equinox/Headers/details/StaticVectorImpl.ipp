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

#ifndef EQUINOX_DETAILS_STATICVECTORIMPL_IPP
#define EQUINOX_DETAILS_STATICVECTORIMPL_IPP

#include "StaticVectorDecl.hpp"

namespace eqx
{
    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::StaticVector()
        noexcept(std::is_nothrow_default_constructible_v<t_Held>)
        :
        m_Storage(),
        m_CurSize(0)
    {
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    template <typename... Args>
        requires std::conjunction_v<
            std::is_constructible<t_Held, Args&&>...>
    constexpr StaticVector<t_Held, Capacity>::StaticVector(Args&&... args)
        noexcept(std::conjunction_v<
            std::is_nothrow_default_constructible<t_Held>,
            std::is_nothrow_invocable<decltype(&t_This::push_back<Args&&>),
                t_This, Args&&>...>)
        :
        StaticVector()
    {
        (push_back(std::forward<Args>(args)), ...);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_Ref
        StaticVector<t_Held, Capacity>::at(t_Size index) noexcept
    {
        runtimeAssert(index < m_CurSize, "Index Out Of Bounds");
        return m_Storage.at(index);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CRef
        StaticVector<t_Held, Capacity>::at(t_Size index) const noexcept
    {
        runtimeAssert(index < m_CurSize, "Index Out Of Bounds");
        return m_Storage.at(index);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_Ref
        StaticVector<t_Held, Capacity>::operator[] (t_Size index) noexcept
    {
        return at(index);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CRef
        StaticVector<t_Held, Capacity>::operator[] (t_Size index)
            const noexcept
    {
        return at(index);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_Ref
        StaticVector<t_Held, Capacity>::front() noexcept
    {
        return at(0);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CRef
        StaticVector<t_Held, Capacity>::front() const noexcept
    {
        return at(0);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_Ref
        StaticVector<t_Held, Capacity>::back() noexcept
    {
        return at(m_CurSize - 1);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CRef
        StaticVector<t_Held, Capacity>::back() const noexcept
    {
        return at(m_CurSize - 1);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_Iter
        StaticVector<t_Held, Capacity>::begin() noexcept
    {
        return std::ranges::begin(m_Storage);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CIter
        StaticVector<t_Held, Capacity>::begin() const noexcept
    {
        return std::ranges::begin(m_Storage);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CIter
        StaticVector<t_Held, Capacity>::cbegin() const noexcept
    {
        return begin();
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_Iter
        StaticVector<t_Held, Capacity>::end() noexcept
    {
        return std::ranges::next(begin(), m_CurSize);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CIter
        StaticVector<t_Held, Capacity>::end() const noexcept
    {
        return std::ranges::next(begin(), m_CurSize);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CIter
        StaticVector<t_Held, Capacity>::cend() const noexcept
    {
        return end();
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_RIter
        StaticVector<t_Held, Capacity>::rbegin() noexcept
    {
        return std::ranges::next(std::ranges::rbegin(m_Storage),
            Capacity - m_CurSize);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CRIter
        StaticVector<t_Held, Capacity>::rbegin() const noexcept
    {
        return std::ranges::next(std::ranges::rbegin(m_Storage),
            Capacity - m_CurSize);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CRIter
        StaticVector<t_Held, Capacity>::crbegin() const noexcept
    {
        return rbegin();
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_RIter
        StaticVector<t_Held, Capacity>::rend() noexcept
    {
        return std::ranges::next(rbegin(), m_CurSize);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CRIter
        StaticVector<t_Held, Capacity>::rend() const noexcept
    {
        return std::ranges::next(rbegin(), m_CurSize);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_CRIter
        StaticVector<t_Held, Capacity>::crend() const noexcept
    {
        return rend();
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr bool StaticVector<t_Held, Capacity>::empty() const noexcept
    {
        return m_CurSize == 0;
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_Size
        StaticVector<t_Held, Capacity>::size() const noexcept
    {
        return m_CurSize;
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_Size
        StaticVector<t_Held, Capacity>::max_size() const noexcept
    {
        return std::numeric_limits<t_Size>::max();
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr StaticVector<t_Held, Capacity>::t_Size
        StaticVector<t_Held, Capacity>::capacity() const noexcept
    {
        return Capacity;
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr void StaticVector<t_Held, Capacity>::clear()
        noexcept(std::is_nothrow_invocable_v<
            decltype(&t_This::resize), t_This, int>)
    {
        resize(0);
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    template <typename Arg>
        requires std::is_constructible_v<t_Held, Arg&&>
    constexpr void StaticVector<t_Held, Capacity>::push_back(Arg&& arg)
        noexcept(std::is_nothrow_invocable_v<
            decltype(&t_This::emplace_back<Arg&&>), t_This, Arg&&>)
    {
        emplace_back(std::forward<Arg>(arg));
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    template <typename... Args>
        requires std::is_constructible_v<t_Held, Args&&...>
    constexpr StaticVector<t_Held, Capacity>::t_Ref
        StaticVector<t_Held, Capacity>::emplace_back(Args&&... args)
            noexcept(std::is_nothrow_constructible_v<t_Held, Args&&...>)
    {
        runtimeAssert(m_CurSize < Capacity, "Vector Is Full");
        m_CurSize++;
        if constexpr (!std::is_trivially_destructible_v<t_Held>)
        {
            std::destroy_at(&back());
        }
        return *(std::construct_at(&back(), std::forward<Args>(args)...));
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr void StaticVector<t_Held, Capacity>::pop_back()
        noexcept(std::conjunction_v<
            std::is_nothrow_default_constructible<t_Held>,
            std::is_nothrow_destructible<t_Held>>)
    {
        runtimeAssert(m_CurSize > 0, "Can't pop_back From Empty Vector");
        if constexpr (!std::is_trivially_destructible_v<t_Held>)
        {
            std::destroy_at(&back());
        }
        std::construct_at(&back());
        m_CurSize--;
    }

    template <typename t_Held, std::uint8_t Capacity>
        requires std::is_default_constructible_v<t_Held>
    constexpr void StaticVector<t_Held, Capacity>::resize(t_Size size)
        noexcept(std::is_nothrow_invocable_v<
            decltype(&t_This::pop_back), t_This>)
    {
        runtimeAssert(size <= Capacity, "Bad Resize");
        while (m_CurSize > size)
        {
            pop_back();
        }
        m_CurSize = size;
    }
}

#endif // EQUINOX_DETAILS_STATICVECTORIMPL_IPP
