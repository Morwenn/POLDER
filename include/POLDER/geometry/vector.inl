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

template<size_t N>
inline Vector<N>::Vector(const Vector<N>& other)
{
    std::copy(other.coordinates, other.coordinates+N, coordinates);
}

template<size_t N>
inline Vector<N>::Vector(const std::initializer_list<double>& coords)
{
    assert(coords.size() == N);
    std::copy(coords.begin(), coords.end(), coordinates);
}

template<size_t N>
Vector<N>::Vector(double first, ...)
{
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
inline Vector<N>::Vector(const Point<N>& P)
{
    std::copy(P.coordinates, P.coordinates+N, coordinates);
}

template<size_t N>
Vector<N>::Vector(const Point<N>& origin, const Point<N>& target)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] = target[i] - origin[i];
    }
}

template<size_t N>
Vector<N>::Vector(const Line<N>& L)
{
    coordinates[0] = 1.0;
    const Direction<N>& dir = L.direction();
    for (size_t i = 1 ; i < N ; ++i)
    {
        coordinates[i] = dir[i-1];
    }
}

template<size_t N>
inline Direction<N> Vector<N>::direction() const
{
    return Direction<N>(*this);
}

template<size_t N>
double Vector<N>::norm(math::Norm n) const
{
    switch (n)
    {
        case math::Norm::Manhattan:
        {
            double res = 0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += fabs(coordinates[i]);
            }
            return res;
        }
        case math::Norm::Euclidean:
        {
            double res = 0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += coordinates[i] * coordinates[i];
            }
            return sqrt(res);
        }
        case math::Norm::Maximum:
        {
            double res = fabs(coordinates[0]);
            for (size_t i = 1 ; i < N ; ++i)
            {
                const double tmp = fabs(coordinates[i]);
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

template<size_t N>
double Vector<N>::norm(math::Norm n, unsigned int p) const
{
    switch (n)
    {
        case math::Norm::P:
        {
            double res = 0;
            for (size_t i = 0 ; i < N ; ++i)
            {
                res += pow(fabs(coordinates[i]), p);
            }
            return pow(res, 1.0 / p);
        }
    }
    return 1.0; // Should never be executed
}

template<size_t N>
inline double Vector<N>::operator[](size_t index) const
{
    assert(index < N);
    return coordinates[index];
}

template<size_t N>
inline double& Vector<N>::operator[](size_t index)
{
    assert(index < N);
    return coordinates[index];
}

template<size_t N>
inline Vector<N>& Vector<N>::operator=(const Vector<N>& other)
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
inline bool Vector<N>::operator==(const Vector<N>& other) const
{
    return round_equal(coordinates, coordinates+N, other.coordinates);
}

template<size_t N>
inline bool Vector<N>::operator!=(const Vector<N>& other) const
{
    return !(*this == other);
}

template<size_t N>
Vector<N>& Vector<N>::operator+=(const Vector<N>& other)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] += other.coordinates[i];
    }
    return *this;
}

template<size_t N>
Vector<N>& Vector<N>::operator-=(const Vector<N>& other)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates[i] -= other.coordinates[i];
    }
    return *this;
}

template<size_t N>
inline Vector<N> Vector<N>::operator+(const Vector<N>& other) const
{
    return Vector<N>(*this) += other;
}

template<size_t N>
inline Vector<N> Vector<N>::operator-(const Vector<N>& other) const
{
    return Vector<N>(*this) -= other;
}

template<size_t N>
double Vector<N>::operator*(const Vector<N>& other) const
{
    double res = 0;
    for (size_t i = 0 ; i < N ; ++i)
    {
        res += coordinates[i] * other.coordinates[i];
    }
    return res;
}

template<size_t N>
Vector<N> Vector<N>::operator-() const
{
    Vector<N> V = *this;
    for (size_t i = 0 ; i < N ; ++i)
    {
        V.coordinates[i] = -V.coordinates[i];
    }
    return V;
}

template<size_t N>
Vector<N>& Vector<N>::operator*=(double other)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates *= other;
    }
    return *this;
}

template<size_t N>
Vector<N>& Vector<N>::operator/=(double other)
{
    assert(other != 0);
    for (size_t i = 0 ; i < N ; ++i)
    {
        coordinates /= other;
    }
    return *this;
}

template<size_t N>
inline Vector<N> Vector<N>::operator*(double other) const
{
    return Vector(*this) *= other;
}

template<size_t N>
inline Vector<N> Vector<N>::operator/(double other) const
{
    return Vector(*this) /= other;
}

template<size_t N>
inline double& Vector<N>::x()
{
    return coordinates[0];
}

template<size_t N>
inline double& Vector<N>::y()
{
    return coordinates[1];
}

template<size_t N>
inline double& Vector<N>::z()
{
    return coordinates[2];
}

template<size_t N>
inline double Vector<N>::x() const
{
    return coordinates[0];
}

template<size_t N>
inline double Vector<N>::y() const
{
    return coordinates[1];
}

template<size_t N>
inline double Vector<N>::z() const
{
    return coordinates[2];
}

template<size_t N>
inline typename Vector<N>::iterator Vector<N>::begin()
{
    return coordinates;
}

template<size_t N>
inline typename Vector<N>::iterator Vector<N>::end()
{
    return coordinates + N;
}

template<size_t N>
inline typename Vector<N>::const_iterator Vector<N>::begin() const
{
    return coordinates;
}

template<size_t N>
inline typename Vector<N>::const_iterator Vector<N>::end() const
{
    return coordinates + N;
}

template<size_t N>
inline typename Vector<N>::const_iterator Vector<N>::cbegin() const
{
    return coordinates;
}

template<size_t N>
inline typename Vector<N>::const_iterator Vector<N>::cend() const
{
    return coordinates + N;
}
