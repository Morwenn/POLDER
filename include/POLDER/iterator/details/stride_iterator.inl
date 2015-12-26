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

////////////////////////////////////////////////////////////
// Constructors

template<typename Iterator, typename Distance>
stride_iterator<Iterator, Distance>::stride_iterator()
    = default;

template<typename Iterator, typename Distance>
stride_iterator<Iterator, Distance>::stride_iterator(Iterator it):
    _it{it}
{}

template<typename Iterator, typename Distance>
stride_iterator<Iterator, Distance>::stride_iterator(Iterator it, Distance stride):
    _it{it},
    _stride{stride}
{}

template<typename Iterator, typename Distance>
template<typename U>
stride_iterator<Iterator, Distance>::stride_iterator(const stride_iterator<U, Distance>& other):
    _it{other.base()},
    _stride{other.stride()}
{}

////////////////////////////////////////////////////////////
// Assignment operator

template<typename Iterator, typename Distance>
template<typename U>
auto stride_iterator<Iterator, Distance>::operator=(const stride_iterator<U, Distance>& other)
    -> stride_iterator&
{
    _it = other.base();
    _stride = other.stride();
    return *this;
}

////////////////////////////////////////////////////////////
// Members access

template<typename Iterator, typename Distance>
auto stride_iterator<Iterator, Distance>::base() const
    -> Iterator
{
    return _it;
}

template<typename Iterator, typename Distance>
auto stride_iterator<Iterator, Distance>::stride() const
    -> Distance
{
    return _stride;
}

////////////////////////////////////////////////////////////
// Element access

template<typename Iterator, typename Distance>
auto stride_iterator<Iterator, Distance>::operator*() const
    -> reference
{
    return *_it;
}

template<typename Iterator, typename Distance>
auto stride_iterator<Iterator, Distance>::operator->() const
    -> pointer
{
    return &(operator*());
}

////////////////////////////////////////////////////////////
// Increment/decrement operators

template<typename Iterator, typename Distance>
auto stride_iterator<Iterator, Distance>::operator++()
    -> stride_iterator&
{
    std::advance(_it, stride());
    return *this;
}

template<typename Iterator, typename Distance>
auto stride_iterator<Iterator, Distance>::operator++(int)
    -> stride_iterator
{
    auto tmp = *this;
    operator++();
    return tmp;
}

template<typename Iterator, typename Distance>
auto stride_iterator<Iterator, Distance>::operator--()
    -> stride_iterator&
{
    std::advance(_it, -stride());
    return *this;
}

template<typename Iterator, typename Distance>
auto stride_iterator<Iterator, Distance>::operator--(int)
    -> stride_iterator
{
    auto tmp = *this;
    operator--();
    return tmp;
}

////////////////////////////////////////////////////////////
// Comparison operators

template<typename Iterator1, typename Iterator2, typename Distance>
auto operator==(const stride_iterator<Iterator1, Distance>& lhs,
                const stride_iterator<Iterator2, Distance>& rhs)
    -> bool
{
    return lhs.base() == rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Distance>
auto operator!=(const stride_iterator<Iterator1, Distance>& lhs,
                const stride_iterator<Iterator2, Distance>& rhs)
    -> bool
{
    return lhs.base() != rhs.base();
}

////////////////////////////////////////////////////////////
// Relational operators

template<typename Iterator1, typename Iterator2, typename Distance>
auto operator<(const stride_iterator<Iterator1, Distance>& lhs,
               const stride_iterator<Iterator2, Distance>& rhs)
    -> bool
{
    return lhs.base() < rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Distance>
auto operator<=(const stride_iterator<Iterator1, Distance>& lhs,
                const stride_iterator<Iterator2, Distance>& rhs)
    -> bool
{
    return lhs.base() <= rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Distance>
auto operator>(const stride_iterator<Iterator1, Distance>& lhs,
               const stride_iterator<Iterator2, Distance>& rhs)
    -> bool
{
    return lhs.base() > rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Distance>
auto operator>=(const stride_iterator<Iterator1, Distance>& lhs,
                const stride_iterator<Iterator2, Distance>& rhs)
    -> bool
{
    return lhs.base() >= rhs.base();
}

////////////////////////////////////////////////////////////
// Construction function

template<typename Iterator, typename Distance>
auto make_stride_iterator(Iterator it, Distance stride)
    -> stride_iterator<Iterator, Distance>
{
    return { it, stride };
}
