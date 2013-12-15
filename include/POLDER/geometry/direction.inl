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

template<std::size_t N, typename T>
inline Direction<N, T>::Direction(const Direction<N, T>& other)
{
    std::copy(other.coordinates, other.coordinates+N-1, coordinates);
}

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Point<N, T>& P)
{
    for (std::size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i-1] = P[i] / P[0];
    }
}

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Point<N, T>& P1, const Point<N, T>& P2)
{
    const T first = P2[0] - P1[0];
    for (std::size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i-1] = (P2[i] - P1[i]) / first;
    }
}

template<std::size_t N, typename T>
Direction<N, T>::Direction(const Vector<N, T>& V)
{
    for (std::size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i-1] = V[i] / V[0];
    }
}

template<std::size_t N, typename T>
inline Direction<N, T>::Direction(const Line<N, T>& L)
{
    *this = L.direction();
}

template<std::size_t N, typename T>
inline T Direction<N, T>::operator[](std::size_t index) const
{
    if (index > N-1)
    {
        throw std::out_of_range("Index out of range.");
    }
    return coordinates[index];
}

template<std::size_t N, typename T>
Direction<N, T>& Direction<N, T>::operator=(const Direction<N, T>& other)
{
    if (this != &other)
    {
        std::copy(other.coordinates, other.coordinates+N-1, coordinates);
    }
    return *this;
}

template<std::size_t N, typename T>
inline bool Direction<N, T>::operator==(const Direction<N, T>& other) const
{
    return std::equal(coordinates, coordinates+N-1, other.coordinates,
                      [](T a, T b)
                      {
                          return float_equal(a, b);
                      });
}

template<std::size_t N, typename T>
inline bool Direction<N, T>::operator!=(const Direction<N, T>& other) const
{
    return !(*this == other);
}

template<std::size_t N, typename T>
Direction<N, T> Direction<N, T>::operator-() const
{
    Direction<N, T> D(*this);
    for (std::size_t i = 0 ; i < N-1 ; ++i)
    {
        D.coordinates[i] = -D.coordinates[i];
    }
    return D;
}

template<std::size_t N, typename T>
inline typename Direction<N, T>::iterator Direction<N, T>::begin()
{
    return coordinates;
}

template<std::size_t N, typename T>
inline typename Direction<N, T>::iterator Direction<N, T>::end()
{
    return coordinates + N - 1;
}

template<std::size_t N, typename T>
inline typename Direction<N, T>::const_iterator Direction<N, T>::begin() const
{
    return coordinates;
}

template<std::size_t N, typename T>
inline typename Direction<N, T>::const_iterator Direction<N, T>::end() const
{
    return coordinates + N - 1;
}

template<std::size_t N, typename T>
inline typename Direction<N, T>::const_iterator Direction<N, T>::cbegin() const
{
    return coordinates;
}

template<std::size_t N, typename T>
inline typename Direction<N, T>::const_iterator Direction<N, T>::cend() const
{
    return coordinates + N - 1;
}
