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
// Defaulted functions
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
Point<N, T>::Point()
    = default;

template<std::size_t N, typename T>
Point<N, T>::Point(const Point<N, T>&)
    = default;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
template<typename... Args>
Point<N, T>::Point(Args... args)
{
    static_assert(sizeof...(Args) == N,
                  "Point constructed with wrong number of coordinates.");
    construct(args...);
}

////////////////////////////////////////////////////////////
// Operators
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto Point<N, T>::operator[](std::size_t index)
    -> reference
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<std::size_t N, typename T>
inline auto Point<N, T>::operator[](std::size_t index) const
    -> const_reference
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<std::size_t N, typename T>
auto Point<N, T>::operator+=(const Vector<N, T>& vec)
    -> Point&
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] += vec[i];
    }
    return *this;
}

template<std::size_t N, typename T>
auto Point<N, T>::operator-=(const Vector<N, T>& vec)
    -> Point&
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] -= vec[i];
    }
    return *this;
}

////////////////////////////////////////////////////////////
// Coordinates aliases
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto Point<N, T>::x()
    -> reference
{
    return coordinates[0];
}

template<std::size_t N, typename T>
inline auto Point<N, T>::y()
    -> reference
{
    POLDER_ASSERT(N > 1);
    return coordinates[1];
}

template<std::size_t N, typename T>
inline auto Point<N, T>::z()
    -> reference
{
    POLDER_ASSERT(N > 2);
    return coordinates[2];
}

template<std::size_t N, typename T>
inline auto Point<N, T>::x() const
    -> const_reference
{
    return coordinates[0];
}

template<std::size_t N, typename T>
inline auto Point<N, T>::y() const
    -> const_reference
{
    POLDER_ASSERT(N > 1);
    return coordinates[1];
}

template<std::size_t N, typename T>
inline auto Point<N, T>::z() const
    -> const_reference
{
    POLDER_ASSERT(N > 2);
    return coordinates[2];
}

////////////////////////////////////////////////////////////
// Iterators
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto Point<N, T>::begin()
    -> iterator
{
    return std::begin(coordinates);
}

template<std::size_t N, typename T>
inline auto Point<N, T>::begin() const
    -> const_iterator
{
    return std::begin(coordinates);
}

template<std::size_t N, typename T>
inline auto Point<N, T>::cbegin() const
    -> const_iterator
{
    return std::begin(coordinates);
}

template<std::size_t N, typename T>
inline auto Point<N, T>::end()
    -> iterator
{
    return std::end(coordinates);
}

template<std::size_t N, typename T>
inline auto Point<N, T>::end() const
    -> const_iterator
{
    return std::end(coordinates);
}

template<std::size_t N, typename T>
inline auto Point<N, T>::cend() const
    -> const_iterator
{
    return std::end(coordinates);
}

////////////////////////////////////////////////////////////
// Private construction methods
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
template<typename First, typename... Args>
auto Point<N, T>::construct(First first, Args... args)
    -> void
{
    coordinates[N-sizeof...(args)-1] = first;
    construct(args...);
}

template<std::size_t N, typename T>
template<typename First>
auto Point<N, T>::construct(First first)
    -> void
{
    coordinates[N-1] = first;
}

////////////////////////////////////////////////////////////
// Outside class operators - Comparison
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
auto operator==(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(),
                      [](T a, T b)
                      {
                          return float_equal(a, b);
                      });
}

template<std::size_t N, typename T>
auto operator!=(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

////////////////////////////////////////////////////////////
// Outside class operators - Point-Vector arithmetic
////////////////////////////////////////////////////////////

template<std::size_t N, typename T>
inline auto operator+(Point<N, T> pt, const Vector<N, T>& vec)
    -> Point<N, T>
{
    return pt += vec;
}

template<std::size_t N, typename T>
inline auto operator-(Point<N, T> pt, const Vector<N, T>& vec)
    -> Point<N, T>
{
    return pt -= vec;
}

template<std::size_t N, typename T>
auto operator-(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> Vector<N, T>
{
    Vector<N, T> res;
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        res[i] -= lhs[i] - rhs[i];
    }
    return res;
}
