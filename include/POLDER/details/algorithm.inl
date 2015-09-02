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

template<class ForwardIt, class Compare>
auto min_element_and_is_sorted(ForwardIt first, ForwardIt last, Compare comp)
    -> std::pair<ForwardIt, bool>
{
    if (first == last)
    {
        return { last, true };
    }

    ForwardIt smallest = first;
    first = std::is_sorted_until(first, last, comp);
    bool sorted = first == last;
    while (first != last)
    {
        if (comp(*first, *smallest))
        {
            smallest = first;
        }
        ++first;
    }
    return { smallest, sorted };
}

template<class ForwardIt, class Compare>
auto max_element_and_is_sorted(ForwardIt first, ForwardIt last, Compare comp)
    -> std::pair<ForwardIt, bool>
{
    if (first == last)
    {
        return { last, true };
    }

    first = std::is_sorted_until(first, last, comp);
    bool sorted = first == last;
    auto greatest = std::max_element(--first, last);
    return { greatest, sorted };
}

template<class ForwardIt, class Compare>
auto min_element_and_is_sorted_until(ForwardIt first, ForwardIt last, Compare comp)
    -> std::pair<ForwardIt, ForwardIt>
{
    if (first == last)
    {
        return { last, last };
    }

    ForwardIt smallest = first;
    auto res = std::is_sorted_until(first, last, comp);
    first = res;
    while (first != last)
    {
        if (comp(*first, *smallest))
        {
            smallest = first;
        }
        ++first;
    }
    return { smallest, res };
}

template<class ForwardIt, class Compare>
auto max_element_and_is_sorted(ForwardIt first, ForwardIt last, Compare comp)
    -> std::pair<ForwardIt, ForwardIt>
{
    if (first == last)
    {
        return { last, last };
    }

    first = std::is_sorted_until(first, last, comp);
    auto greatest = std::max_element(first-1, last);
    return { greatest, first };
}
