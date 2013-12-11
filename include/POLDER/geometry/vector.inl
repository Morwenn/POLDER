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
inline Vector<N, T>::Vector(const Vector<N, T>& other)
{
    std::copy(other.coordinates, other.coordinates+N, coordinates);
}

template<size_t N, typename T>
inline Vector<N, T>::Vector(const std::initializer_list<T>& coords)
{
    POLDER_ASSERT(coords.size() == N);
    std::copy(coords.begin(), coords.end(), coordinates);
}

template<size_t N, typename T>
template<typename... Args>
Vector<N, T>::Vector(Args... args)
{
    static_assert(sizeof...(Args) == N,
                  "Vector constructed with wrong number of coordinates.");
    construct(args...);
}

template<size_t N, typename T>
inline Vector<N, T>::Vector(const Point<N, T>& P)
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
inline Direction<N, T> Vector<N, T>::direction() const
{
    return Direction<N, T>(*this);
}

template<size_t N, typename T>
T Vector<N, T>::norm(math::Norm n) const
{
    switch (n)
    {
        case math::Norm::Manhattan:
        {
            T res = 0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += std::abs(coordinates[i]);
            }
            return res;
        }
        case math::Norm::Euclidean:
        {
            T res = 0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += coordinates[i] * coordinates[i];
            }
            return sqrt(res);
        }
        case math::Norm::Maximum:
        {
            T res = std::abs(coordinates[0]);
            for (size_t i = 1 ; i < N ; ++i)
            {
                const T tmp = std::abs(coordinates[i]);
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
T Vector<N, T>::norm(math::Norm n, unsigned int p) const
{
    switch (n)
    {
        case math::Norm::P:
        {
            T res = 0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += pow(std::abs(coordinates[i]), p);
            }
            return pow(res, 1.0 / p);
        }
    }
    return 1.0; // Should never be executed
}

template<size_t N, typename T>
inline T Vector<N, T>::operator[](size_t index) const
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<size_t N, typename T>
inline T& Vector<N, T>::operator[](size_t index)
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<size_t N, typename T>
inline Vector<N, T>& Vector<N, T>::operator=(const Vector<N, T>& other)
{
    if (this != &other)
    {
        delete[] coordinates;
        coordinates = new T[N];
        std::copy(other.coordinates, other.coordinates+N, coordinates);
    }
    return *this;
}

template<size_t N, typename T>
inline bool Vector<N, T>::operator==(const Vector<N, T>& other) const
{
    return std::equal(coordinates, coordinates+N, other.coordinates,
                      [](T a, T b)
                      {
                          return float_equal(a, b);
                      });
}

template<size_t N, typename T>
inline bool Vector<N, T>::operator!=(const Vector<N, T>& other) const
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
inline Vector<N, T> Vector<N, T>::operator+(const Vector<N, T>& other) const
{
    return Vector<N, T>(*this) += other;
}

template<size_t N, typename T>
inline Vector<N, T> Vector<N, T>::operator-(const Vector<N, T>& other) const
{
    return Vector<N, T>(*this) -= other;
}

template<size_t N, typename T>
T Vector<N, T>::operator*(const Vector<N, T>& other) const
{
    T res = 0;
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
Vector<N, T>& Vector<N, T>::operator*=(T other)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates *= other;
    }
    return *this;
}

template<size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator/=(T other)
{
    POLDER_ASSERT(other != 0);
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates /= other;
    }
    return *this;
}

template<size_t N, typename T>
inline Vector<N, T> Vector<N, T>::operator*(T other) const
{
    return Vector(*this) *= other;
}

template<size_t N, typename T>
inline Vector<N, T> Vector<N, T>::operator/(T other) const
{
    return Vector(*this) /= other;
}

template<size_t N, typename T>
inline T& Vector<N, T>::x()
{
    return coordinates[0];
}

template<size_t N, typename T>
inline T& Vector<N, T>::y()
{
    return coordinates[1];
}

template<size_t N, typename T>
inline T& Vector<N, T>::z()
{
    return coordinates[2];
}

template<size_t N, typename T>
inline T Vector<N, T>::x() const
{
    return coordinates[0];
}

template<size_t N, typename T>
inline T Vector<N, T>::y() const
{
    return coordinates[1];
}

template<size_t N, typename T>
inline T Vector<N, T>::z() const
{
    return coordinates[2];
}

template<size_t N, typename T>
inline typename Vector<N, T>::iterator Vector<N, T>::begin()
{
    return coordinates;
}

template<size_t N, typename T>
inline typename Vector<N, T>::iterator Vector<N, T>::end()
{
    return coordinates + N;
}

template<size_t N, typename T>
inline typename Vector<N, T>::const_iterator Vector<N, T>::begin() const
{
    return coordinates;
}

template<size_t N, typename T>
inline typename Vector<N, T>::const_iterator Vector<N, T>::end() const
{
    return coordinates + N;
}

template<size_t N, typename T>
inline typename Vector<N, T>::const_iterator Vector<N, T>::cbegin() const
{
    return coordinates;
}

template<size_t N, typename T>
inline typename Vector<N, T>::const_iterator Vector<N, T>::cend() const
{
    return coordinates + N;
}

template<size_t N, typename T>
template<typename First, typename... Args>
auto Vector<N, T>::construct(First first, Args... args)
    -> void
{
    coordinates[N-sizeof...(args)-1] = first;
    construct(args...);
}

template<size_t N, typename T>
template<typename First>
auto Vector<N, T>::construct(First first)
    -> void
{
    coordinates[N-1] = first;
}
