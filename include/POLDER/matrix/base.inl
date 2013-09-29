/*
 * Copyright (C) 2011-2013 Morwenn
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
// Operators
////////////////////////////////////////////////////////////

template<typename Derived>
inline auto MutableMatrix<Derived>::operator()(size_type y, size_type x)
    -> reference
{
    return derived()(y, x);
}

template<typename Derived>
inline auto ImmutableMatrix<Derived>::operator()(size_type y, size_type x) const
    -> value_type
{
    return derived()(y, x);
}

////////////////////////////////////////////////////////////
// STL-like functions
////////////////////////////////////////////////////////////

template<typename Derived>
auto MutableMatrix<Derived>::at(size_type y, size_type x)
    -> reference
{
    if (y > height())
    {
        throw std::out_of_range("Height out of range.");
    }
    else if (x > width())
    {
        throw std::out_of_range("Width out of range.");
    }
    return operator()(y, x);
}

template<typename Derived>
auto ImmutableMatrix<Derived>::at(size_type y, size_type x) const
    -> value_type
{
    if (y > height())
    {
        throw std::out_of_range("Height out of range.");
    }
    else if (x > width())
    {
        throw std::out_of_range("Width out of range.");
    }
    return operator()(y, x);
}

template<typename Derived>
inline auto ImmutableMatrix<Derived>::size() const
    -> size_type
{
    return height() * width();
}

////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

// Capacity
template<typename Derived>
inline auto ImmutableMatrix<Derived>::height() const
    -> size_type
{
    return derived().height();
}

template<typename Derived>
inline auto ImmutableMatrix<Derived>::width() const
    -> size_type
{
    return derived().width();
}

template<typename Derived>
inline auto ImmutableMatrix<Derived>::dimensions() const
    -> std::pair<size_type, size_type>
{
    return { height(), width() };
}

// Properties
template<typename Derived>
inline auto ImmutableMatrix<Derived>::is_square() const
    -> bool
{
    return height() == width();
}

////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////

template<typename Derived>
inline auto MutableMatrix<Derived>::derived()
    -> Derived&
{
    return static_cast<Derived&>(*this);
}

template<typename Derived>
inline auto ImmutableMatrix<Derived>::derived() const
    -> const Derived&
{
    return static_cast<const Derived&>(*this);
}
