/*
 * Copyright (C) 2014-2015 Morwenn
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
#ifndef POLDER_POLYMORPHIC_VECTOR_H_
#define POLDER_POLYMORPHIC_VECTOR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iterator>
#include <memory>
#include <utility>
#include <vector>
#include <POLDER/iterator/indirect_iterator.h>

namespace polder
{
namespace polymorphic
{
    template<typename Interface, template<typename> class Adapter>
    class vector
    {
        public:

            ////////////////////////////////////////////////////////////
            // Public types

            using reference = Interface&;
            using const_reference = const Interface&;
            using pointer = Interface*;
            using const_pointer = const Interface*;

            using iterator = indirect_iterator<typename std::vector<std::unique_ptr<Interface>>::iterator>;
            using const_iterator = indirect_iterator<typename std::vector<std::unique_ptr<Interface>>::const_iterator>;
            using reverse_iterator = std::reverse_iterator<iterator>;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;

            ////////////////////////////////////////////////////////////
            // Modifying operations

            template<typename T, typename... Args>
            auto emplace_back(Args&&... args)
                -> void;

            template<typename T>
            auto push_back(T&& other)
                -> void;

            ////////////////////////////////////////////////////////////
            // Iterator operations

            auto begin()
                -> iterator;
            auto begin() const
                -> const_iterator;
            auto cbegin() const
                -> const_iterator;
            auto end()
                -> iterator;
            auto end() const
                -> const_iterator;
            auto cend() const
                -> const_iterator;

            auto rbegin()
                -> reverse_iterator;
            auto rbegin() const
                -> const_reverse_iterator;
            auto crbegin() const
                -> const_reverse_iterator;
            auto rend()
                -> reverse_iterator;
            auto rend() const
                -> const_reverse_iterator;
            auto crend() const
                -> const_reverse_iterator;

        private:

            std::vector<std::unique_ptr<Interface>> _entities;
    };

    #include "details/vector.inl"
}}

#endif // POLDER_POLYMORPHIC_VECTOR_H_
