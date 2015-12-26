/*
 * Copyright (C) 2015 Morwenn
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
#ifndef POLDER_ITERATOR_STRIDE_ITERATOR_H_
#define POLDER_ITERATOR_STRIDE_ITERATOR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iterator>
#include <POLDER/details/config.h>

namespace polder
{
    /**
     * @brief Stride iterator adapter.
     *
     * Make an iterator which will increment the given
     * iterator by an amount give at construction. It is
     * useful to implement a matrix over a vector and
     * have line iterators.
     */
    template<
        typename Iterator,
        typename Distance = typename std::iterator_traits<Iterator>::difference_type
    >
    class stride_iterator
    {
        private:

            Iterator _it;
            const Distance _stride = 1;

        public:

            ////////////////////////////////////////////////////////////
            // Public types

            using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
            using iterator_type     = Iterator;
            using value_type        = typename std::iterator_traits<Iterator>::value_type;
            using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
            using pointer           = typename std::iterator_traits<Iterator>::pointer;
            using reference         = typename std::iterator_traits<Iterator>::reference;

            ////////////////////////////////////////////////////////////
            // Constructors

            stride_iterator();
            explicit stride_iterator(Iterator it);
            stride_iterator(Iterator it, Distance stride);
            template<typename U>
            stride_iterator(const stride_iterator<U, Distance>& other);

            ////////////////////////////////////////////////////////////
            // Assignment operator

            template<typename U>
            auto operator=(const stride_iterator<U, Distance>& other)
                -> stride_iterator&;

            ////////////////////////////////////////////////////////////
            // Members access

            auto base() const
                -> Iterator;
            auto stride() const
                -> Distance;

            ////////////////////////////////////////////////////////////
            // Element access

            auto operator*() const
                -> reference;
            auto operator->() const
                -> pointer;

            ////////////////////////////////////////////////////////////
            // Increment/decrement operators

            auto operator++()
                -> stride_iterator&;
            auto operator++(int)
                -> stride_iterator;

            auto operator--()
                -> stride_iterator&;
            auto operator--(int)
                -> stride_iterator;
    };

    ////////////////////////////////////////////////////////////
    // Comparison operators

    template<typename Iterator1, typename Iterator2, typename Distance>
    auto operator==(const stride_iterator<Iterator1, Distance>& lhs,
                    const stride_iterator<Iterator2, Distance>& rhs)
        -> bool;

    template<typename Iterator1, typename Iterator2, typename Distance>
    auto operator!=(const stride_iterator<Iterator1, Distance>& lhs,
                    const stride_iterator<Iterator2, Distance>& rhs)
        -> bool;

    ////////////////////////////////////////////////////////////
    // Relational operators

    template<typename Iterator1, typename Iterator2, typename Distance>
    auto operator<(const stride_iterator<Iterator1, Distance>& lhs,
                   const stride_iterator<Iterator2, Distance>& rhs)
        -> bool;

    template<typename Iterator1, typename Iterator2, typename Distance>
    auto operator<=(const stride_iterator<Iterator1, Distance>& lhs,
                    const stride_iterator<Iterator2, Distance>& rhs)
        -> bool;

    template<typename Iterator1, typename Iterator2, typename Distance>
    auto operator>(const stride_iterator<Iterator1, Distance>& lhs,
                   const stride_iterator<Iterator2, Distance>& rhs)
        -> bool;

    template<typename Iterator1, typename Iterator2, typename Distance>
    auto operator>=(const stride_iterator<Iterator1, Distance>& lhs,
                    const stride_iterator<Iterator2, Distance>& rhs)
        -> bool;

    ////////////////////////////////////////////////////////////
    // Construction function

    template<typename Iterator, typename Distance>
    auto make_stride_iterator(Iterator it, Distance stride=1)
        -> stride_iterator<Iterator, Distance>;

    #include "details/stride_iterator.inl"
}

#endif // POLDER_ITERATOR_STRIDE_ITERATOR_H_
