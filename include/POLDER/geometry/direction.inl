/*
 * Copyright (C) 2011 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

template<size_t N>
inline Direction<N>::Direction():
    coordinates(new double[N-1])
{}

template<size_t N>
inline Direction<N>::Direction(const Direction<N>& other):
    coordinates(new double[N-1])
{
    std::copy(other.coordinates, other.coordinates+N-1, coordinates);
}

template<size_t N>
inline Direction<N>::Direction(Direction<N>&& other):
    coordinates(other.coordinates)
{
    other.coordinates = nullptr;
}

template<size_t N>
Direction<N>::Direction(const Point<N>& P):
    coordinates(new double[N-1])
{
    for (size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i-1] = P[i] / P[0];
    }
}

template<size_t N>
Direction<N>::Direction(const Point<N>& P1, const Point<N>& P2):
    coordinates(new double[N-1])
{
    const double first = P2[0] - P1[0];
    for (size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i-1] = (P2[i] - P1[i]) / first;
    }
}

template<size_t N>
Direction<N>::Direction(const Vector<N>& V):
    coordinates(new double[N-1])
{
    for (size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i-1] = V[i] / V[0];
    }
}

template<size_t N>
inline Direction<N>::Direction(const Line<N>& L)
{
    *this = L.direction();
}

template<size_t N>
inline Direction<N>::~Direction()
{
    delete[] coordinates;
}

template<size_t N>
inline double Direction<N>::operator[](size_t index) const
{
    if (index < N-1)
    {
        throw std::out_of_range("Index out of range.");
    }
    return coordinates[index];
}

template<size_t N>
Direction<N>& Direction<N>::operator=(const Direction<N>& other)
{
    if (this != &other)
    {
        delete[] coordinates;
        coordinates = new double[N-1];
        std::copy(other.coordinates, other.coordinates+N-1, coordinates);
    }
    return *this;
}

template<size_t N>
Direction<N>& Direction<N>::operator=(Direction<N>&& other)
{
    if (this != &other)
    {
        coordinates = other.coordinates;
        other.coordinates = nullptr;
    }
    return *this;
}

template<size_t N>
inline bool Direction<N>::operator==(const Direction<N>& other) const
{
    return round_equal(coordinates, coordinates+N-1, other.coordinates);
}

template<size_t N>
inline bool Direction<N>::operator!=(const Direction<N>& other) const
{
    return !(*this == other);
}

template<size_t N>
Direction<N> Direction<N>::operator-() const
{
    Direction<N> D(*this);
    for (size_t i = 0 ; i < N-1 ; ++i)
    {
        D.coordinates[i] = -D.coordinates[i];
    }
    return D;
}

template<size_t N>
inline typename Direction<N>::iterator Direction<N>::begin()
{
    return coordinates;
}

template<size_t N>
inline typename Direction<N>::iterator Direction<N>::end()
{
    return coordinates + N - 1;
}

template<size_t N>
inline typename Direction<N>::const_iterator Direction<N>::begin() const
{
    return coordinates;
}

template<size_t N>
inline typename Direction<N>::const_iterator Direction<N>::end() const
{
    return coordinates + N - 1;
}

template<size_t N>
inline typename Direction<N>::const_iterator Direction<N>::cbegin() const
{
    return coordinates;
}

template<size_t N>
inline typename Direction<N>::const_iterator Direction<N>::cend() const
{
    return coordinates + N - 1;
}
