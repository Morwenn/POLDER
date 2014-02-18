/*
 * Copyright (C) 2011-2014 Morwenn
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
#ifndef _POLDER_GEOMETRY_VECTOR_BASE_H
#define _POLDER_GEOMETRY_VECTOR_BASE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>
#include <POLDER/algorithm.h>
#include <POLDER/math/norm.h>
#include <POLDER/geometry/details/types.h>


namespace polder
{
namespace geometry
{
    template<std::size_t N, typename T>
    class ImmutableVectorBase
    {
        public:

            ////////////////////////////////////////////////////////////
            // Types
            ////////////////////////////////////////////////////////////

            // Value
            using value_type = T;
            using const_reference = const value_type&;
            using const_pointer = const value_type*;

            // Iterators
            using const_iterator = typename std::array<T, N>::const_iterator;

            ////////////////////////////////////////////////////////////
            // Operators
            ////////////////////////////////////////////////////////////

            // Accessors
            auto operator[](std::size_t index) const
                -> const_reference;

            ////////////////////////////////////////////////////////////
            // Coordinates aliases
            ////////////////////////////////////////////////////////////

            auto x() const
                -> const_reference;
            auto y() const
                -> const_reference;
            auto z() const
                -> const_reference;

            ////////////////////////////////////////////////////////////
            // Vector iterators
            ////////////////////////////////////////////////////////////

            auto begin() const
                -> const_iterator;
            auto cbegin() const
                -> const_iterator;
            auto end() const
                -> const_iterator;
            auto cend() const
                -> const_iterator;

        protected:

            template<typename First, typename... Args>
            auto construct(First first, Args... args)
                -> void;
            template<typename First>
            auto construct(First first)
                -> void;

            std::array<T, N> coordinates;    /**< Coordinates */
    };

    template<std::size_t N, typename T>
    class MutableVectorBase:
        public ImmutableVectorBase<N, T>
    {
        public:

            ////////////////////////////////////////////////////////////
            // Types
            ////////////////////////////////////////////////////////////

            using super = ImmutableVectorBase<N, T>;

            // Value
            using typename super::value_type;
            using reference = value_type&;
            using typename super::const_reference;
            using pointer = value_type*;
            using typename super::const_pointer;

            // Iterators
            using iterator = typename std::array<T, N>::iterator;
            using typename super::const_iterator;

            ////////////////////////////////////////////////////////////
            // Operators
            ////////////////////////////////////////////////////////////

            // Accessors
            using super::operator[];
            auto operator[](std::size_t index)
                -> reference;

            ////////////////////////////////////////////////////////////
            // Coordinates aliases
            ////////////////////////////////////////////////////////////

            using super::x;
            using super::y;
            using super::z;
            auto x()
                -> reference;
            auto y()
                -> reference;
            auto z()
                -> reference;

            ////////////////////////////////////////////////////////////
            // Vector iterators
            ////////////////////////////////////////////////////////////

            using super::begin;
            using super::end;
            auto begin()
                -> iterator;
            auto end()
                -> iterator;

            // Member data
            using super::coordinates;
    };

    #include "vector_base.inl"
}}

#endif // _POLDER_GEOMETRY_VECTOR_BASE_H
