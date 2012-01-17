/*
 * Copyright (C) 2011 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _POLDER_RECURSION_ARRAY_H
#define _POLDER_RECURSION_ARRAY_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <cassert>
#include <initializer_list>
#include <stdexcept>
#include <vector>


namespace polder
{


/**
 * @brief Recursion array
 *
 * Some wrapper to apply memoization principles
 * to some embedded recursive functions.
 *
 * I recommand you see the examples for a better
 * understanding.
 */
template<typename T>
class RecursionArray
{

    public:

        /**
         * An empty RecursionArray can not be instantiated
         */
        RecursionArray() = delete;

        /**
         * A RecursionArray is not copiable
         */
        RecursionArray(const RecursionArray&) = delete;
        RecursionArray& operator=(const RecursionArray&) = delete;

        /**
         * @brief Calls "function" and applies memoization
         * @see T self(size_t n)
         */
        inline T operator()(size_t n)
        {
            return self(n);
        }

    protected:

        /**
         * @brief Initializer-list constructor
         *
         * This should be the one and only way to instance a
         * RecursionArray.
         *
         * @param vals Results of "function" for the first values
         */
        RecursionArray(const std::initializer_list<T>& vals)
        {
            for (const T& value: vals)
            {
                values.push_back(value);
            }
        }

        /**
         * @brief Calls "function" and applies memoization
         *
         * @param n Index of the value to [compute, memoize and] return
         * @return Value of "function" for n
         */
        T self(size_t n)
        {
            if (n < 0)
            {
                throw std::out_of_range("RecursionArray can only store results for positive integers.");
            }
            while (values.size() <= n)
            {
                // Compute and add the values to the vector
                values.push_back(function(values.size()));
            }
            return values[n];
        }

        /**
         * @brief Returns the number of computed elements
         * @return Number of computed elements in the vector
         */
        constexpr inline size_t size() const
        {
            return values.size();
        }

        /**
         * @brief User-defined function whose results are stored
         *
         * This is the core of the class. A RecuresionArray is just
         * meant to store the results of "function" are reuse them
         * instead of computing them another time. That is why a
         * RecursionArray function can just accept unsigned integers
         * a parameters.
         *
         * @param n Index of the element
         * @return See user-defined function
         */
        virtual T function(size_t n) = 0;

    private:

        // Member data
        std::vector<T> values;  /**< Computed results of "function" */
};


} // namespace polder


#endif // _POLDER_RECURSION_ARRAY_H
