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
Hypersphere<N, T>::Hypersphere(const Point<N, T>& center, value_type radius):
    _center(center),
    _radius(radius)
{}

template<size_t N, typename T>
Hypersphere<N, T>::Hypersphere(const Point<N, T>& center, const Vector<N, T>& V):
    _center(center),
    _radius(V.norm())
{}

template<size_t N, typename T>
Hypersphere<N, T>::Hypersphere(const Point<N, T>& center, const Point<N, T>& P):
    _center(center),
    _radius(0.0)
{
    for (size_t i = 0 ; i < N ; ++i)
    {
        const value_type tmp = P[i] - _center[i];
        _radius += tmp * tmp;
    }
    _radius = sqrt(_radius);
}

template<size_t N, typename T>
Point<N, T> Hypersphere<N, T>::center() const
{
    return _center;
}

template<size_t N, typename T>
auto Hypersphere<N, T>::radius() const -> value_type
{
    return _radius;
}

template<size_t N, typename T>
Hypersphere<N, T>& Hypersphere<N, T>::operator=(const Hypersphere<N, T>& other)
{
    if (this != &other)
    {
        _center = other.Center;
        _radius = other.Radius;
    }
    return *this;
}

template<size_t N, typename T>
bool Hypersphere<N, T>::operator==(const Hypersphere<N, T>& other) const
{
    return _center == other._center && round_equal(_radius, other._radius);
}

template<size_t N, typename T>
bool Hypersphere<N, T>::operator!=(const Hypersphere<N, T>& other) const
{
    return !(*this = other);
}

template<size_t N, typename T>
bool Hypersphere<N, T>::includes(const Point<N, T>& P) const
{
    // Hypersphere equation:
        // Two dimensions:   (x - xc)² + (y - yc)² = R²
        // Three dimensions: (x - xc)² + (y - yc)² + (z - zc)² = R²
        // Four dimensions:  (x - xc)² + (y - yc)² + (z - zc)² + (w - wc)² = R²
        // Etc...
    // A point is included in the hypersphere if its distance to the center equals the radius
    // Actually, the above equations are used to spare the square root computation

    value_type res = 0.0;
    for (size_t i = 0 ; i < N ; ++i)
    {
        const value_type temp = P[i] - _center[i];
        res += temp * temp;
    }
    return round_equal(res, _radius*_radius);
}
