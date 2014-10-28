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
#ifndef POLDER_RECURSION_ARRAY_H_
#define POLDER_RECURSION_ARRAY_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <initializer_list>
#include <vector>
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
    class recursion_array
    {
        public:

            using value_type = typename types_t<Derived>::value_type;

            // A recursion_array is not copyable
            recursion_array(const recursion_array&) = delete;
            recursion_array& operator=(const recursion_array&) = delete;

            /**
             * @brief Calls "function" and applies memoization
             * @see value_type self(std::size_t n)
             */
            auto operator()(std::size_t n)
                -> value_type;

        protected:

            recursion_array() = default;

            /**
             * @brief Initializer-list constructor
             *
             * This should be the one and only way to instance a
             * recursion_array.
             *
             * @param vals Results of "function" for the first values
             */
            constexpr recursion_array(std::initializer_list<value_type> vals);

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
             * This is the core of the class. A recursion_array is just
             * meant to store the results of "function" are reuse them
             * instead of computing them another time. That is why a
             * recursion_array function can only accept unsigned integers
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

    #include "details/recursion_array.inl"
}

#endif // POLDER_RECURSION_ARRAY_H_
