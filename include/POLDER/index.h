/*
 * Copyright (C) 2011-2013 Morwenn
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
#ifndef _POLDER_INDEX_H
#define _POLDER_INDEX_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/config.h>

namespace polder
{
    /**
     * @brief Multi-dimensional index
     *
     * Index to use with multi-dimensional containers.
     * For a 3-dimensional array for example, you should
     * override operator[] so that it takes a index<3>.
     * That way, you will be able to write code like:
     *
     * array<3, 3, 3> arr = { ... };
     * std::cout << arr[{0, 2, 1}] << std::endl;
     */
    template<std::size_t N>
    class index
    {
        public:

            index();
            index(const index<N>& other);
            index(index<N>&& other);

            template<typename... Args>
            index(Args... indices);

            auto operator=(const index<N>& other)
                -> index<N>&;
            auto operator=(index<N>&& other)
                -> index<N>&;

            auto operator[](std::size_t ind) const
                -> std::size_t;

        private:

            template<typename... Args>
            auto _build(std::size_t head, Args... tail)
                -> void;
            auto _build(std::size_t head)
                -> void;

            // Member indices
            std::size_t _indices[N];
    };

    template<std::size_t N>
    auto operator==(const index<N>& lhs, const index<N>& rhs)
        -> bool;
    template<std::size_t N>
    auto operator!=(const index<N>& lhs, const index<N>& rhs)
        -> bool;

    #include "index.inl"
}

#endif // _POLDER_INDEX_H
