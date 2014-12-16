/*
 * Copyright (C) 2014 Morwenn
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
#ifndef POLDER_ITERATOR_TRANSFORM_ITERATOR_H_
#define POLDER_ITERATOR_TRANSFORM_ITERATOR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iterator>
#include <tuple>
#include <type_traits>
#include <POLDER/details/config.h>

namespace polder
{
    /**
     * @brief Iterator adapter.
     *
     * Make an iterator which will apply the given unary
     * function to the dereferenced iterator before
     * returning it.
     *
     * This class may perform the empty base class
     * optimization if UnaryFunction is an empty functor
     * class.
     */
    template<typename Iterator, typename UnaryFunction>
    class transform_iterator
    {
        private:

            // std::tuple may perform empty base class optimization
            // when UnaryFunction is an empty function object
            std::tuple<Iterator, UnaryFunction> members;

        public:

            using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
            using iterator_type     = Iterator;
            using value_type        = std::decay_t<decltype(std::get<1>(members)(*std::get<0>(members)))>;
            using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
            using pointer           = value_type*;
            using reference         = decltype(std::get<1>(members)(*std::get<0>(members)));

            transform_iterator();
            explicit transform_iterator(Iterator it);
            transform_iterator(Iterator it, UnaryFunction func);
            template<typename U>
            transform_iterator(const transform_iterator<U, UnaryFunction>& other);

            template<typename U>
            auto operator=(const transform_iterator<U, UnaryFunction>& other)
                -> transform_iterator&;

            auto base() const
                -> Iterator;

            auto operator*() const
                -> reference;
            auto operator->() const
                -> pointer;

            auto operator++()
                -> transform_iterator&;
            auto operator++(int)
                -> transform_iterator;

            auto operator--()
                -> transform_iterator&;
            auto operator--(int)
                -> transform_iterator;
    };

    template<typename Iterator1, typename Iterator2, typename UnaryFunction>
    auto operator==(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                    const transform_iterator<Iterator2, UnaryFunction>& rhs)
        -> bool;

    template<typename Iterator1, typename Iterator2, typename UnaryFunction>
    auto operator!=(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                    const transform_iterator<Iterator2, UnaryFunction>& rhs)
        -> bool;

    template<typename Iterator1, typename Iterator2, typename UnaryFunction>
    auto operator<(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                   const transform_iterator<Iterator2, UnaryFunction>& rhs)
        -> bool;

    template<typename Iterator1, typename Iterator2, typename UnaryFunction>
    auto operator<=(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                    const transform_iterator<Iterator2, UnaryFunction>& rhs)
        -> bool;

    template<typename Iterator1, typename Iterator2, typename UnaryFunction>
    auto operator>(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                   const transform_iterator<Iterator2, UnaryFunction>& rhs)
        -> bool;

    template<typename Iterator1, typename Iterator2, typename UnaryFunction>
    auto operator>=(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                    const transform_iterator<Iterator2, UnaryFunction>& rhs)
        -> bool;

    #include "details/transform_iterator.inl"
}

#endif // POLDER_ITERATOR_TRANSFORM_ITERATOR_H_
