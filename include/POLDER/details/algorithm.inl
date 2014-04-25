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

template<typename InputIt, typename UnaryOperation>
auto range_map(InputIt first, InputIt last, UnaryOperation unary_op)
    -> void
{
    while (first != last)
    {
        unary_op(*first++);
    }
}

template<typename InputIt1, typename InputIt2, typename BinaryOperation>
auto range_map(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op)
    -> void
{
    while (first1 != last1)
    {
        binary_op(*first1++, *first2++);
    }
}

template<typename Float>
auto float_equal(std::true_type, Float lhs, Float rhs)
    -> bool
{
    return std::abs(lhs-rhs) <=
        std::numeric_limits<Float>::epsilon() *
        std::max(std::abs(lhs), std::abs(rhs));
}

template<typename T>
auto float_equal(std::false_type, T lhs, T rhs)
    -> bool
{
    return lhs == rhs;
}

template<typename T>
auto float_equal(T lhs, T rhs)
    -> bool
{
    return float_equal(std::is_floating_point<T>{}, lhs, rhs);
}
