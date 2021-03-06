/*
 * Copyright (C) 2011-2016 Morwenn
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
#include <functional>
#include <limits>
#include <string>
#include <type_traits>
#include <utility>
#include <POLDER/details/config.h>
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

    template<typename CharT,
             typename Traits1, typename Alloc1,
             typename Traits2, typename Alloc2>
    auto compare(const std::basic_string<CharT, Traits1, Alloc1>& lhs,
                 const std::basic_string<CharT, Traits2, Alloc2>& rhs)
        -> int;

    /**
     * @brief Applies an unary function to a range.
     *
     * Applies a given unary function to a given
     * range of iterators element-wise.
     *
     * @param first First element of the range
     * @param last Last element of the range
     * @param unary_op Operation to apply to the range
     */
    template<typename InputIt, typename UnaryOperation>
    auto for_each(InputIt first, InputIt last, UnaryOperation unary_op)
        -> UnaryOperation;

    /**
     * @brief Applies a binary function to a range.
     *
     * Applies a given binary function element-wise
     * taking two ranges as argument.
     *
     * @param first1 First element of the first range
     * @param last1 Last element of the first range
     * @param first2 First element of the second range
     * @param binary_op Operation to apply to the range
     */
    template<typename InputIt1, typename InputIt2, typename BinaryOperation>
    auto for_each(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op)
        -> BinaryOperation;

    /**
     * @brief Fused std::min_element and std::is_sorted.
     *
     * Returns the min element of a range and whether
     * this range is sorted.
     *
     * @param first First element of the range
     * @param last Last element of the range
     * @return Min element and whether the range is sorted
     */
    template<typename ForwardIt, typename Compare=std::less<>>
    auto min_element_and_is_sorted(ForwardIt first, ForwardIt last, Compare comp={})
        -> decltype(auto);

    /**
     * @brief Fused std::max_element and std::is_sorted.
     *
     * Returns the max element of a range and whether
     * this range is sorted.
     *
     * @param first First element of the range
     * @param last Last element of the range
     * @return Max element and whether the range is sorted
     */
    template<typename ForwardIt, typename Compare=std::less<>>
    auto max_element_and_is_sorted(ForwardIt first, ForwardIt last, Compare comp={})
        -> decltype(auto);


    /**
     * @brief Fused std::min_element and std::is_sorted_until.
     *
     * Returns an iterator to the min element of a range and
     * the iterator one past the last sorted element.
     *
     * @param first First element of the range
     * @param last Last element of the range
     * @return Min element and past sorted element
     */
    template<typename ForwardIt, typename Compare=std::less<>>
    auto min_element_and_is_sorted_until(ForwardIt first, ForwardIt last, Compare comp={})
        -> decltype(auto);

    /**
     * @brief Fused std::max_element and std::is_sorted_until.
     *
     * Returns an iterator to the max element of a range and
     * the iterator one past the last sorted element.
     *
     * @param first First element of the range
     * @param last Last element of the range
     * @return Max element and past sorted element
     */
    template<typename ForwardIt, typename Compare=std::less<>>
    auto max_element_and_is_sorted_until(ForwardIt first, ForwardIt last, Compare comp={})
        -> decltype(auto);

    #include "details/algorithm.inl"
}

#endif // POLDER_ALGORITHM_H_
