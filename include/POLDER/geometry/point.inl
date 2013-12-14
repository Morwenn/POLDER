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

template<size_t N, typename T>
inline Point<N, T>::Point(const Point<N, T>& other)
{
    std::copy(other.coordinates, other.coordinates+N, coordinates);
}

template<size_t N, typename T>
inline Point<N, T>::Point(std::initializer_list<T> coords)
{
    POLDER_ASSERT(N > 1 && coords.size() == N);
    std::copy(coords.begin(), coords.end(), coordinates);
}

template<size_t N, typename T>
template<typename... Args>
Point<N, T>::Point(Args... args)
{
    static_assert(sizeof...(Args) == N,
                  "Point constructed with wrong number of coordinates.");
    construct(args...);
}

template<size_t N, typename T>
inline T& Point<N, T>::operator[](size_t index)
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<size_t N, typename T>
inline T Point<N, T>::operator[](size_t index) const
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<size_t N, typename T>
inline Point<N, T>& Point<N, T>::operator=(const Point<N, T>& other)
{
    if (this != &other)
    {
        std::copy(other.coordinates, other.coordinates+N, coordinates);
    }
    return *this;
}

template<size_t N, typename T>
inline bool Point<N, T>::operator==(const Point<N, T>& other) const
{
    return std::equal(coordinates, coordinates+N, other.coordinates,
                      [](T a, T b)
                      {
                          return float_equal(a, b);
                      });
}

template<size_t N, typename T>
inline bool Point<N, T>::operator!=(const Point<N, T>& other) const
{
    return !(*this == other);
}

template<size_t N, typename T>
Point<N, T>& Point<N, T>::operator+=(const Vector<N, T>& V)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] += V[i];
    }
    return *this;
}

template<size_t N, typename T>
Point<N, T>& Point<N, T>::operator-=(const Vector<N, T>& V)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] -= V[i];
    }
    return *this;
}

template<size_t N, typename T>
inline const Point<N, T> Point<N, T>::operator+(const Vector<N, T>& V)
{
    return Point<N, T>(*this) += V;
}

template<size_t N, typename T>
inline const Point<N, T> Point<N, T>::operator-(const Vector<N, T>& V)
{
    return Point<N, T>(*this) -= V;
}

template<size_t N, typename T>
const Vector<N, T> Point<N, T>::operator-(const Point<N, T>& other)
{
    Vector<N, T> res = *this;
    for (size_t i = 0 ; i < N ; ++i)
    {
        res.coordinates[i] -= other[i];
    }
    return res;
}

template<size_t N, typename T>
inline T& Point<N, T>::x()
{
    return coordinates[0];
}

template<size_t N, typename T>
inline T& Point<N, T>::y()
{
    POLDER_ASSERT(N > 1);
    return coordinates[1];
}

template<size_t N, typename T>
inline T& Point<N, T>::z()
{
    POLDER_ASSERT(N > 2);
    return coordinates[2];
}

template<size_t N, typename T>
inline T Point<N, T>::x() const
{
    return coordinates[0];
}

template<size_t N, typename T>
inline T Point<N, T>::y() const
{
    POLDER_ASSERT(N > 1);
    return coordinates[1];
}

template<size_t N, typename T>
inline T Point<N, T>::z() const
{
    POLDER_ASSERT(N > 2);
    return coordinates[2];
}

template<size_t N, typename T>
inline typename Point<N, T>::iterator Point<N, T>::begin()
{
    return coordinates;
}

template<size_t N, typename T>
inline typename Point<N, T>::iterator Point<N, T>::end()
{
    return coordinates + N;
}

template<size_t N, typename T>
inline typename Point<N, T>::const_iterator Point<N, T>::begin() const
{
    return coordinates;
}

template<size_t N, typename T>
inline typename Point<N, T>::const_iterator Point<N, T>::end() const
{
    return coordinates + N;
}

template<size_t N, typename T>
inline typename Point<N, T>::const_iterator Point<N, T>::cbegin() const
{
    return coordinates;
}

template<size_t N, typename T>
inline typename Point<N, T>::const_iterator Point<N, T>::cend() const
{
    return coordinates + N;
}

template<size_t N, typename T>
template<typename First, typename... Args>
auto Point<N, T>::construct(First first, Args... args)
    -> void
{
    coordinates[N-sizeof...(args)-1] = first;
    construct(args...);
}

template<size_t N, typename T>
template<typename First>
auto Point<N, T>::construct(First first)
    -> void
{
    coordinates[N-1] = first;
}
