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

template<std::size_t N, typename T>
inline T& Point<N, T>::operator[](std::size_t index)
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<std::size_t N, typename T>
inline T Point<N, T>::operator[](std::size_t index) const
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<std::size_t N, typename T>
Point<N, T>& Point<N, T>::operator+=(const Vector<N, T>& V)
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] += V[i];
    }
    return *this;
}

template<std::size_t N, typename T>
Point<N, T>& Point<N, T>::operator-=(const Vector<N, T>& V)
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] -= V[i];
    }
    return *this;
}

template<std::size_t N, typename T>
inline T& Point<N, T>::x()
{
    return coordinates[0];
}

template<std::size_t N, typename T>
inline T& Point<N, T>::y()
{
    POLDER_ASSERT(N > 1);
    return coordinates[1];
}

template<std::size_t N, typename T>
inline T& Point<N, T>::z()
{
    POLDER_ASSERT(N > 2);
    return coordinates[2];
}

template<std::size_t N, typename T>
inline T Point<N, T>::x() const
{
    return coordinates[0];
}

template<std::size_t N, typename T>
inline T Point<N, T>::y() const
{
    POLDER_ASSERT(N > 1);
    return coordinates[1];
}

template<std::size_t N, typename T>
inline T Point<N, T>::z() const
{
    POLDER_ASSERT(N > 2);
    return coordinates[2];
}

template<std::size_t N, typename T>
inline typename Point<N, T>::iterator Point<N, T>::begin()
{
    return std::begin(coordinates);
}

template<std::size_t N, typename T>
inline typename Point<N, T>::iterator Point<N, T>::end()
{
    return std::end(coordinates);
}

template<std::size_t N, typename T>
inline typename Point<N, T>::const_iterator Point<N, T>::begin() const
{
    return std::begin(coordinates);;
}

template<std::size_t N, typename T>
inline typename Point<N, T>::const_iterator Point<N, T>::end() const
{
    return std::end(coordinates);
}

template<std::size_t N, typename T>
inline typename Point<N, T>::const_iterator Point<N, T>::cbegin() const
{
    return std::begin(coordinates);
}

template<std::size_t N, typename T>
inline typename Point<N, T>::const_iterator Point<N, T>::cend() const
{
    return std::end(coordinates);
}

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
