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
#ifndef POLDER_ITERATOR_H_
#define POLDER_ITERATOR_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iterator>

namespace polder
{
    /**
     * @brief Global rbegin function
     *
     * The equivalent of std::begin for reversed
     * iteration.
     */
    template<typename T>
    auto rbegin(T& iterable)
        -> decltype(iterable.rbegin());
    template<typename T>
    auto rbegin(const T& iterable)
        -> decltype(iterable.crbegin());
    template<typename T, std::size_t N>
    auto rbegin(T (&array)[N])
        -> std::reverse_iterator<T*>;

    /**
     * @brief Global rend function
     *
     * The equivalent of std::end for reversed
     * iteration.
     */
    template<typename T>
    auto rend(T& iterable)
        -> decltype(iterable.rend());
    template<typename T>
    auto rend(const T& iterable)
        -> decltype(iterable.crend());
    template<typename T, std::size_t N>
    auto rend(T (&array)[N])
        -> std::reverse_iterator<T*>;

    /**
     * @brief Iterator adapter
     *
     * Make an iterator which will get the nth
     * element of the object returned by the
     * given iterator. It allows to create iterators
     * to traverse keys of a std::map-like object
     * for example.
     * Useful to iterate through some specific std::pair
     * or std::tuple elements.
     */
    template<std::size_t N, typename Iterator>
    class get_iterator
    {
        private:

            Iterator _current;

        public:

            using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
            using iterator_type     = Iterator;
            using value_type        = std::remove_reference_t<decltype(std::get<N>(*_current))>;
            using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
            using pointer           = value_type*;
            using reference         = value_type&;

            get_iterator();
            explicit get_iterator(Iterator it);
            template<typename U>
            get_iterator(const get_iterator<N, U>& other);

            template<typename U>
            auto operator=(const get_iterator<N, U>& other)
                -> get_iterator&;

            auto base() const
                -> Iterator;

            auto operator*() const
                -> reference;
            auto operator->() const
                -> pointer;

            auto operator++()
                -> get_iterator&;
            auto operator++(int)
                -> get_iterator&;

            auto operator--()
                -> get_iterator&;
            auto operator--(int)
                -> get_iterator&;
    };

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator==(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator!=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator<(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator<=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator>(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    template<std::size_t N, typename Iterator1, typename Iterator2>
    auto operator>=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
        -> bool;

    #include "details/iterator.inl"
}

#endif // POLDER_ITERATOR_H_
