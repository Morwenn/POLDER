/*
 * Copyright (C) 2011-2012 Morwenn
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

template<size_t N, typename T>
Point<N, T>::Point(const Point<N, T>& other)
{
    std::copy(other.coordinates, other.coordinates+N, coordinates);
}

template<size_t N, typename T>
Point<N, T>::Point(const std::initializer_list<value_type>& coords)
{
    assert(N > 1 && coords.size() == N);
    std::copy(coords.begin(), coords.end(), coordinates);
}

template<size_t N, typename T>
template<typename... Args>
Point<N, T>::Point(Args... coords)
{
    static_assert(sizeof... coords == N, "Wrong number of arguments.");
    create(0, coords...);
}

template<size_t N, typename T>
auto Point<N, T>::operator[](size_t index) -> reference
{
    assert(index < N);
    return coordinates[index];
}

template<size_t N, typename T>
auto Point<N, T>::operator[](size_t index) const -> value_type
{
    assert(index < N);
    return coordinates[index];
}

template<size_t N, typename T>
Point<N, T>& Point<N, T>::operator=(const Point<N, T>& other)
{
    if (this != &other)
    {
        std::copy(other.coordinates, other.coordinates+N, coordinates);
    }
    return *this;
}

template<size_t N, typename T>
bool Point<N, T>::operator==(const Point<N, T>& other) const
{
    return round_equal(coordinates, coordinates+N, other.coordinates);
}

template<size_t N, typename T>
bool Point<N, T>::operator!=(const Point<N, T>& other) const
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
const Point<N, T> Point<N, T>::operator+(const Vector<N, T>& V)
{
    return Point<N, T>(*this) += V;
}

template<size_t N, typename T>
const Point<N, T> Point<N, T>::operator-(const Vector<N, T>& V)
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
auto Point<N, T>::x() -> reference
{
    return coordinates[0];
}

template<size_t N, typename T>
auto Point<N, T>::y() -> reference
{
    assert(N > 1);
    return coordinates[1];
}

template<size_t N, typename T>
auto Point<N, T>::z() -> reference
{
    assert(N > 2);
    return coordinates[2];
}

template<size_t N, typename T>
auto Point<N, T>::x() const -> value_type
{
    return coordinates[0];
}

template<size_t N, typename T>
auto Point<N, T>::y() const -> value_type
{
    assert(N > 1);
    return coordinates[1];
}

template<size_t N, typename T>
auto Point<N, T>::z() const -> value_type
{
    assert(N > 2);
    return coordinates[2];
}

template<size_t N, typename T>
typename Point<N, T>::iterator Point<N, T>::begin()
{
    return coordinates;
}

template<size_t N, typename T>
typename Point<N, T>::iterator Point<N, T>::end()
{
    return coordinates + N;
}

template<size_t N, typename T>
typename Point<N, T>::const_iterator Point<N, T>::begin() const
{
    return coordinates;
}

template<size_t N, typename T>
typename Point<N, T>::const_iterator Point<N, T>::end() const
{
    return coordinates + N;
}

template<size_t N, typename T>
typename Point<N, T>::const_iterator Point<N, T>::cbegin() const
{
    return coordinates;
}

template<size_t N, typename T>
typename Point<N, T>::const_iterator Point<N, T>::cend() const
{
    return coordinates + N;
}

template<size_t N, typename T>
template<typename... Args>
void Point<N, T>::create(size_t pos, T first, Args... coords)
{
    coordinates[pos] = first;
    if (pos < N)
    {
        create(pos+1, coords...);
    }
}

template<size_t N, typename T>
void Point<N, T>::create(size_t pos, T first)
{
    coordinates[pos] = first;
}
