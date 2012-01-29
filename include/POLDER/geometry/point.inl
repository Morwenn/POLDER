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
inline Point<N>::Point():
    coordinates(new double[N])
{}

template<size_t N>
inline Point<N>::Point(const Point<N>& other):
    coordinates(new double[N])
{
    std::copy(other.coordinates, other.coordinates+N, coordinates);
}

template<size_t N>
inline Point<N>::Point(Point<N>&& other):
    coordinates(other.coordinates)
{
    other.coordinates = nullptr;
}

template<size_t N>
inline Point<N>::Point(const std::initializer_list<double>& coords):
    coordinates(new double[N])
{
    assert(N > 1 && coords.size() == N);
    std::copy(coords.begin(), coords.end(), coordinates);
}

template<size_t N>
Point<N>::Point(double first, ...):
    coordinates(new double[N])
{
    assert(N > 1);
    coordinates[0] = first;
    va_list args;
    va_start(args, first);
    for (size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i] = va_arg(args, double);
    }
    va_end(args);
}

template<size_t N>
inline Point<N>::~Point()
{
    delete[] coordinates;
}

template<size_t N>
inline double& Point<N>::operator[](size_t index)
{
    assert(index < N);
    return coordinates[index];
}

template<size_t N>
inline double Point<N>::operator[](size_t index) const
{
    assert(index < N);
    return coordinates[index];
}

template<size_t N>
inline Point<N>& Point<N>::operator=(const Point<N>& other)
{
    if (this != &other)
    {
        delete[] coordinates;
        coordinates = new double[N];
        std::copy(other.coordinates, other.coordinates+N, coordinates);
    }
    return *this;
}

template<size_t N>
inline Point<N>& Point<N>::operator=(Point<N>&& other)
{
    if (this != &other)
    {
        coordinates = other.coordinates;
        other.coordinates = nullptr;
    }
    return *this;
}

template<size_t N>
inline bool Point<N>::operator==(const Point<N>& other) const
{
    return round_equal(coordinates, coordinates+N, other.coordinates);
}

template<size_t N>
inline bool Point<N>::operator!=(const Point<N>& other) const
{
    return !(*this == other);
}

template<size_t N>
Point<N>& Point<N>::operator+=(const Vector<N>& V)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] += V[i];
    }
    return *this;
}

template<size_t N>
Point<N>& Point<N>::operator-=(const Vector<N>& V)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] -= V[i];
    }
    return *this;
}

template<size_t N>
inline const Point<N> Point<N>::operator+(const Vector<N>& V)
{
    return Point<N>(*this) += V;
}

template<size_t N>
inline const Point<N> Point<N>::operator-(const Vector<N>& V)
{
    return Point<N>(*this) -= V;
}

template<size_t N>
const Vector<N> Point<N>::operator-(const Point<N>& other)
{
    Vector<N> res = *this;
    for (size_t i = 0 ; i < N ; ++i)
    {
        res.coordinates[i] -= other[i];
    }
    return res;
}

template<size_t N>
inline double& Point<N>::x()
{
    return coordinates[0];
}

template<size_t N>
inline double& Point<N>::y()
{
    assert(N > 1);
    return coordinates[1];
}

template<size_t N>
inline double& Point<N>::z()
{
    assert(N > 2);
    return coordinates[2];
}

template<size_t N>
inline double Point<N>::x() const
{
    return coordinates[0];
}

template<size_t N>
inline double Point<N>::y() const
{
    assert(N > 1);
    return coordinates[1];
}

template<size_t N>
inline double Point<N>::z() const
{
    assert(N > 2);
    return coordinates[2];
}

template<size_t N>
inline typename Point<N>::iterator Point<N>::begin()
{
    return coordinates;
}

template<size_t N>
inline typename Point<N>::iterator Point<N>::end()
{
    return coordinates + N;
}

template<size_t N>
inline typename Point<N>::const_iterator Point<N>::begin() const
{
    return coordinates;
}

template<size_t N>
inline typename Point<N>::const_iterator Point<N>::end() const
{
    return coordinates + N;
}

template<size_t N>
inline typename Point<N>::const_iterator Point<N>::cbegin() const
{
    return coordinates;
}

template<size_t N>
inline typename Point<N>::const_iterator Point<N>::cend() const
{
    return coordinates + N;
}
