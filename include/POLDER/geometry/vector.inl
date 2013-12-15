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

namespace details
{
    template<std::size_t N, typename T, typename Norm>
    struct vecnorm_helper_t;

    template<std::size_t N, typename T>
    struct vecnorm_helper_t<N, T, math::norm::manhattan>
    {
        static auto norm(const Vector<N, T>& vec)
            -> T
        {
            T res = T(0);
            for (auto coord: vec)
            {
                res += std::abs(coord);
            }
            return res;
        }
    };

    template<std::size_t N, typename T>
    struct vecnorm_helper_t<N, T, math::norm::euclidean>
    {
        static auto norm(const Vector<N, T>& vec)
            -> T
        {
            T res = T(0);
            for (auto coord: vec)
            {
                auto tmp = std::abs(coord);
                res += tmp * tmp;
            }
            return std::sqrt(res);
        }
    };

    template<std::size_t N, typename T>
    struct vecnorm_helper_t<N, T, math::norm::maximum>
    {
        static auto norm(const Vector<N, T>& vec)
            -> T
        {
            T res = std::abs(vec[0]);
            for (std::size_t i = 1 ; i < N ; ++i)
            {
                T tmp = std::abs(vec[i]);
                if (tmp > res)
                {
                    res = tmp;
                }
            }
            return res;
        }
    };

    template<std::size_t N, typename T>
    struct vecnorm_helper_t<N, T, math::norm::p>
    {
        static auto norm(const Vector<N, T>& vec, unsigned p)
            -> T
        {
            T res = T(0);
            for (auto coord: vec)
            {
                auto tmp = std::abs(coord);
                res += std::pow(tmp, p);
            }
            return std::pow(res, 1.0/p);
        }
    };
}

template<std::size_t N, typename T>
inline Vector<N, T>::Vector(const Vector<N, T>& other)
{
    std::copy(other.coordinates, other.coordinates+N, coordinates);
}

template<std::size_t N, typename T>
inline Vector<N, T>::Vector(std::initializer_list<T> coords)
{
    POLDER_ASSERT(coords.size() == N);
    std::copy(coords.begin(), coords.end(), coordinates);
}

template<std::size_t N, typename T>
template<typename... Args>
Vector<N, T>::Vector(Args... args)
{
    static_assert(sizeof...(Args) == N,
                  "Vector constructed with wrong number of coordinates.");
    construct(args...);
}

template<std::size_t N, typename T>
inline Vector<N, T>::Vector(const Point<N, T>& P)
{
    std::copy(P.coordinates, P.coordinates+N, coordinates);
}

template<std::size_t N, typename T>
Vector<N, T>::Vector(const Point<N, T>& origin, const Point<N, T>& target)
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] = target[i] - origin[i];
    }
}

template<std::size_t N, typename T>
Vector<N, T>::Vector(const Line<N, T>& L)
{
    coordinates[0] = 1.0;
    const Direction<N, T>& dir = L.direction();
    for (std::size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i] = dir[i-1];
    }
}

template<std::size_t N, typename T>
inline Direction<N, T> Vector<N, T>::direction() const
{
    return Direction<N, T>(*this);
}

template<std::size_t N, typename T>
template<typename Norm>
auto Vector<N, T>::norm() const
    -> T
{
    return details::vecnorm_helper_t<N, T, Norm>::norm(*this);
}

template<std::size_t N, typename T>
template<typename Norm>
auto Vector<N, T>::norm(unsigned p) const
    -> T
{
    return details::vecnorm_helper_t<N, T, Norm>::norm(*this, p);
}

template<std::size_t N, typename T>
inline T Vector<N, T>::operator[](std::size_t index) const
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<std::size_t N, typename T>
inline T& Vector<N, T>::operator[](std::size_t index)
{
    POLDER_ASSERT(index < N);
    return coordinates[index];
}

template<std::size_t N, typename T>
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

template<std::size_t N, typename T>
inline bool Vector<N, T>::operator==(const Vector<N, T>& other) const
{
    return std::equal(coordinates, coordinates+N, other.coordinates,
                      [](T a, T b)
                      {
                          return float_equal(a, b);
                      });
}

template<std::size_t N, typename T>
inline bool Vector<N, T>::operator!=(const Vector<N, T>& other) const
{
    return !(*this == other);
}

template<std::size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator+=(const Vector<N, T>& other)
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] += other.coordinates[i];
    }
    return *this;
}

template<std::size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator-=(const Vector<N, T>& other)
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] -= other.coordinates[i];
    }
    return *this;
}

template<std::size_t N, typename T>
inline Vector<N, T> Vector<N, T>::operator+(const Vector<N, T>& other) const
{
    return Vector<N, T>(*this) += other;
}

template<std::size_t N, typename T>
inline Vector<N, T> Vector<N, T>::operator-(const Vector<N, T>& other) const
{
    return Vector<N, T>(*this) -= other;
}

template<std::size_t N, typename T>
T Vector<N, T>::operator*(const Vector<N, T>& other) const
{
    T res = 0;
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        res += coordinates[i] * other.coordinates[i];
    }
    return res;
}

template<std::size_t N, typename T>
Vector<N, T> Vector<N, T>::operator-() const
{
    Vector<N, T> V = *this;
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        V.coordinates[i] = -V.coordinates[i];
    }
    return V;
}

template<std::size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator*=(T other)
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates *= other;
    }
    return *this;
}

template<std::size_t N, typename T>
Vector<N, T>& Vector<N, T>::operator/=(T other)
{
    POLDER_ASSERT(other != 0);
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        coordinates /= other;
    }
    return *this;
}

template<std::size_t N, typename T>
inline Vector<N, T> Vector<N, T>::operator*(T other) const
{
    return Vector(*this) *= other;
}

template<std::size_t N, typename T>
inline Vector<N, T> Vector<N, T>::operator/(T other) const
{
    return Vector(*this) /= other;
}

template<std::size_t N, typename T>
inline T& Vector<N, T>::x()
{
    return coordinates[0];
}

template<std::size_t N, typename T>
inline T& Vector<N, T>::y()
{
    return coordinates[1];
}

template<std::size_t N, typename T>
inline T& Vector<N, T>::z()
{
    return coordinates[2];
}

template<std::size_t N, typename T>
inline T Vector<N, T>::x() const
{
    return coordinates[0];
}

template<std::size_t N, typename T>
inline T Vector<N, T>::y() const
{
    return coordinates[1];
}

template<std::size_t N, typename T>
inline T Vector<N, T>::z() const
{
    return coordinates[2];
}

template<std::size_t N, typename T>
inline typename Vector<N, T>::iterator Vector<N, T>::begin()
{
    return coordinates;
}

template<std::size_t N, typename T>
inline typename Vector<N, T>::iterator Vector<N, T>::end()
{
    return coordinates + N;
}

template<std::size_t N, typename T>
inline typename Vector<N, T>::const_iterator Vector<N, T>::begin() const
{
    return coordinates;
}

template<std::size_t N, typename T>
inline typename Vector<N, T>::const_iterator Vector<N, T>::end() const
{
    return coordinates + N;
}

template<std::size_t N, typename T>
inline typename Vector<N, T>::const_iterator Vector<N, T>::cbegin() const
{
    return coordinates;
}

template<std::size_t N, typename T>
inline typename Vector<N, T>::const_iterator Vector<N, T>::cend() const
{
    return coordinates + N;
}

template<std::size_t N, typename T>
template<typename First, typename... Args>
auto Vector<N, T>::construct(First first, Args... args)
    -> void
{
    coordinates[N-sizeof...(args)-1] = first;
    construct(args...);
}

template<std::size_t N, typename T>
template<typename First>
auto Vector<N, T>::construct(First first)
    -> void
{
    coordinates[N-1] = first;
}
