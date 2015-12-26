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
#ifndef POLDER_ITERATOR_GET_ITERATOR_H_
#define POLDER_ITERATOR_GET_ITERATOR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstddef>
#include <utility>
#include <POLDER/details/config.h>
#include <POLDER/iterator/transform_iterator.h>

namespace polder
{
    namespace details
    {
        template<std::size_t N>
        struct getter
        {
            template<typename T>
            auto operator()(T&& arg) const
                -> decltype(std::get<N>(std::forward<T>(arg)))
            {
                return std::get<N>(std::forward<T>(arg));
            }
        };
    }

    /**
     * @brief Iterator adapter for std::get.
     *
     * Make an iterator which will get the nth
     * element of the object returned by the
     * given iterator. It allows to create iterators
     * to traverse keys of a std::map-like object
     * for example.
     *
     * Useful to iterate through some specific std::pair
     * or std::tuple elements, for example only the keys
     * or only the values of a std::map.
     */
    template<std::size_t N, typename Iterator>
    using get_iterator = transform_iterator<Iterator, details::getter<N>>;

    ////////////////////////////////////////////////////////////
    // Construction function

    template<std::size_t N, typename Iterator>
    auto make_get_iterator(Iterator it)
        -> get_iterator<N, Iterator>
    {
        return get_iterator<N, Iterator>(it);
    }
}

#endif // POLDER_ITERATOR_GET_ITERATOR_H_
