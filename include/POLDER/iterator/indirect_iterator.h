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
#ifndef POLDER_ITERATOR_INDIRECT_ITERATOR_H_
#define POLDER_ITERATOR_INDIRECT_ITERATOR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utility>
#include <POLDER/details/config.h>
#include <POLDER/iterator/transform_iterator.h>

namespace polder
{
    namespace details
    {
        struct indirection
        {
            template<typename T>
            auto operator()(T&& arg) const
                -> decltype(auto)
            {
                return *std::forward<T>(arg);
            }
        };
    }

    /**
     * @brief Iterator adapter for indirection.
     *
     * Make an iterator meant to iterate over a
     * range of objects which can be dereferenced.
     *
     * Useful to iterate over a collection of pointers.
     */
    template<typename Iterator>
    using indirect_iterator = transform_iterator<Iterator, details::indirection>;
}

#endif // POLDER_ITERATOR_INDIRECT_ITERATOR_H_
