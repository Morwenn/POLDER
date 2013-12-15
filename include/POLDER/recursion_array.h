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
#ifndef _POLDER_RECURSION_ARRAY_H
#define _POLDER_RECURSION_ARRAY_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <initializer_list>
#include <vector>
#include <POLDER/config.h>
#include <POLDER/utility.h>

namespace polder
{
    /**
     * @brief Recursion array
     *
     * A generic wrapper to apply memoization
     * principles to some embedded recursive
     * functions. It only allows to create
     * index-based functions where the index
     * is an unsigned int.
     */
    template<typename Derived>
    class RecursionArray
    {
        public:

            using value_type = typename types_t<Derived>::value_type;

            // A RecursionArray is not copyable
            RecursionArray(const RecursionArray&) = delete;
            RecursionArray& operator=(const RecursionArray&) = delete;

            /**
             * @brief Calls "function" and applies memoization
             * @see value_type self(std::size_t n)
             */
            auto operator()(std::size_t n)
                -> value_type;

        protected:

            RecursionArray() = default;

            /**
             * @brief Initializer-list constructor
             *
             * This should be the one and only way to instance a
             * RecursionArray.
             *
             * @param vals Results of "function" for the first values
             */
            constexpr RecursionArray(std::initializer_list<value_type> vals);

            /**
             * @brief Calls "function" and applies memoization
             *
             * @param n Index of the value to [compute, memoize and] return
             * @return Value of "function" for n
             */
            auto self(std::size_t n)
                -> value_type;

            /**
             * @brief Returns the number of computed elements
             * @return Number of computed elements in the vector
             */
            constexpr auto size() const
                -> std::size_t;

            /**
             * @brief User-defined function whose results are stored
             *
             * This is the core of the class. A RecursionArray is just
             * meant to store the results of "function" are reuse them
             * instead of computing them another time. That is why a
             * RecursionArray function can only accept unsigned integers
             * as parameters.
             *
             * @param n Index of the element
             * @return See user-defined function
             */
            auto function(std::size_t n)
                -> value_type;

        private:

            std::vector<value_type> _values;  /**< Computed results of "function" */
    };

    #include "recursion_array.inl"
}

#endif // _POLDER_RECURSION_ARRAY_H
