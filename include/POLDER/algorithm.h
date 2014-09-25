/*
 * Copyright (C) 2011-2014 Morwenn
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
#ifndef POLDER_ALGORITHM_H_
#define POLDER_ALGORITHM_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>
#include <POLDER/math/details/cmath_base.h>

namespace polder
{
    /**
     * @brief Three-way comparison between values.
     *
     * Performs a three-way comparison between two
     * LessComparable values.
     *
     * @param lhs Left-hand side value
     * @param rhs Right-hand side value
     */
    template<typename T, typename U>
    auto compare(const T& lhs, const U& rhs)
        -> int;

    /**
     * @brief Map an unary function to a range
     *
     * Apply a given unary function to a given
     * range of iterators element-wise.
     *
     * @param first First element of the range
     * @param last Last element of the range
     * @param unary_op Operation to apply to the range
     */
    template<typename InputIt, typename UnaryOperation>
    auto range_map(InputIt first, InputIt last, UnaryOperation unary_op)
        -> void;

    /**
     * @brief Map a binary function to a range
     *
     * Apply a given binary function element-wise
     * taking two ranges as argument.
     *
     * @param first1 First element of the first range
     * @param last1 Last element of the first range
     * @param first2 First element of the second range
     * @param binary_op Operation to apply to the range
     */
    template<typename InputIt1, typename InputIt2, typename BinaryOperation>
    auto range_map(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op)
        -> void;

    /**
     *
     * @brief Floating point comparison
     *
     * Compares two floating point numbers by checking whether
     * the difference between the two of them is lower than a
     * given value.
     *
     * If the types are not floating point types, a regular
     * comparison is performed instead.
     *
     * @param lhs First value to compare
     * @param rhs Second value to compare
     * @return true if the values compare equal
     */
    template<typename T>
    constexpr auto float_equal(T lhs, T rhs)
        -> bool;

    #include "details/algorithm.inl"
}

#endif // POLDER_ALGORITHM_H_
