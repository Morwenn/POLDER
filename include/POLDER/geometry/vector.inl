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
Vector<N, T>::Vector(const Vector<N, T>& other)
{
    std::copy(other.coordinates, other.coordinates+N, coordinates);
}

template<size_t N, typename T>
Vector<N, T>::Vector(const std::initializer_list<value_type>& coords)
{
    assert(coords.size() == N);
    std::copy(coords.begin(), coords.end(), coordinates);
}

template<size_t N, typename T>
template<typename... Args>
Vector<N, T>::Vector(Args... coords)
{
    static_assert(sizeof... coords == N, "Wrong number of arguments.");
    create(0, coords...);
}

template<size_t N, typename T>
Vector<N, T>::Vector(const Point<N, T>& P)
{
    std::copy(P.coordinates, P.coordinates+N, coordinates);
}

template<size_t N, typename T>
Vector<N, T>::Vector(const Point<N, T>& origin, const Point<N, T>& target)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] = target[i] - origin[i];
    }
}

template<size_t N, typename T>
Vector<N, T>::Vector(const Line<N, T>& L)
{
    coordinates[0] = 1.0;
    const Direction<N, T>& dir = L.direction();
    for (size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i] = dir[i-1];
    }
}

template<size_t N, typename T>
Direction<N, T> Vector<N, T>::direction() const
{
    return Direction<N, T>(*this);
}

template<size_t N, typename T>
auto Vector<N, T>::norm(math::Norm n) const -> value_type
{
    switch (n)
    {
        case math::Norm::Manhattan:
        {
            value_type res = 0.0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += fabs(coordinates[i]);
            }
            return res;
        }
        case math::Norm::Euclidean:
        {
            value_type res = 0.0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += coordinates[i] * coordinates[i];
            }
            return sqrt(res);
        }
        case math::Norm::Maximum:
        {
            value_type res = fabs(coordinates[0]);
            for (size_t i = 1 ; i < N ; ++i)
            {
                const value_type tmp = fabs(coordinates[i]);
                if (tmp > res)
                {
                    res = tmp;
                }
            }
            return res;
        }
    }
    return 1.0; // Should never be executed
}

template<size_t N, typename T>
auto Vector<N, T>::norm(math::Norm n, unsigned int p) const -> value_type
{
    switch (n)
    {
        case math::Norm::P:
        {
            value_type res = 0.0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += pow(fabs(coordinates[i]), p);
            }
            return pow(res, 1.0 / p);
        }
    }
    return 1.0; // Should never be executed
}

template<size_t N, typename T>
auto Vector<N, T>::operator[](size_t index) const -> value_type
{
    assert(index < N);
    return coordinates[index];
}

template<size_t N, typename T>
auto Vector<N, T>::operator[](size_t index) -> reference
{
    assert(index < N);
    return coordinates[index];
}

template<size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator=(const Vector<N, T>& other)
{
    if (this != &other)
    {
        std::copy(other.coordinates, other.coordinates+N, coordinates);
    }
    return *this;
}

template<size_t N, typename T>
bool Vector<N, T>::operator==(const Vector<N, T>& other) const
{
    return round_equal(coordinates, coordinates+N, other.coordinates);
}

template<size_t N, typename T>
bool Vector<N, T>::operator!=(const Vector<N, T>& other) const
{
    return !(*this == other);
}

template<size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator+=(const Vector<N, T>& other)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] += other.coordinates[i];
    }
    return *this;
}

template<size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator-=(const Vector<N, T>& other)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] -= other.coordinates[i];
    }
    return *this;
}

template<size_t N, typename T>
Vector<N, T> Vector<N, T>::operator+(const Vector<N, T>& other) const
{
    return Vector<N, T>(*this) += other;
}

template<size_t N, typename T>
Vector<N, T> Vector<N, T>::operator-(const Vector<N, T>& other) const
{
    return Vector<N, T>(*this) -= other;
}

template<size_t N, typename T>
auto Vector<N, T>::operator*(const Vector<N, T>& other) const -> value_type
{
    value_type res = 0.0;
    for (size_t i = 0 ; i < N ; ++i)
    {
        res += coordinates[i] * other.coordinates[i];
    }
    return res;
}

template<size_t N, typename T>
Vector<N, T> Vector<N, T>::operator-() const
{
    Vector<N, T> V = *this;
    for (size_t i = 0 ; i < N ; ++i)
    {
        V.coordinates[i] = -V.coordinates[i];
    }
    return V;
}

template<size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator*=(value_type other)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates *= other;
    }
    return *this;
}

template<size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator/=(value_type other)
{
    assert(other != 0);
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates /= other;
    }
    return *this;
}

template<size_t N, typename T>
Vector<N, T> Vector<N, T>::operator*(value_type other) const
{
    return Vector(*this) *= other;
}

template<size_t N, typename T>
Vector<N, T> Vector<N, T>::operator/(value_type other) const
{
    return Vector(*this) /= other;
}

template<size_t N, typename T>
auto Vector<N, T>::x() -> reference
{
    return coordinates[0];
}

template<size_t N, typename T>
auto Vector<N, T>::y() -> reference
{
    return coordinates[1];
}

template<size_t N, typename T>
auto Vector<N, T>::z() -> reference
{
    return coordinates[2];
}

template<size_t N, typename T>
auto Vector<N, T>::x() const -> value_type
{
    return coordinates[0];
}

template<size_t N, typename T>
auto Vector<N, T>::y() const -> value_type
{
    return coordinates[1];
}

template<size_t N, typename T>
auto Vector<N, T>::z() const -> value_type
{
    return coordinates[2];
}

template<size_t N, typename T>
typename Vector<N, T>::iterator Vector<N, T>::begin()
{
    return coordinates;
}

template<size_t N, typename T>
typename Vector<N, T>::iterator Vector<N, T>::end()
{
    return coordinates + N;
}

template<size_t N, typename T>
typename Vector<N, T>::const_iterator Vector<N, T>::begin() const
{
    return coordinates;
}

template<size_t N, typename T>
typename Vector<N, T>::const_iterator Vector<N, T>::end() const
{
    return coordinates + N;
}

template<size_t N, typename T>
typename Vector<N, T>::const_iterator Vector<N, T>::cbegin() const
{
    return coordinates;
}

template<size_t N, typename T>
typename Vector<N, T>::const_iterator Vector<N, T>::cend() const
{
    return coordinates + N;
}

template<size_t N, typename T>
template<typename... Args>
void Vector<N, T>::create(size_t pos, T first, Args... coords)
{
    coordinates[pos] = first;
    if (pos < N)
    {
        create(pos+1, coords...);
    }
}

template<size_t N, typename T>
void Vector<N, T>::create(size_t pos, T first)
{
    coordinates[pos] = first;
}
