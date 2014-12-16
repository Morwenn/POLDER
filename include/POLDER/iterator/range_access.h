/*
 * Copyright (C) 2014 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#ifndef POLDER_ITERATOR_RANGE_ACCESS_H_
#define POLDER_ITERATOR_RANGE_ACCESS_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iterator>
#include <POLDER/details/config.h>

namespace polder
{
    /**
     * @brief Global rbegin function
     *
     * The equivalent of std::begin for reversed
     * iteration.
     */
    template<typename T>
    auto rbegin(T& iterable)
        -> decltype(iterable.rbegin());
    template<typename T>
    auto rbegin(const T& iterable)
        -> decltype(iterable.crbegin());
    template<typename T, std::size_t N>
    auto rbegin(T (&array)[N])
        -> std::reverse_iterator<T*>;

    /**
     * @brief Global rend function
     *
     * The equivalent of std::end for reversed
     * iteration.
     */
    template<typename T>
    auto rend(T& iterable)
        -> decltype(iterable.rend());
    template<typename T>
    auto rend(const T& iterable)
        -> decltype(iterable.crend());
    template<typename T, std::size_t N>
    auto rend(T (&array)[N])
        -> std::reverse_iterator<T*>;

    #include "details/range_access.inl"
}

#endif // POLDER_ITERATOR_RANGE_ACCESS_H_
