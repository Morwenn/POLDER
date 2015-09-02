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

template<typename T, typename U>
auto compare(const T& lhs, const U& rhs)
    -> int
{
    return (lhs < rhs) ? -1 : (rhs < lhs);
}

template<typename CharT,
         typename Traits1, typename Alloc1,
         typename Traits2, typename Alloc2>
auto compare(const std::basic_string<CharT, Traits1, Alloc1>& lhs,
             const std::basic_string<CharT, Traits2, Alloc2>& rhs)
    -> int
{
    int res = lhs.compare(0, lhs.size(), rhs.data(), rhs.size());
    return compare(res, 0);
}

template<typename InputIt, typename UnaryOperation>
auto for_each(InputIt first, InputIt last, UnaryOperation unary_op)
    -> UnaryOperation
{
    return std::for_each(first, last, unary_op);
}

template<typename InputIt1, typename InputIt2, typename BinaryOperation>
auto for_each(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryOperation binary_op)
    -> BinaryOperation
{
    while (first1 != last1)
    {
        binary_op(*first1++, *first2++);
    }
    return binary_op;
}

template<typename Float>
constexpr auto float_equal(std::true_type, Float lhs, Float rhs)
    -> bool
{
    using math::meta::details::abs;
    using math::meta::details::max;

    return abs(lhs-rhs) <=
        std::numeric_limits<Float>::epsilon() *
        max(abs(lhs), abs(rhs));
}

template<typename T>
constexpr auto float_equal(std::false_type, T lhs, T rhs)
    -> bool
{
    return lhs == rhs;
}

template<typename T>
constexpr auto float_equal(T lhs, T rhs)
    -> bool
{
    return float_equal(std::is_floating_point<T>{}, lhs, rhs);
}
