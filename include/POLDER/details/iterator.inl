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

namespace details
{
    template<std::size_t N>
    struct getter
    {
        template<typename T>
        auto operator()(T&& arg) const
            -> decltype(auto)
        {
            return std::get<N>(std::forward<T>(arg));
        }
    };
}

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
// transform_iterator

template<typename Iterator, typename UnaryFunction>
transform_iterator<Iterator, UnaryFunction>::transform_iterator()
    = default;

template<typename Iterator, typename UnaryFunction>
transform_iterator<Iterator, UnaryFunction>::transform_iterator(Iterator it):
    members{it, UnaryFunction()}
{}

template<typename Iterator, typename UnaryFunction>
transform_iterator<Iterator, UnaryFunction>::transform_iterator(Iterator it, UnaryFunction func):
    members{it, func}
{}

template<typename Iterator, typename UnaryFunction>
template<typename U>
transform_iterator<Iterator, UnaryFunction>::transform_iterator(const transform_iterator<U, UnaryFunction>& other):
    members{other.base(), std::get<1>(other.members)}
{}

template<typename Iterator, typename UnaryFunction>
template<typename U>
auto transform_iterator<Iterator, UnaryFunction>::operator=(const transform_iterator<U, UnaryFunction>& other)
    -> transform_iterator&
{
    if (&other != this)
    {
        members = {
            other.base(),
            std::get<1>(other.members)
        };
    }
    return *this;
}

template<typename Iterator, typename UnaryFunction>
auto transform_iterator<Iterator, UnaryFunction>::base() const
    -> Iterator
{
    return std::get<0>(members);
}

template<typename Iterator, typename UnaryFunction>
auto transform_iterator<Iterator, UnaryFunction>::operator*() const
    -> reference
{
    return std::get<1>(members)(*base());
}

template<typename Iterator, typename UnaryFunction>
auto transform_iterator<Iterator, UnaryFunction>::operator->() const
    -> pointer
{
    return &(operator*());
}

template<typename Iterator, typename UnaryFunction>
auto transform_iterator<Iterator, UnaryFunction>::operator++()
    -> transform_iterator&
{
    ++std::get<0>(members);
    return *this;
}

template<typename Iterator, typename UnaryFunction>
auto transform_iterator<Iterator, UnaryFunction>::operator++(int)
    -> transform_iterator
{
    auto tmp = *this;
    operator++();
    return tmp;
}

template<typename Iterator, typename UnaryFunction>
auto transform_iterator<Iterator, UnaryFunction>::operator--()
    -> transform_iterator&
{
    --std::get<0>(members);
    return *this;
}

template<typename Iterator, typename UnaryFunction>
auto transform_iterator<Iterator, UnaryFunction>::operator--(int)
    -> transform_iterator
{
    auto tmp = *this;
    operator--();
    return tmp;
}

template<typename Iterator1, typename Iterator2, typename UnaryFunction>
auto operator==(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                const transform_iterator<Iterator2, UnaryFunction>& rhs)
    -> bool
{
    return lhs.base() == rhs.base();
}

template<typename Iterator1, typename Iterator2, typename UnaryFunction>
auto operator!=(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                const transform_iterator<Iterator2, UnaryFunction>& rhs)
    -> bool
{
    return lhs.base() != rhs.base();
}

template<typename Iterator1, typename Iterator2, typename UnaryFunction>
auto operator<(const transform_iterator<Iterator1, UnaryFunction>& lhs,
               const transform_iterator<Iterator2, UnaryFunction>& rhs)
    -> bool
{
    return lhs.base() < rhs.base();
}

template<typename Iterator1, typename Iterator2, typename UnaryFunction>
auto operator<=(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                const transform_iterator<Iterator2, UnaryFunction>& rhs)
    -> bool
{
    return lhs.base() <= rhs.base();
}

template<typename Iterator1, typename Iterator2, typename UnaryFunction>
auto operator>(const transform_iterator<Iterator1, UnaryFunction>& lhs,
               const transform_iterator<Iterator2, UnaryFunction>& rhs)
    -> bool
{
    return lhs.base() > rhs.base();
}

template<typename Iterator1, typename Iterator2, typename UnaryFunction>
auto operator>=(const transform_iterator<Iterator1, UnaryFunction>& lhs,
                const transform_iterator<Iterator2, UnaryFunction>& rhs)
    -> bool
{
    return lhs.base() >= rhs.base();
}
