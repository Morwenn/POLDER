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
// Operators
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto MutableVectorBase<N, T>::operator[](std::size_t index)
    -> reference
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<std::size_t N, typename T>
inline auto ImmutableVectorBase<N, T>::operator[](std::size_t index) const
    -> const_reference
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

////////////////////////////////////////////////////////////
// Coordinates aliases
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto MutableVectorBase<N, T>::x()
    -> reference
{
    return coordinates[0];
}

template<std::size_t N, typename T>
inline auto MutableVectorBase<N, T>::y()
    -> reference
{
    POLDER_ASSERT(N > 1);
    return coordinates[1];
}

template<std::size_t N, typename T>
inline auto MutableVectorBase<N, T>::z()
    -> reference
{
    POLDER_ASSERT(N > 2);
    return coordinates[2];
}

template<std::size_t N, typename T>
inline auto ImmutableVectorBase<N, T>::x() const
    -> const_reference
{
    return coordinates[0];
}

template<std::size_t N, typename T>
inline auto ImmutableVectorBase<N, T>::y() const
    -> const_reference
{
    POLDER_ASSERT(N > 1);
    return coordinates[1];
}

template<std::size_t N, typename T>
inline auto ImmutableVectorBase<N, T>::z() const
    -> const_reference
{
    POLDER_ASSERT(N > 2);
    return coordinates[2];
}

////////////////////////////////////////////////////////////
// Iterators
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto MutableVectorBase<N, T>::begin()
    -> iterator
{
    return std::begin(coordinates);
}

template<std::size_t N, typename T>
inline auto ImmutableVectorBase<N, T>::begin() const
    -> const_iterator
{
    return std::begin(coordinates);
}

template<std::size_t N, typename T>
inline auto ImmutableVectorBase<N, T>::cbegin() const
    -> const_iterator
{
    return std::begin(coordinates);
}

template<std::size_t N, typename T>
inline auto MutableVectorBase<N, T>::end()
    -> iterator
{
    return std::end(coordinates);
}

template<std::size_t N, typename T>
inline auto ImmutableVectorBase<N, T>::end() const
    -> const_iterator
{
    return std::end(coordinates);
}

template<std::size_t N, typename T>
inline auto ImmutableVectorBase<N, T>::cend() const
    -> const_iterator
{
    return std::end(coordinates);
}

////////////////////////////////////////////////////////////
// Protected construction methods
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
ImmutableVectorBase<N, T>::ImmutableVectorBase()
    = default;

template<std::size_t N, typename T>
ImmutableVectorBase<N, T>::ImmutableVectorBase(const ImmutableVectorBase& other)
{
    std::copy(
        std::begin(other.coordinates),
        std::end(other.coordinates),
        std::begin(coordinates)
    );
}

template<std::size_t N, typename T>
template<typename First, typename... Args>
auto ImmutableVectorBase<N, T>::construct(First first, Args... args)
    -> void
{
    coordinates[N-sizeof...(args)-1] = first;
    construct(args...);
}

template<std::size_t N, typename T>
template<typename First>
auto ImmutableVectorBase<N, T>::construct(First first)
    -> void
{
    coordinates[N-1] = first;
}
