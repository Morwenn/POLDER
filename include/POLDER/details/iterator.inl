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

////////////////////////////////////////////////////////////
// Global begin and end functions

template<typename T>
auto rbegin(T& iterable)
    -> decltype(iterable.rbegin())
{
    return iterable.rbegin();
}

template<typename T>
auto rbegin(const T& iterable)
    -> decltype(iterable.crbegin())
{
    return iterable.crbegin();
}

template<typename T, std::size_t N>
auto rbegin(T (&array)[N])
    -> std::reverse_iterator<T*>
{
    return std::reverse_iterator<T*>(std::end(array));
}

template<typename T>
auto rend(T& iterable)
    -> decltype(iterable.rend())
{
    return iterable.rend();
}

template<typename T>
auto rend(const T& iterable)
    -> decltype(iterable.crend())
{
    return iterable.crend();
}

template<typename T, std::size_t N>
auto rend(T (&array)[N])
    -> std::reverse_iterator<T*>
{
    return std::reverse_iterator<T*>(std::begin(array));
}

////////////////////////////////////////////////////////////
// get_iterator

template<std::size_t N, typename Iterator>
get_iterator<N, Iterator>::get_iterator()
    = default;

template<std::size_t N, typename Iterator>
get_iterator<N, Iterator>::get_iterator(Iterator it):
    _current(it)
{}

template<std::size_t N, typename Iterator>
template<typename U>
get_iterator<N, Iterator>::get_iterator(const get_iterator<N, U>& other):
    _current(other.base())
{}

template<std::size_t N, typename Iterator>
template<typename U>
auto get_iterator<N, Iterator>::operator=(const get_iterator<N, U>& other)
    -> get_iterator&
{
    if (&other != this)
    {
        _current = other.base();
    }
    return *this;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::base() const
    -> Iterator
{
    return _current;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator*() const
    -> reference
{
    return std::get<N>(*_current);
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator->() const
    -> pointer
{
    return &(operator*());
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator++()
    -> get_iterator&
{
    ++_current;
    return *this;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator++(int)
    -> get_iterator&
{
    auto tmp = *this;
    ++_current;
    return tmp;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator--()
    -> get_iterator&
{
    --_current;
    return *this;
}

template<std::size_t N, typename Iterator>
auto get_iterator<N, Iterator>::operator--(int)
    -> get_iterator&
{
    auto tmp = *this;
    --_current;
    return tmp;
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator==(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return lhs.base() == rhs.base();
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator!=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator<(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return lhs.base() < rhs.base();
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator<=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return !(rhs < lhs);
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator>(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return rhs < lhs;
}

template<std::size_t N, typename Iterator1, typename Iterator2>
auto operator>=(const get_iterator<N, Iterator1>& lhs, const get_iterator<N, Iterator2>& rhs)
    -> bool
{
    return !(lhs < rhs);
}
